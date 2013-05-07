#! /usr/bin/env python

import ROOT
import rat
import sys

#define the histograms
evNhits = ROOT.TH1F("evNits", "evNhits", 150, 0, 3000)
MCPMThits = ROOT.TH1F("MCPMThits", "MCPMThits", 150, 0, 3000)
MCPECount = ROOT.TH1F("MCPECount", "MCPECount", 150, 0, 3000)

#read in the root file, which should be the first argument of the script
for ds in rat.dsreader(sys.argv[1]):

    for iEV in range(0, ds.GetEVCount()):
         evNhits.Fill(ds.GetEV(iEV).GetNhits()) #fill Nhits, retriggers included

    MCPECount.Fill(ds.GetMC().GetNumPE()) #fill the MC photo electron histo
    MCPMThits.Fill(ds.GetMC().GetMCPMTCount()) #fill the MC PMT hits histo

#make things pretty
#set the line width larger than default
evNhits.SetLineWidth(2)
MCPMThits.SetLineWidth(2)
MCPECount.SetLineWidth(2)

#Set the line color
evNhits.SetLineColor(ROOT.kBlack)
MCPMThits.SetLineColor(ROOT.kRed)
MCPECount.SetLineColor(ROOT.kBlue)

#set the axis titles
evNhits.SetXTitle("Number of Nhits, MCPMThits, or MCPEs")
evNhits.SetYTitle("Number of Events")

#get rid of the title and stats box
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)

#draw the histograms
evNhits.Draw()
MCPMThits.Draw("same")
MCPECount.Draw("same")

#make a legend
leg = ROOT.TLegend(0.15,0.65,0.48,0.85)
#make it pretty
leg.SetFillColor(0)
leg.SetBorderSize(0)
#add the histos to the legend
leg.AddEntry(evNhits)
leg.AddEntry(MCPMThits)
leg.AddEntry(MCPECount)

leg.Draw("same")
raw_input("RET to exit")
