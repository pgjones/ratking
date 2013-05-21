#!usr/bin/env python

import ROOT
import rat
import sys
 
# Read in the root file
# Prepare the plots 
pmtPositions = ROOT.TGraph2D()
telliePositions = ROOT.TGraph2D()
amelliePositions = ROOT.TGraph2D()
smelliePositions = ROOT.TGraph2D()

for ds in rat.dsreader(sys.argv[1]):
  pmtProp=ds[1].GetPMTProp()
  for pmt in range (0,pmtProp.GetPMTCount()):
    if (pmtProp.GetType(pmt)==1):    
      pmtPositions.SetPoint(pmt, pmtProp.GetPos(pmt).x(), pmtProp.GetPos(pmt).y(), pmtProp.GetPos(pmt).z())

  ellieProp=ds[1].GetELLIEProp()
  for tellie in range (0,ellieProp.GetTELLIECount()):
    telliePositions.SetPoint(tellie, ellieProp.GetTELLIEPos(tellie).x(), ellieProp.GetTELLIEPos(tellie).y(), ellieProp.GetTELLIEPos(tellie).z())

  for amellie in range (0,ellieProp.GetAMELLIECount()):
    amelliePositions.SetPoint(amellie, ellieProp.GetAMELLIEPos(amellie).x(), ellieProp.GetAMELLIEPos(amellie).y(), ellieProp.GetAMELLIEPos(amellie).z())

  for smellie in range (0,ellieProp.GetSMELLIECount()):
    smelliePositions.SetPoint(smellie, ellieProp.GetSMELLIEPos(smellie).x(), ellieProp.GetSMELLIEPos(smellie).y(), ellieProp.GetSMELLIEPos(smellie).z())

#  Make the plots pretty
pmtPositions.SetMarkerColor(ROOT.kBlack)
telliePositions.SetMarkerColor(ROOT.kYellow);
telliePositions.SetMarkerStyle(8);
amelliePositions.SetMarkerColor(ROOT.kRed);
amelliePositions.SetMarkerStyle(8);
smelliePositions.SetMarkerColor(ROOT.kBlue);
smelliePositions.SetMarkerStyle(8);

# Draw the plots
pmtPositions.Draw("AP")
telliePositions.Draw("P SAME");
amelliePositions.Draw("P SAME");
smelliePositions.Draw("P SAME");
raw_input("RET to exit")
