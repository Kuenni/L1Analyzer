#define TrigTestTreeData_cxx
#include "TrigTestTreeData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TrigTestTreeData::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L TrigTestTreeData.C
//      Root > TrigTestTreeData t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

TrigTestTreeData::TrigTestTreeData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
	   return;
   }
   Init(tree);
}

TrigTestTreeData::~TrigTestTreeData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TrigTestTreeData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TrigTestTreeData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TrigTestTreeData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Pxgen = 0;
   Pygen = 0;
   Pzgen = 0;
   Ptgen = 0;
   Etagen = 0;
   Phigen = 0;
   Chagen = 0;
   Vxgen = 0;
   Vygen = 0;
   Vzgen = 0;
   etaGenParticles = 0;
   phiGenParticles = 0;
   genParticleId = 0;
   bwh = 0;
   bstat = 0;
   bsect = 0;
   bsl = 0;
   bnum = 0;
   bbx = 0;
   bcod = 0;
   bk = 0;
   bx = 0;
   bposx = 0;
   bposy = 0;
   bposz = 0;
   bdirx = 0;
   bdiry = 0;
   bdirz = 0;
   twh = 0;
   tstat = 0;
   tsect = 0;
   tnum = 0;
   tbx = 0;
   tcod = 0;
   tk = 0;
   tx = 0;
   tposx = 0;
   tposy = 0;
   tposz = 0;
   tdirx = 0;
   tdiry = 0;
   tdirz = 0;
   swh = 0;
   sstat = 0;
   ssect = 0;
   sbx = 0;
   scod = 0;
   sphi = 0;
   sphib = 0;
   sposx = 0;
   sposy = 0;
   sposz = 0;
   sdirx = 0;
   sdiry = 0;
   sdirz = 0;
   thwh = 0;
   thstat = 0;
   thsect = 0;
   thbx = 0;
   scphwh = 0;
   scphstat = 0;
   scphsect = 0;
   scphbx = 0;
   scphcod = 0;
   scphphi = 0;
   scphphib = 0;
   scphposx = 0;
   scphposy = 0;
   scphposz = 0;
   scphdirx = 0;
   scphdiry = 0;
   scphdirz = 0;
   scthwh = 0;
   scthstat = 0;
   scthsect = 0;
   scthbx = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("Ngen", &Ngen, &b_Ngen);
   fChain->SetBranchAddress("Pxgen", &Pxgen, &b_Pxgen);
   fChain->SetBranchAddress("Pygen", &Pygen, &b_Pygen);
   fChain->SetBranchAddress("Pzgen", &Pzgen, &b_Pzgen);
   fChain->SetBranchAddress("Ptgen", &Ptgen, &b_Ptgen);
   fChain->SetBranchAddress("Etagen", &Etagen, &b_Etagen);
   fChain->SetBranchAddress("Phigen", &Phigen, &b_Phigen);
   fChain->SetBranchAddress("Chagen", &Chagen, &b_Chagen);
   fChain->SetBranchAddress("Vxgen", &Vxgen, &b_Vxgen);
   fChain->SetBranchAddress("Vygen", &Vygen, &b_Vygen);
   fChain->SetBranchAddress("Vzgen", &Vzgen, &b_Vzgen);
   fChain->SetBranchAddress("nGenParticles", &nGenParticles, &b_nGenParticles);
   fChain->SetBranchAddress("etaGenParticles", &etaGenParticles, &b_etaGenParticles);
   fChain->SetBranchAddress("phiGenParticles", &phiGenParticles, &b_phiGenParticles);
   fChain->SetBranchAddress("genParticleId", &genParticleId, &b_genParticleId);
   fChain->SetBranchAddress("Nbti", &Nbti, &b_Nbti);
   fChain->SetBranchAddress("bwh", &bwh, &b_bwh);
   fChain->SetBranchAddress("bstat", &bstat, &b_bstat);
   fChain->SetBranchAddress("bsect", &bsect, &b_bsect);
   fChain->SetBranchAddress("bsl", &bsl, &b_bsl);
   fChain->SetBranchAddress("bnum", &bnum, &b_bnum);
   fChain->SetBranchAddress("bbx", &bbx, &b_bbx);
   fChain->SetBranchAddress("bcod", &bcod, &b_bcod);
   fChain->SetBranchAddress("bk", &bk, &b_bk);
   fChain->SetBranchAddress("bx", &bx, &b_bx);
   fChain->SetBranchAddress("bposx", &bposx, &b_bposx);
   fChain->SetBranchAddress("bposy", &bposy, &b_bposy);
   fChain->SetBranchAddress("bposz", &bposz, &b_bposz);
   fChain->SetBranchAddress("bdirx", &bdirx, &b_bdirx);
   fChain->SetBranchAddress("bdiry", &bdiry, &b_bdiry);
   fChain->SetBranchAddress("bdirz", &bdirz, &b_bdirz);
   fChain->SetBranchAddress("Ntraco", &Ntraco, &b_Ntraco);
   fChain->SetBranchAddress("twh", &twh, &b_twh);
   fChain->SetBranchAddress("tstat", &tstat, &b_tstat);
   fChain->SetBranchAddress("tsect", &tsect, &b_tsect);
   fChain->SetBranchAddress("tnum", &tnum, &b_tnum);
   fChain->SetBranchAddress("tbx", &tbx, &b_tbx);
   fChain->SetBranchAddress("tcod", &tcod, &b_tcod);
   fChain->SetBranchAddress("tk", &tk, &b_tk);
   fChain->SetBranchAddress("tx", &tx, &b_tx);
   fChain->SetBranchAddress("tposx", &tposx, &b_tposx);
   fChain->SetBranchAddress("tposy", &tposy, &b_tposy);
   fChain->SetBranchAddress("tposz", &tposz, &b_tposz);
   fChain->SetBranchAddress("tdirx", &tdirx, &b_tdirx);
   fChain->SetBranchAddress("tdiry", &tdiry, &b_tdiry);
   fChain->SetBranchAddress("tdirz", &tdirz, &b_tdirz);
   fChain->SetBranchAddress("Ntsphi", &Ntsphi, &b_Ntsphi);
   fChain->SetBranchAddress("swh", &swh, &b_swh);
   fChain->SetBranchAddress("sstat", &sstat, &b_sstat);
   fChain->SetBranchAddress("ssect", &ssect, &b_ssect);
   fChain->SetBranchAddress("sbx", &sbx, &b_sbx);
   fChain->SetBranchAddress("scod", &scod, &b_scod);
   fChain->SetBranchAddress("sphi", &sphi, &b_sphi);
   fChain->SetBranchAddress("sphib", &sphib, &b_sphib);
   fChain->SetBranchAddress("sposx", &sposx, &b_sposx);
   fChain->SetBranchAddress("sposy", &sposy, &b_sposy);
   fChain->SetBranchAddress("sposz", &sposz, &b_sposz);
   fChain->SetBranchAddress("sdirx", &sdirx, &b_sdirx);
   fChain->SetBranchAddress("sdiry", &sdiry, &b_sdiry);
   fChain->SetBranchAddress("sdirz", &sdirz, &b_sdirz);
   fChain->SetBranchAddress("Ntstheta", &Ntstheta, &b_Ntstheta);
   fChain->SetBranchAddress("thwh", &thwh, &b_thwh);
   fChain->SetBranchAddress("thstat", &thstat, &b_thstat);
   fChain->SetBranchAddress("thsect", &thsect, &b_thsect);
   fChain->SetBranchAddress("thbx", &thbx, &b_thbx);
   fChain->SetBranchAddress("thcode", thcode, &b_thcode);
   fChain->SetBranchAddress("thpos", thpos, &b_thpos);
   fChain->SetBranchAddress("thqual", thqual, &b_thqual);
   fChain->SetBranchAddress("Nscphi", &Nscphi, &b_Nscphi);
   fChain->SetBranchAddress("scphwh", &scphwh, &b_scphwh);
   fChain->SetBranchAddress("scphstat", &scphstat, &b_scphstat);
   fChain->SetBranchAddress("scphsect", &scphsect, &b_scphsect);
   fChain->SetBranchAddress("scphbx", &scphbx, &b_scphbx);
   fChain->SetBranchAddress("scphcod", &scphcod, &b_scphcod);
   fChain->SetBranchAddress("scphphi", &scphphi, &b_scphphi);
   fChain->SetBranchAddress("scphphib", &scphphib, &b_scphphib);
   fChain->SetBranchAddress("scphposx", &scphposx, &b_scphposx);
   fChain->SetBranchAddress("scphposy", &scphposy, &b_scphposy);
   fChain->SetBranchAddress("scphposz", &scphposz, &b_scphposz);
   fChain->SetBranchAddress("scphdirx", &scphdirx, &b_scphdirx);
   fChain->SetBranchAddress("scphdiry", &scphdiry, &b_scphdiry);
   fChain->SetBranchAddress("scphdirz", &scphdirz, &b_scphdirz);
   fChain->SetBranchAddress("Nsctheta", &Nsctheta, &b_Nsctheta);
   fChain->SetBranchAddress("scthwh", &scthwh, &b_scthwh);
   fChain->SetBranchAddress("scthstat", &scthstat, &b_scthstat);
   fChain->SetBranchAddress("scthsect", &scthsect, &b_scthsect);
   fChain->SetBranchAddress("scthbx", &scthbx, &b_scthbx);
   fChain->SetBranchAddress("scthcode", scthcode, &b_scthcode);
   fChain->SetBranchAddress("scthpos", scthpos, &b_scthpos);
   fChain->SetBranchAddress("scthqual", scthqual, &b_scthqual);
   Notify();
}

Bool_t TrigTestTreeData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TrigTestTreeData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TrigTestTreeData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

