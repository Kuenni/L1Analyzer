import FWCore.ParameterSet.Config as cms

process = cms.Process("L1DTTrigProd")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cff")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.DTGeometryESModule.applyAlignment = False

process.load("L1Analyzer.DTTrigger.dtTriggerPrimitiveDigis_cfi")

process.dtTriggerPrimitiveDigis.digiTag = "hltMuonDTDigis"


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:0E84878D-1522-E311-B1DB-003048678FB8.root')
)

#process.MessageLogger = cms.Service("MessageLogger",
#    debugModules = cms.untracked.vstring('*'),
#    cout = cms.untracked.PSet(
#        threshold = cms.untracked.string('INFO'),
#        WARNING = cms.untracked.PSet(
#            limit = cms.untracked.int32(0)
#        ),
#        noLineBreaks = cms.untracked.bool(True)
#    ),
#    destinations = cms.untracked.vstring('cout')
#)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *', 
        'keep L1MuDTChambPhContainer_*_*_*', 
        'keep L1MuDTChambThContainer_*_*_*'),
    fileName = cms.untracked.string('DTTriggerPrimitives.root')
)

process.p = cms.Path(process.dtTriggerPrimitiveDigis)
process.this_is_the_end = cms.EndPath(process.out)

