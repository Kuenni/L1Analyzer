#include "Analyse.h"

Analyse::Analyse(TTree* tree, bool debug) : TrigTestTreeData(tree),debug(debug){
	std::cout << "[Analyse] Loading Tree: " << LoadTree(0) << std::endl;
}

TH1D* Analyse::plotBtiTriggers(){
	if(debug)
		std::cout << "[Analyse] plotBtiTriggers called" << std::endl;
	TH1D* hist = new TH1D("histNBtiTriggers","",200,-0.5,199.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(Nbti);
	}
	hist->SetTitle("Distribution of number of BTI triggers per event");
	hist->GetXaxis()->SetTitle("# BTI triggers per evt");
	hist->GetYaxis()->SetTitle("# Entries");
	return hist;
}

TH1D* Analyse::plotNGenMuons(){
	if(debug)
		std::cout << "[Analyse] plotGenMuons called" << std::endl;
	TH1D* hist = new TH1D("histNGenMuons","",200,-0.5,199.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(nGenParticles);
	}
	hist->SetTitle("Distribution of the number of gen muons per Event");
	hist->GetXaxis()->SetTitle("# BTI triggers per evt");
	hist->GetYaxis()->SetTitle("# Entries");
	return hist;
}
