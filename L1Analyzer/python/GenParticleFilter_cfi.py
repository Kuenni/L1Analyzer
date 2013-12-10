import FWCore.ParameterSet.Config as cms

#filter on the genparticles given in the gen particle id vector
#filtering criteria are the min pt, status and eta
mugenfilter = cms.EDFilter("MCSingleParticleFilter",
	Status = cms.untracked.vint32(1,1),
	MinPt = cms.untracked.vdouble(10.0,10.0),
	ParticleID = cms.untracked.vint32(13,-13),
	MinEta = cms.untracked.vdouble(-0.5,-0.5),
	MaxEta = cms.untracked.vdouble(0.5,0.5),
)
