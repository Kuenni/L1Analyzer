//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 28 09:56:06 2013 by ROOT version 5.34/07
// from TTree h1/GMT
// found on file: DTTrigTest.root
//////////////////////////////////////////////////////////

#ifndef TrigTestTreeData_h
#define TrigTestTreeData_h

#include "TROOT.h"
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class TrigTestTreeData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Float_t         Weight;
   Int_t           Ngen;
   std::vector<float>   *Pxgen;
   std::vector<float>   *Pygen;
   std::vector<float>   *Pzgen;
   std::vector<float>   *Ptgen;
   std::vector<float>   *Etagen;
   std::vector<float>   *Phigen;
   std::vector<int>     *Chagen;
   std::vector<float>   *Vxgen;
   std::vector<float>   *Vygen;
   std::vector<float>   *Vzgen;
   Int_t           nGenParticles;
   std::vector<double>  *etaGenParticles;
   std::vector<double>  *phiGenParticles;
   Int_t           Nbti;
   std::vector<int>     *bwh;
   std::vector<int>     *bstat;
   std::vector<int>     *bsect;
   std::vector<int>     *bsl;
   std::vector<int>     *bnum;
   std::vector<int>     *bbx;
   std::vector<int>     *bcod;
   std::vector<int>     *bk;
   std::vector<int>     *bx;
   std::vector<float>   *bposx;
   std::vector<float>   *bposy;
   std::vector<float>   *bposz;
   std::vector<float>   *bdirx;
   std::vector<float>   *bdiry;
   std::vector<float>   *bdirz;
   Int_t           Ntraco;
   std::vector<int>     *twh;
   std::vector<int>     *tstat;
   std::vector<int>     *tsect;
   std::vector<int>     *tnum;
   std::vector<int>     *tbx;
   std::vector<int>     *tcod;
   std::vector<int>     *tk;
   std::vector<int>     *tx;
   std::vector<float>   *tposx;
   std::vector<float>   *tposy;
   std::vector<float>   *tposz;
   std::vector<float>   *tdirx;
   std::vector<float>   *tdiry;
   std::vector<float>   *tdirz;
   Int_t           Ntsphi;
   std::vector<int>     *swh;
   std::vector<int>     *sstat;
   std::vector<int>     *ssect;
   std::vector<int>     *sbx;
   std::vector<int>     *scod;
   std::vector<int>     *sphi;
   std::vector<int>     *sphib;
   std::vector<float>   *sposx;
   std::vector<float>   *sposy;
   std::vector<float>   *sposz;
   std::vector<float>   *sdirx;
   std::vector<float>   *sdiry;
   std::vector<float>   *sdirz;
   Int_t           Ntstheta;
   std::vector<int>     *thwh;
   std::vector<int>     *thstat;
   std::vector<int>     *thsect;
   std::vector<int>     *thbx;
   Int_t           thcode[17][7];   //[Ntstheta]
   Int_t           thpos[17][7];   //[Ntstheta]
   Int_t           thqual[17][7];   //[Ntstheta]
   Int_t           Nscphi;
   std::vector<int>     *scphwh;
   std::vector<int>     *scphstat;
   std::vector<int>     *scphsect;
   std::vector<int>     *scphbx;
   std::vector<int>     *scphcod;
   std::vector<int>     *scphphi;
   std::vector<int>     *scphphib;
   std::vector<float>   *scphposx;
   std::vector<float>   *scphposy;
   std::vector<float>   *scphposz;
   std::vector<float>   *scphdirx;
   std::vector<float>   *scphdiry;
   std::vector<float>   *scphdirz;
   Int_t           Nsctheta;
   std::vector<int>     *scthwh;
   std::vector<int>     *scthstat;
   std::vector<int>     *scthsect;
   std::vector<int>     *scthbx;
   Int_t           scthcode[17][7];   //[Nsctheta]
   Int_t           scthpos[17][7];   //[Nsctheta]
   Int_t           scthqual[17][7];   //[Nsctheta]

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_Ngen;   //!
   TBranch        *b_Pxgen;   //!
   TBranch        *b_Pygen;   //!
   TBranch        *b_Pzgen;   //!
   TBranch        *b_Ptgen;   //!
   TBranch        *b_Etagen;   //!
   TBranch        *b_Phigen;   //!
   TBranch        *b_Chagen;   //!
   TBranch        *b_Vxgen;   //!
   TBranch        *b_Vygen;   //!
   TBranch        *b_Vzgen;   //!
   TBranch        *b_nGenParticles;   //!
   TBranch        *b_etaGenParticles;   //!
   TBranch        *b_phiGenParticles;   //!
   TBranch        *b_Nbti;   //!
   TBranch        *b_bwh;   //!
   TBranch        *b_bstat;   //!
   TBranch        *b_bsect;   //!
   TBranch        *b_bsl;   //!
   TBranch        *b_bnum;   //!
   TBranch        *b_bbx;   //!
   TBranch        *b_bcod;   //!
   TBranch        *b_bk;   //!
   TBranch        *b_bx;   //!
   TBranch        *b_bposx;   //!
   TBranch        *b_bposy;   //!
   TBranch        *b_bposz;   //!
   TBranch        *b_bdirx;   //!
   TBranch        *b_bdiry;   //!
   TBranch        *b_bdirz;   //!
   TBranch        *b_Ntraco;   //!
   TBranch        *b_twh;   //!
   TBranch        *b_tstat;   //!
   TBranch        *b_tsect;   //!
   TBranch        *b_tnum;   //!
   TBranch        *b_tbx;   //!
   TBranch        *b_tcod;   //!
   TBranch        *b_tk;   //!
   TBranch        *b_tx;   //!
   TBranch        *b_tposx;   //!
   TBranch        *b_tposy;   //!
   TBranch        *b_tposz;   //!
   TBranch        *b_tdirx;   //!
   TBranch        *b_tdiry;   //!
   TBranch        *b_tdirz;   //!
   TBranch        *b_Ntsphi;   //!
   TBranch        *b_swh;   //!
   TBranch        *b_sstat;   //!
   TBranch        *b_ssect;   //!
   TBranch        *b_sbx;   //!
   TBranch        *b_scod;   //!
   TBranch        *b_sphi;   //!
   TBranch        *b_sphib;   //!
   TBranch        *b_sposx;   //!
   TBranch        *b_sposy;   //!
   TBranch        *b_sposz;   //!
   TBranch        *b_sdirx;   //!
   TBranch        *b_sdiry;   //!
   TBranch        *b_sdirz;   //!
   TBranch        *b_Ntstheta;   //!
   TBranch        *b_thwh;   //!
   TBranch        *b_thstat;   //!
   TBranch        *b_thsect;   //!
   TBranch        *b_thbx;   //!
   TBranch        *b_thcode;   //!
   TBranch        *b_thpos;   //!
   TBranch        *b_thqual;   //!
   TBranch        *b_Nscphi;   //!
   TBranch        *b_scphwh;   //!
   TBranch        *b_scphstat;   //!
   TBranch        *b_scphsect;   //!
   TBranch        *b_scphbx;   //!
   TBranch        *b_scphcod;   //!
   TBranch        *b_scphphi;   //!
   TBranch        *b_scphphib;   //!
   TBranch        *b_scphposx;   //!
   TBranch        *b_scphposy;   //!
   TBranch        *b_scphposz;   //!
   TBranch        *b_scphdirx;   //!
   TBranch        *b_scphdiry;   //!
   TBranch        *b_scphdirz;   //!
   TBranch        *b_Nsctheta;   //!
   TBranch        *b_scthwh;   //!
   TBranch        *b_scthstat;   //!
   TBranch        *b_scthsect;   //!
   TBranch        *b_scthbx;   //!
   TBranch        *b_scthcode;   //!
   TBranch        *b_scthpos;   //!
   TBranch        *b_scthqual;   //!

   TrigTestTreeData(TTree *tree=0);
   virtual ~TrigTestTreeData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


#endif
