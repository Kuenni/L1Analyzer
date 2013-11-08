import FWCore.ParameterSet.Config as cms

process = cms.Process("L1DataAggregator")


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

#JEC necessary for getting jet collections
process.load("JetMETCorrections.Configuration.DefaultJEC_cff")


#Loading L1TriggerDPG configs
process.load('L1TriggerDPG.L1Ntuples.l1NtupleProducer_cfi')
process.l1NtupleProducer.verbose = cms.untracked.bool(True)
process.l1NtupleProducer.hltSource = cms.InputTag("none")

process.load("L1TriggerDPG.L1Ntuples.l1ExtraTreeProducer_cfi")

process.load("L1TriggerDPG.L1Ntuples.l1MenuTreeProducer_cfi")
process.load("EventFilter.L1GlobalTriggerRawToDigi.l1GtTriggerMenuLite_cfi")

process.load("L1TriggerDPG.L1Ntuples.l1RecoTreeProducer_cfi")

process.load("L1TriggerDPG.L1Ntuples.l1MuonRecoTreeProducer_cfi")

# global tag FIXME
process.GlobalTag.globaltag = 'DES17_62_V7::All'

# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Analysed.root')
)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:0E84878D-1522-E311-B1DB-003048678FB8.root'
    )
)

process.demo = cms.EDAnalyzer('L1Analyzer'
)

process.out = cms.OutputModule(
        "PoolOutputModule",
        outputCommands = cms.untracked.vstring(
			'keep *'
                ),
        fileName = cms.untracked.string('Collections.root')
        )


process.p = cms.Path(
			process.RawToDigi*
			process.gtDigis* 		#Generate digis from sim
			process.gtEvmDigis*		#for L1 muon system information
			process.gctDigis*
    			process.dttfDigis*
    			process.csctfDigis*
			process.l1NtupleProducer*	#Run the nTuple producer from L1TriggerDPG
			process.l1extraParticles*
			process.l1ExtraTreeProducer*
			process.l1GtTriggerMenuLite*
			process.l1MenuTreeProducer*
			process.l1RecoTreeProducer*
			process.l1MuonRecoTreeProducer
			)

process.outpath = cms.EndPath(process.out)
