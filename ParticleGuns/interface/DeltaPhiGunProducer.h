#ifndef DeltaPhiGunProducer_H
#define DeltaPhiGunProducer_H

/*
 *  $Date: 07. May 2014$
 *  \author Andreas Kuensken
 *  kuensken@physik.rwth-aachen.de
 *  Derived from MultiParticleInConeGunProducer
 */


#include "L1Analyzer/ParticleGuns/interface/BaseFlatGunProducer.h"
#include "CLHEP/Random/RandExponential.h"
namespace edm
{
  
  class DeltaPhiGunProducer : public BaseFlatGunProducer
  {
  
  public:
    DeltaPhiGunProducer(const ParameterSet &);
    virtual ~DeltaPhiGunProducer();

  private:
   
    virtual void produce(Event & e, const EventSetup& es) override;
    
  protected :
  
    // data members
    double fMinPt   ;
    double fMaxPt   ;

    std::vector<int> fInConeIds;
    double fMinDeltaPhi;
    double fMaxDeltaPhi;
    double fMinMomRatio;
    double fMaxMomRatio;

    double fParticleMinEta;
    double fParticleMaxEta;
    double fParticleMinPhi;
    double fParticleMaxPhi;
    unsigned int fInConeMaxTry;


  };
} 

#endif
