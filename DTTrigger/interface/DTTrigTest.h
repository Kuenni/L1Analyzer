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
  int             		ngen;
  std::vector<float>	pxgen;
  std::vector<float>	pygen;
  std::vector<float> 	pzgen;
  std::vector<float> 	ptgen;
  std::vector<float> 	etagen;
  std::vector<float> 	phigen;
  std::vector<int>     	chagen;
  std::vector<float> 	vxgen;
  std::vector<float>  	vygen;
  std::vector<float> 	vzgen;
  
  //GenParticle Information
  int 		nGenParticles;
  std::vector<double>	etaGenParticles;
  std::vector<double> 	phiGenParticles;

  // BTI
  int nbti;
  std::vector<int> bwh;
  std::vector<int> bstat;
  std::vector<int> bsect;
  std::vector<int> bsl;
  std::vector<int> bnum;
  std::vector<int> bbx;
  std::vector<int> bcod;
  std::vector<int> bk;
  std::vector<int> bx;
  std::vector<float> bposx;
  std::vector<float> bposy;
  std::vector<float> bposz;
  std::vector<float> bdirx;
  std::vector<float> bdiry;
  std::vector<float> bdirz;
  
  // TRACO
  int ntraco;
  std::vector<int> twh;
  std::vector<int> tstat;
  std::vector<int> tsect;
  std::vector<int> tnum;
  std::vector<int> tbx;
  std::vector<int> tcod;
  std::vector<int> tk;
  std::vector<int> tx;
  std::vector<float> tposx;
  std::vector<float> tposy;
  std::vector<float> tposz;
  std::vector<float> tdirx;
  std::vector<float> tdiry;
  std::vector<float> tdirz;
  
  // TSPHI
  int ntsphi;
  std::vector<int> swh;
  std::vector<int> sstat; 
  std::vector<int> ssect;
  std::vector<int> sbx;
  std::vector<int> scod;
  std::vector<int> sphi;
  std::vector<int> sphib;
  std::vector<float> sposx;
  std::vector<float> sposy;
  std::vector<float> sposz;
  std::vector<float> sdirx;
  std::vector<float> sdiry;
  std::vector<float> sdirz;

  // TSTHETA
  int ntstheta;
  std::vector<int> thwh;
  std::vector<int> thstat; 
  std::vector<int> thsect;
  std::vector<int> thbx;
  int thcode[40][7];
  int thpos[40][7];
  int thqual[40][7];

  // SECTOR COLLECTOR (PHI VIEW)
  int nscphi;
  std::vector<int> scphwh;
  std::vector<int> scphstat; 
  std::vector<int> scphsect;
  std::vector<int> scphbx;
  std::vector<int> scphcod;
  std::vector<int> scphphi;
  std::vector<int> scphphib;
  std::vector<float> scphposx;
  std::vector<float> scphposy;
  std::vector<float> scphposz;
  std::vector<float> scphdirx;
  std::vector<float> scphdiry;
  std::vector<float> scphdirz;

  // SECTOR COLLECTOR (THETA VIEW)
  int nsctheta;
  std::vector<int> scthwh;
  std::vector<int> scthstat; 
  std::vector<int> scthsect;
  std::vector<int> scthbx;
  int scthcode[40][7];
  int scthpos[40][7];
  int scthqual[40][7];

};
 
#endif

