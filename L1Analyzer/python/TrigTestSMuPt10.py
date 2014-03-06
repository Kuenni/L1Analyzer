import FWCore.ParameterSet.Config as cms

process = cms.Process('DataAggregatorL1TUpgrade')


process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')			#originally included
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.Geometry.GeometryIdeal_cff')			#originally included
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#global Tag for the given source File
process.GlobalTag.globaltag = 'START62_V1::All'

#Load own plugins

#From LXR. Makes dttriganalyzer run because it needs a DT config record 
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfig_cff")

#Load the DTTrigTest config
process.load('L1Analyzer.DTTrigger.dttrigtest_cfi')
process.dttriganalyzer.debug = cms.untracked.bool(False)
process.dttriganalyzer.outputFileName = cms.untracked.string('TrigTestsMuPt10.root')
#set the correct dt digi input tag
process.dttriganalyzer.digiTag = cms.InputTag("simMuonDTDigis")


#Load the gen muon filter
process.load('L1Analyzer.L1Analyzer.GenParticleFilter_cfi')

infile = []
infile.append('file:/user/kuensken/Promotion/CMSSW/CMSSW_6_2_0_SLHC3/src/crabDirs/MuGunPt10dR0_3/root/MuGun.root')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Analysed.root')
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

process.L1TMuonSeq = cms.Sequence( #	process.mugenfilter*
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
