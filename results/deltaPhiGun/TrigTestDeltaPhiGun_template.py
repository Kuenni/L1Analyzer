import FWCore.ParameterSet.Config as cms

process = cms.Process('DataAggregatorL1TUpgrade')


process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')			#originally included
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgrade2017', '')

#process.load('L1TriggerDPGUpgrade.L1TMuon.L1TMuonTriggerPrimitiveProducer_cfi')
#process.load('L1TriggerDPGUpgrade.L1TMuon.L1CSCTFTrackConverter_cfi')
#process.load('L1TriggerDPGUpgrade.L1TMuon.L1DTTFTrackConverter_cfi')
#process.load('L1TriggerDPGUpgrade.L1TMuon.L1RPCTFTrackConverter_cfi')
#process.load('L1TriggerDPGUpgrade.L1TMuon.L1TMuonSimpleDeltaEtaHitMatcher_cfi')

#Load own plugins
#process.load('L1Analyzer.L1Analyzer.BXAnalyzer_cfi')

#From LXR. Makes dttriganalyzer run because it needs a DT config record 
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfig_cff")

#Load the DTTrigTest config
process.load('L1Analyzer.DTTrigger.dttrigtest_cfi')
process.dttriganalyzer.debug = cms.untracked.bool(False)
process.dttriganalyzer.outputFileName = cms.untracked.string('TrigTestDeltaPhiGun.root')

#Load the gen muon filter
process.load('L1Analyzer.L1Analyzer.GenParticleFilter_cfi')

infile = []
infile.append('file:/net/scratch_cms/institut_3b/kuensken/@jobdir@/DeltaPhi.root')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('DeltaPhi_Analysed.root')
)

process.MessageLogger = cms.Service("MessageLogger",
 #       destinations = cms.untracked.vstring("Log")
)

##
# MAX EVENT NUMBER
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source(
    'PoolSource',
    fileNames = cms.untracked.vstring(infile)
    )

process.L1TMuonSeq = cms.Sequence( 
#					process.BXAnalyzer*
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
