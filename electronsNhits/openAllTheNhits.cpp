//////////////////////////
// This is an example of how to open a root file and fill
// histograms nhits, MCPMThits, and MCPhotoElectronCount
// which are similar parts of the RAT DS.
//
//////////////////////////
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>

using namespace std;

#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/PMTProperties.hh>
#include <RAT/DS/MCTrack.hh>
#include <RAT/DS/MCTrackStep.hh>
#include <RAT/DS/MCHit.hh>


void openAlltheNhits(const char* inFile)
{

    const int largestBin = 3000;

    //define the histograms we want to plot
    TH1F* evNhits = new TH1F("evNhits", "evNhits", (int) largestBin/20, 0, largestBin);
    TH1F* MCPMThits = new TH1F("MCPPMThits", "MCPMThits", (int) largestBin/20, 0, largestBin);
    TH1F* MCPECount = new TH1F("MCPECount", "MCPECount", (int) largestBin/20, 0, largestBin);

    //open the root file and set the branch address to DS
    TFile *dataFile = new TFile(inFile);
    TTree* tree = (TTree*) dataFile->Get("T");
    RAT::DS::Root* rds = new RAT::DS::Root();
    tree->SetBranchAddress("ds", &rds);
    int nEvents = tree->GetEntries();
    for(int i=0; i<nEvents; i++) //loop over events for the MC branch
	{
	  tree->GetEntry(i);
		RAT::DS::MC* rmc = rds->GetMC();
		MCPMThits->Fill(rmc->GetMCPMTCount()); //fill the MC PMT hit histogram
		MCPECount->Fill(rmc->GetNumPE()); //fill the MC photo electron count histogram
	}

    for(int i=0; i<nEvents; i++) //now loop over events for the EV branch
	{
	  tree->GetEntry(i);
	  int evc = rds->GetEVCount();
	     for(int tr=0; tr<evc; tr++){ //this is the re-trigger loop
		// retriggers are included here,
		// you'll notice a lot of low Nhit events from the retriggers on the plot
		RAT::DS::EV* rev = rds->GetEV(tr);
		evNhits->Fill(rev->GetNhits()); //fill the Nhit histogram
	     }
	}

    //make things pretty
    //set line width to thicker than default
    evNhits->SetLineWidth(2);
    MCPMThits->SetLineWidth(2);
    MCPECount->SetLineWidth(2);

    //set the color of the different histograms
    evNhits->SetLineColor(kBlack);
    MCPMThits->SetLineColor(kRed);
    MCPECount->SetLineColor(kBlue);

    //take out the title & the status box
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    //set the axis titles
    evNhits->SetXTitle("Number of Nhits, PMThits, or MCPEs");
    evNhits->SetYTitle("Number of Events");

    //draw the things
    evNhits->Draw();
    MCPMThits->Draw("same");
    MCPECount->Draw("same");

    //make a legend
    TLegend *leg = new TLegend(0.15, 0.65, 0.48, 0.85);
    //make it pretty
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    //add the entries
    leg->AddEntry(evNhits);
    leg->AddEntry(MCPMThits);
    leg->AddEntry(MCPECount);
    leg->Draw();


}
