from ROOT import gROOT,TCanvas,TFile,TH1D

import PlotStyle

PlotStyle.setPlotStyle()

canv = TCanvas("Test")
canv.Draw()

file = TFile.Open("../DeltaPhiGunPt100dPhi3_0/DeltaPhi_Analysed.root")

h1dw2m  = file.Get("dttriganalyzer/histBtiTrgWhm2Stat4")
h1dw1m  = file.Get("dttriganalyzer/histBtiTrgWhm1Stat1")
h1dw0   = file.Get("dttriganalyzer/histBtiTrgWh0Stat1")
h1dw1p  = file.Get("dttriganalyzer/histBtiTrgWhp1Stat1")
h1dw2p  = file.Get("dttriganalyzer/histBtiTrgWhp2Stat4")


h1dw1m.Add(h1dw0)
h1dw1m.Add(h1dw1p)

h1dw1m.SetTitle("Hits per Station")
h1dw1m.GetXaxis().SetTitle("Sector")
h1dw1m.GetYaxis().SetTitle("# Entries")

h1dw1m.SetLineWidth(3)
h1dw1m.Draw()
canv.Update()

canv.SaveAs("h1dBtiPerSect.png")
print h1dw1m.Integral()