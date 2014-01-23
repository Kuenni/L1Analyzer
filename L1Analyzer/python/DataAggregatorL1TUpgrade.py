import FWCore.ParameterSet.Config as cms

process = cms.Process('DataAggregatorL1TUpgrade')


process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')			#originally included
#process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.Geometry.GeometryIdeal_cff')			#originally included
process.load('Configuration.Geometry.GeometryDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('L1TriggerDPGUpgrade.L1TMuon.L1TMuonTriggerPrimitiveProducer_cfi')
process.load('L1TriggerDPGUpgrade.L1TMuon.L1CSCTFTrackConverter_cfi')
process.load('L1TriggerDPGUpgrade.L1TMuon.L1DTTFTrackConverter_cfi')
process.load('L1TriggerDPGUpgrade.L1TMuon.L1RPCTFTrackConverter_cfi')
process.load('L1TriggerDPGUpgrade.L1TMuon.L1TMuonSimpleDeltaEtaHitMatcher_cfi')

#Load own plugins
process.load('L1Analyzer.L1Analyzer.BXAnalyzer_cfi')

#From LXR. Makes dttriganalyzer run because it needs a DT config record 
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfig_cff")

#Load the DTTrigTest config
process.load('L1Analyzer.DTTrigger.dttrigtest_cfi')
process.dttriganalyzer.debug = cms.untracked.bool(False)

#Load the gen muon filter
process.load('L1Analyzer.L1Analyzer.GenParticleFilter_cfi')

#
# Originally included
# 
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V7A::All', '')

#global Tag for the given source File
process.GlobalTag.globaltag = 'DES17_62_V7::All'

infile = []
infile.append('file:0E84878D-1522-E311-B1DB-003048678FB8.root')
#infile.append('file:STEP2_RAW2DIGI_L1Reco_RECO_PU.root')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Analysed.root')
)

#process.MessageLogger = cms.Service("MessageLogger",
 #       destinations = cms.untracked.vstring("Log")
#)

#
# Originally included source files
#
##################################
#infile.append('file:SingleMuFlatPt_minusEta_1GeVto200GeV_GEN_SIM_DIGI_L1.root')
#['file:SingleMuFlatPt_5GeVto200GeV_GEN_SIM_DIGI_L1.root']
#['file:SingleMuFlatPt_minusEta_1GeVto200GeV_GEN_SIM_DIGI_L1.root']
#infile.append('file:SingleMuFlatPt_plusEta_1GeVto200GeV_GEN_SIM_DIGI_L1.root')
#infile.append('file:SingleMuFlatPt_plusEta_1GeVto200GeV_GEN_SIM_DIGI_L1_2.root')
#infile.append('file:SingleMuFlatPt_minusEta_1GeVto200GeV_GEN_SIM_DIGI_L1_2.root')


##
# MAX EVENT NUMBER
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source(
    'PoolSource',
    fileNames = cms.untracked.vstring(infile)
    )

process.L1TMuonSeq = cms.Sequence( 	process.mugenfilter*
					process.L1TMuonTriggerPrimitives *
                                   	process.L1CSCTFTrackConverter    *
                                   	process.L1DTTFTrackConverter     *
                                   	process.L1RPCTFTrackConverters   *
                                   	process.L1TMuonSimpleDeltaEtaHitMatcher*
					process.BXAnalyzer*
					process.dttriganalyzer
				)

process.L1TMuonPath = cms.Path(process.L1TMuonSeq)

outCommands = cms.untracked.vstring('drop *')
outCommands.append('keep *_genParticles_*_*')
outCommands.append('keep *_simCsctfDigis_*_*')
outCommands.append('keep *_simDttfDigis_*_*')
outCommands.append('keep *_simRpcTriggerDigis_*_*')
outCommands.append('keep *_simMuonRPCDigis_*_*')
outCommands.append('keep *_simDtTriggerPrimitiveDigis_*_*')
outCommands.append('keep *_simCscTriggerPrimitiveDigis_*_*')
outCommands.append('keep *_L1TMuonTriggerPrimitives_*_*')
outCommands.append('keep *_*Converter_*_*')
outCommands.append('keep *_*Matcher_*_*')

process.FEVTDEBUGoutput = cms.OutputModule(
    "PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = outCommands,
    fileName = cms.untracked.string('L1TMuon.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    )
)

process.outPath = cms.EndPath(process.FEVTDEBUGoutput)

process.schedule = cms.Schedule(process.L1TMuonPath,
                                process.outPath)
