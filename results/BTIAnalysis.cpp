#include "BTIAnalysis.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TCanvas.h"
#include "TH1.h"
#include <vector>
/**
 * Make the plots for number of hit BTIs
 */
TH1D* BTIAnalysis::plotBtiTriggers(){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTriggers called" << std::endl;
	TString histName("histNBtiTrg");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName,"Distribution of number of BTI triggers per event;# BTI triggers per evt;# Entries",201,-1.5,199.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(Nbti);
	}
	return hist;
}

/**
 * Plot the number of BTI triggers vs Bx Id
 */
TH1D* BTIAnalysis::plotBtiTrgVsBx(){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTrgVsBx called" << std::endl;
	TString histName("histBtiTrgVsBx");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName,"Distribution of BTI triggers over BX ID;BX ID;# Entries",31,-0.5,30.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( int j = 0 ; j < bbx->size() ; j++ ){
			//Look only at HTRG, since LTRG are not used for DT Trig
			if( bcod->at(j) == 8 )
				hist->Fill( bbx->at(j) );
		}
	}
	return hist;
}

/**
 * Plot the number of BTI triggers vs Bx ID per station in phi
 */
TH1D* BTIAnalysis::plotBtiTrgVsBxPerStationPhi(int station){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTrgVsBxPerStationPhi called" << std::endl;
	TString histName("histBtiTrgVsBxPerPhiSt");
	histName += station;
	histName += getSampleName();

	TString histTitle("Distribution of BTI triggers over BX ID in #phi, Station ");
	histTitle += station;
	histTitle += ";BX ID;# Entries";

	TH1D* hist = new TH1D(histName,histTitle,31,-0.5,30.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( int j = 0 ; j < bbx->size() ; j++ ){
<<<<<<< Updated upstream
			if( bstat->at(j) == station && (bsl->at(j) == 1 || bsl->at(j) == 3) )
=======
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if( bstat->at(j) == station && (bsl->at(j) == sl) && ( bcod->at(j) == 8 ) )
>>>>>>> Stashed changes
				hist->Fill( bbx->at(j) );
		}
	}
	return hist;
}

/**
 * Plot the number of BTI triggers vs Bx ID per station in theta
 */
TH1D* BTIAnalysis::plotBtiTrgVsBxPerStationTheta(int station){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTrgVsBxPerStationTheta called" << std::endl;
	TString histName("histBtiTrgVsBxPerThetaSt");
	histName += station;
	histName += getSampleName();

	TString histTitle("Distribution of BTI triggers over BX ID in #eta, Station ");
	histTitle += station;
	histTitle += ";BX ID;# Entries";

	TH1D* hist = new TH1D(histName,histTitle,31,-0.5,30.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( int j = 0 ; j < bbx->size() ; j++ ){
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if( bstat->at(j) == station && (bsl->at(j) == 2) && (bcod->at(j) == 8) )
				hist->Fill( bbx->at(j) );
		}
	}
	return hist;
}

/**
 * Plot the number of BTI triggers with no theta information resolved for a certain station
 */
TH2D* BTIAnalysis::plotNoBtiTheta(int station){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotNoBtiTheta called" << std::endl;
	TString histName("histNoBtiTheta");
	histName += getSampleName();
	histName += "St";
	histName += station;

	TString histTitle("Distribution of no BTI theta information Station ");
	histTitle += station;
	histTitle += " " + getSampleName();
	histTitle += ";Wheel;Sector";

	TH2D* hist = new TH2D( histName , histTitle , 7, -3.5 , 3.5 , 15 , -1.5 , 13.5 );
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		int counter = 0;

		//Loop over BTI triggers
		for( int j = 0 ; j < Nbti ; j++ ){
			int wheel  = -1;
			int sector = -1;
			//Only start loop if we haven't sl2 (i.e. Theta) already at the beginning
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if( ( bsl-> at(j) != 2 ) && ( bstat->at(j) == station ) && (bcod->at(j) == 8) ){
				//Save wheel and sector for later
				wheel = bwh->at(j);
				sector = bsect->at(j);
			} else {
				continue;
			}
			//Now loop over remaining trigger and look for sl2 entries
			for( int k = j ; k < Nbti ; k++ ){
				//If we find a trigger with same station, wheel, and sector:
				//break, because it is not what we are looking for
				if( 	( bsl->at(k) == 2 )
						&& ( bstat->at(k)	== station )
						&& ( bwh->at(k)		== wheel )
						&& ( bsect->at(k)	== sector )
						&& ( bcod->at(k) 	== 8 )
						){
					counter++;
					break;
				}
			}
			//After inner loop, if nothing raised the counter, we are missing the theta
			//information for this bti trigger
			if(counter == 0)
				hist->Fill(wheel,sector);
		}
	}
	hist->SetOption("colz");
	TCanvas* localCanvas = new TCanvas();
	hist->Draw();
	gPad->Update();
	TPaveStats *st = (TPaveStats*)hist->FindObject("stats");
	st->SetOptStat(10);
	st->SetX1NDC(0.75);
	st->SetX2NDC(0.95);
	st->SetY1NDC(0.9);
	st->SetY2NDC(0.99);
	delete localCanvas;
	localCanvas = 0;
	return hist;
}

