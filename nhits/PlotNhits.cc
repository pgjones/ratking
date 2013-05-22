//////////////////////////
// This is an example of how to open a root file and fill
// histograms nhits, MCPMThits, and MCPhotoElectronCount
// which are similar parts of the RAT DS.
//
//////////////////////////
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>

#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DSReader.hh>


void PlotNhits(const char* inFile)
{
  //define the histograms we want to plot
  TH1D* evNhits = new TH1D("evNhits", "evNhits", 150, 0.0, 3000.0);
  TH1D* MCPMThits = new TH1D("MCPPMThits", "MCPMThits", 150, 0.0, 3000.0);
  TH1D* MCPECount = new TH1D("MCPECount", "MCPECount", 150, 0.0, 3000.0);

  //open the root file with the DSReader and get the first event
  RAT::DSReader reader(inFile);
  RAT::DS::Root* rds = reader.NextEvent();
  while(rds != NULL)
	{
      RAT::DS::MC* rmc = rds->GetMC();
      MCPMThits->Fill(rmc->GetMCPMTCount()); //fill the MC PMT hit histogram
      MCPECount->Fill(rmc->GetNumPE()); //fill the MC photo electron count histogram
      
      for(int iEV=0; iEV<rds->GetEVCount(); iEV++)
        {
          //this is the re-trigger loop, I'm including re-triggers
          //you'll notice a lot of low Nhit events from the retriggers on the plot
          RAT::DS::EV* rev = rds->GetEV(iEV);
          evNhits->Fill(rev->GetNhits()); //fill the Nhit histogram
        }
      rds = reader.NextEvent();
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
    evNhits->SetYTitle("Number of Events per 20 nhit bin");

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
