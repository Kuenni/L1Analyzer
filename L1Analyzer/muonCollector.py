import FWCore.ParameterSet.Config as cms

process = cms.Process("MuonCollector")

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
#process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:00D4272D-8EF1-E111-BE0F-0017A4770C18.root'
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/00D4272D-8EF1-E111-BE0F-0017A4770C18.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/0231DA3D-C4F3-E111-89B5-00266CFC3B0C.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/02A2D10D-B4F3-E111-9D38-AC162DABCAF8.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/02EC6BC3-8FF1-E111-BCDA-0017A4771030.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/043D7273-6DF1-E111-9D5A-00266CFFBCB0.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/06CC4E53-6BF1-E111-974A-78E7D1E4B6E8.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/08CA83CB-8BF1-E111-B4EE-00266CFFBDE8.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/0CE046A9-85F1-E111-A6CC-AC162DACC328.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/0E9945C6-63F1-E111-AE9E-1CC1DE051028.root',
#	'/store/mc/Summer12_DR53X/ZZTo4mu_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/12C91913-CBF3-E111-BD99-1CC1DE052068.root'
    )
)

process.load('PhysicsTools.PatAlgos.mcMatchLayer0.muonMatch_cfi')
process.muonMatch.checkCharge = cms.bool(False)
process.muonMatch.resolveAmbiguities = cms.bool(False)

process.load('PhysicsTools.PatAlgos.producersLayer1.muonProducer_cff')
process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')

process.out = cms.OutputModule(
	"PoolOutputModule",
	outputCommands = cms.untracked.vstring(
		'drop *',
		'keep *_*muon*_*_*',
		'keep *_*Muon*_*_*',
		'keep *_*genParticles*_*_*',
		'keep *_*muonMatch*_*_*',
		'keep *_*trigger*_*_*',
		'keep *_*Trigger*_*_*'
		),
	fileName = cms.untracked.string('muonCollections.root')
	)

process.outpath = cms.EndPath(process.muonMatch*
	process.makePatMuons*
	process.patTriggerDefaultSequence*
	process.out)