/**
 * Plots the mean number of BTI events per station for a given station and super layer
 */
TH2D* BTIAnalysis::plotBtiTrigPerStatAndSL(int station, int sl){
	if(getDebug())
			std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTrigPerStatAndSL called" << std::endl;
	TString histName("histBtiTrigPerStatAndSL");
	histName += getSampleName();
	histName += "St";
	histName += station;
	histName += "SL";
	histName += sl;

	TString histTitle("Distribution of # of BTI triggers per station ");
	histTitle += station;
	histTitle += " and SL ";
	histTitle += sl;
	histTitle += ", " + getSampleName();
	histTitle += ";Wheel;Sector";

	TH2D* hist = new TH2D( histName , histTitle , 7, -3.5 , 3.5 , 15 , -1.5 , 13.5 );

	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( int i = 0 ; i < Nbti ; i++ ){
			//If the desired SL has a trigger, add entry for wheel and sector in histogram
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if( bsl->at(i) == sl && bstat->at(i) == station && bcod->at(i) == 8)
				hist->Fill(bwh->at(i),bsect->at(i));
		}


	}

	hist->SetOption("colz");

	return hist;
}

/**
 * Plot number of BTI triggers per eta segment
 */
TH1D* BTIAnalysis::plotBtiTriggersPerEta(){
	int nBins = 301;
	if(getDebug())
			std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTriggersPerEta called" << std::endl;

	//Build histogram name
	TString histName("histNBtiTrgPerEta");
	histName += getSampleName();

	//Build Histogram title
	TString histTitle("Distribution of number of BTI triggers per #eta");
	histTitle += ";#eta of BTI Trigger Data;";

	//Calculate the bin width for the yAxis Title
	double binWidth = 3.1 / (double)(nBins + 1.);
	binWidth = (int) (binWidth*100 + 0.5);
	binWidth /= 100.;
	TString yAxisTitle("# Entries / ");
	yAxisTitle += binWidth;
	yAxisTitle += " #eta";

	histTitle += yAxisTitle;

	TH1D* hist = new TH1D( histName , histTitle , nBins+1 , -1.55 , 1.55 ); //-0.5 to center bins around value, +/- 1 to have a frame
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for ( unsigned int j = 0 ; j < beta->size() ; j++ ){
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if(bcod->at(j) == 8)
				hist->Fill(beta->at(j));
		}
	}
	return hist;
}

/**
 * Make the plots for number of hit BTIs per station
 */
TH1D* BTIAnalysis::plotBtiTriggersPerStation(int stationNr){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTriggersPerStation called" << std::endl;
	//Build histogram name
	TString histName("histNBtiTrg");
	histName += getSampleName();
	histName += "St";
	histName += stationNr;
	//Build histogram title
	TString histTitle("Distribution of number of BTI triggers per event for station ");
	histTitle += stationNr;
	histTitle += ";# BTI triggers per evt;# Entries";

	TH1D* hist = new TH1D( histName , histTitle ,43,-1.5,41.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		int stationCounter = 0;
		for( unsigned int j = 0 ; j < bstat->size() ; j++ ){
			//Filter for the requested station
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if( bstat->at(j) == stationNr && bcod->at(j) == 8){
				stationCounter++;
			}
		}
		hist->Fill(stationCounter);
	}
	hist->SetStats(true);
	return hist;
}

/**
 * Plot eta of gen particles in an event which does not have
 * BTI trigger events
 */
TH1D* BTIAnalysis::plotEtaNoBtiTriggers(){
	if(getDebug())
		std::cout << "[BTIAnalysis " << getSampleName() << "] plotEtaNoBtiTriggers called" << std::endl;
	TString histName("histEtanoBti");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName.Data(),"Distribution of gen particle eta with no BTI events in event;gen particle #eta;# Entries",101,-5.05,5.05);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		if( Nbti == 0 ){
			for( unsigned int j = 0 ; j < etaGenParticles->size() ; j++ ){
				hist->Fill(etaGenParticles->at(j));
			}
		}
	}
	return hist;
}

/**
 * Make a histogram of number of events with no theta information with an average over the
 * complete wheel
 */
TH1D* BTIAnalysis::plotNoBtiThetaPerWheel(TH2D* input, int station) {
	if(getDebug())
			std::cout << "[BTIAnalysis " << getSampleName() << "] plotBtiTrigsNoThetaPerWheel called" << std::endl;
	TString histName("histNoBtiThetaPerWheel");
	histName += getSampleName();
	histName += "St";
	histName += station;

	TString histTitle("Distribution of no BTI theta information averaged per wheel, Station ");
	histTitle += station;
	histTitle += " " + getSampleName();
	histTitle += ";Wheel;# Entries";

	TH1D* hist = new TH1D( histName , histTitle , 7, -3.5 , 3.5 );

	for (int i = 0 ; i < 5 ; i++ ){
		double wheelSum = 0;
		for( int j = 0 ; j < 12 ; j++) {
			//Sum over the sectors. Bin positions given by BTIAnalysis::plotNoBtiTheta()
			wheelSum += input->GetBinContent( i + 2 , j + 2 );
		}
		hist->SetBinContent( i+2 , wheelSum );
	}
	return hist;
}
