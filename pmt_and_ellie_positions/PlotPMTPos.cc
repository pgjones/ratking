#include <RAT/DS/Root.hh>
#include <RAT/DSReader.hh>
#include <TH1D.h>
#include <TGraph2D.h> 
#include <TTree.h>
#include <TFile.h>
 
using namespace std;
 
void PlotPMTPos( const char* inFile ){
  // Read in the root file
  RAT::DSReader reader(inFile);
  RAT::DS::PMTProperties* pmtProp=reader.GetRun()->GetPMTProp();
  RAT::DS::ELLIEProperties* ellieProp = reader.GetRun()->GetELLIEProp();

  // Prepare the plots 
  TGraph2D* pmtPositions = new TGraph2D();
  TGraph2D* telliePositions = new TGraph2D();
  TGraph2D* amelliePositions = new TGraph2D();
  TGraph2D* smelliePositions = new TGraph2D();

  int graphPoint = 0;
  // Get the PMTProperties class instance

  // Loop over the PMTs
  for( int ipmt = 0; ipmt < int(pmtProp->GetPMTCount()); ipmt++ ){
    if (pmtProp->GetType(ipmt)==1){
      pmtPositions->SetPoint(graphPoint++, pmtProp->GetPos(ipmt).x(), pmtProp->GetPos(ipmt).y(), pmtProp->GetPos(ipmt).z());
    }
  }

  graphPoint = 0;
  for (int itellie=0; itellie<int(ellieProp->GetTELLIECount()); itellie++){
    telliePositions->SetPoint(graphPoint++, ellieProp->GetTELLIEPos(itellie).x(), ellieProp->GetTELLIEPos(itellie).y(), ellieProp->GetTELLIEPos(itellie).z());
  }
  
  graphPoint = 0;
  for (int iamellie=0; iamellie<int(ellieProp->GetAMELLIECount()); iamellie++){
    amelliePositions->SetPoint(graphPoint++, ellieProp->GetAMELLIEPos(iamellie).x(), ellieProp->GetAMELLIEPos(iamellie).y(), ellieProp->GetAMELLIEPos(iamellie).z());
  }
  
  graphPoint = 0;
  for (int ismellie=0; ismellie<int(ellieProp->GetSMELLIECount()); ismellie++){
    smelliePositions->SetPoint(graphPoint++, ellieProp->GetSMELLIEPos(ismellie).x(), ellieProp->GetSMELLIEPos(ismellie).y(), ellieProp->GetSMELLIEPos(ismellie).z());
  }
  
  // Make the plots pretty
  pmtPositions->SetMarkerColor(kBlack);
  telliePositions->SetMarkerColor(kYellow);
  telliePositions->SetMarkerStyle(8);
  amelliePositions->SetMarkerColor(kRed);
  amelliePositions->SetMarkerStyle(8);
  smelliePositions->SetMarkerColor(kBlue);
  smelliePositions->SetMarkerStyle(8);

  // Draw the plots
  pmtPositions->Draw("AP");
  telliePositions->Draw("P SAME");
  amelliePositions->Draw("P SAME");
  smelliePositions->Draw("P SAME");
}
