import FWCore.ParameterSet.Config as cms

process = cms.Process("L1Analyzer")


#Loading standard packages from L1TriggerDPG package 
process.load('Configuration/StandardSequences/Services_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/GeometryDB_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

# global tag FIXME
#process.GlobalTag.globaltag = 'START38_V13::All'

# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Analysed.root')
)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:0E84878D-1522-E311-B1DB-003048678FB8.root'
    )
)

process.demo = cms.EDAnalyzer('L1Analyzer'
)


process.p = cms.Path(process.demo)
