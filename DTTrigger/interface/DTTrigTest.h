//-------------------------------------------------
//
/**  \class DTTrigTest
 *
 *   EDAnalyzer that generates a rootfile useful
 *   for L1-DTTrigger debugging and performance 
 *   studies
 *
 *
 *   $Date: 2009/12/22 09:36:34 $
 *   $Revision: 1.9 $
 *
 *   \author C. Battilana
 */
//
//--------------------------------------------------

#ifndef L1Trigger_DTTrigger_DTTrigTest_h
#define L1Trigger_DTTrigger_DTTrigTest_h

// Framework related headers
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Trigger related headers
#include "L1Analyzer/DTTrigger/interface/DTTrig.h"

// Root headers
#include "TTree.h"
#include "TFile.h"

class DTTrigTest: public edm::EDAnalyzer{
public:

  //! Constructor
  DTTrigTest(const edm::ParameterSet& pset);
  
  //! Destructor
  ~DTTrigTest();

  //! Create tree and Branches
  //void beginJob(const edm::EventSetup & iEventSetup);
  void beginJob();

  //! Close Tree and write File
  void endJob();

  //! Create DTTrig instance and TUs
  void beginRun(const edm::Run& iRun, const edm::EventSetup& iEventSetup);
  
  //! Analyze function executed on all the events
  void analyze(const edm::Event & iEvent, const edm::EventSetup& iEventSetup);
  
private:

  // time to TDC_time conversion
  static const double my_TtoTDC;

  // trigger istance
  DTTrig* my_trig;

  // debug flag
  bool my_debug;
  
  // ParameterSet
  edm::ParameterSet my_params;

  // tree
  TTree* my_tree;
  // TFile
  TFile *my_rootfile;


  //GENERAL block
  int             runn;
  int             eventn;
  float           weight;

  //GEANT block
  int             ngen;
  float           pxgen[20];
  float           pygen[20];
  float           pzgen[20];
  float           ptgen[20];
  float           etagen[20];
  float           phigen[20];
  int             chagen[20];
  float           vxgen[20];
  float           vygen[20];
  float           vzgen[20];
  
  //GenParticle Information
  int 		nGenParticles;
  double	etaGenParticles[20];
  double 	phiGenParticles[20];

  // BTI
  int nbti;
  int bwh[100];
  int bstat[100];
  int bsect[100];
  int bsl[100];
  int bnum[100];
  int bbx[100];
  int bcod[100];
  int bk[100];
  int bx[100];
  float bposx[100];
  float bposy[100];
  float bposz[100];
  float bdirx[100];
  float bdiry[100];
  float bdirz[100];
  
  // TRACO
  int ntraco;
  int twh[80];
  int tstat[80];
  int tsect[80];
  int tnum[80];
  int tbx[80];
  int tcod[80];
  int tk[80];
  int tx[80];
  float tposx[100];
  float tposy[100];
  float tposz[100];
  float tdirx[100];
  float tdiry[100];
  float tdirz[100];
  
  // TSPHI
  int ntsphi;
  int swh[40];
  int sstat[40]; 
  int ssect[40];
  int sbx[40];
  int scod[40];
  int sphi[40];
  int sphib[40];
  float sposx[100];
  float sposy[100];
  float sposz[100];
  float sdirx[100];
  float sdiry[100];
  float sdirz[100]; 

  // TSTHETA
  int ntstheta;
  int thwh[40];
  int thstat[40]; 
  int thsect[40];
  int thbx[40];
  int thcode[40][7];
  int thpos[40][7];
  int thqual[40][7];

  // SECTOR COLLECTOR (PHI VIEW)
  int nscphi;
  int scphwh[40];
  int scphstat[40]; 
  int scphsect[40];
  int scphbx[40];
  int scphcod[40];
  int scphphi[40];
  int scphphib[40];
  float scphposx[100];
  float scphposy[100];
  float scphposz[100];
  float scphdirx[100];
  float scphdiry[100];
  float scphdirz[100]; 

  // SECTOR COLLECTOR (THETA VIEW)
  int nsctheta;
  int scthwh[40];
  int scthstat[40]; 
  int scthsect[40];
  int scthbx[40];
  int scthcode[40][7];
  int scthpos[40][7];
  int scthqual[40][7];

};
 
#endif

