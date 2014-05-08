#include "FWCore/Framework/interface/MakerMacros.h"
// #include "IOMC/Input/interface/MCFileSource.h"

// Julia Yarba : related to particle gun prototypes
//
//#include "IOMC/ParticleGuns/interface/FlatEGunASCIIWriter.h"

#include "L1Analyzer/ParticleGuns/interface/DeltaPhiGunProducer.h"

// particle gun prototypes
//
  
  
/*
using edm::FlatEGunASCIIWriter;
DEFINE_FWK_MODULE(FlatEGunASCIIWriter);
*/

using edm::DeltaPhiGunProducer;
DEFINE_FWK_MODULE(DeltaPhiGunProducer);
