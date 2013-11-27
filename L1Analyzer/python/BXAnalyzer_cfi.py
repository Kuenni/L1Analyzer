import FWCore.ParameterSet.Config as cms
from L1Trigger.DTTrackFinder.dttfDigis_cfi import dttfDigis

BXAnalyzer = cms.EDAnalyzer('BXAnalyzer',
	triggerPrimitiveSrc 	= cms.InputTag("L1TMuonTriggerPrimitives"),
	dtTrackSrc 		= cms.InputTag("simDttfDigis","DTTF"),
	chambPhiContSrc		= cms.InputTag("simDtTriggerPrimitiveDigis"),
	chambThetaContSrc	= cms.InputTag("simDtTriggerPrimitiveDigis"),
	bxMin = cms.int32(-10),
	bxMax = cms.int32(10),
	verbose = cms.bool(False)
)
