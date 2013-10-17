import FWCore.ParameterSet.Config as cms

process = cms.Process("L1Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.messages = cms.untracked.PSet(threshold = cms.untracked.vstring('ERROR'))

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:muonCollections.root'
    )
)

process.TFileService=cms.Service("TFileService",fileName = cms.string("analyzed.root"))

#process.load('PhysicsTools.PatAlgos.mcMatchLayer0.muonMatch_cfi')
#process.muonMatch.checkCharge = cms.bool(False)


process.l1analysis = cms.EDAnalyzer('L1Analyzer'
)

process.p = cms.Path(process.l1analysis)

