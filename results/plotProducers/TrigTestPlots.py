from ROOT import gROOT,TCanvas,TFile,TH1D

import PlotStyle

PlotStyle.setPlotStyle()

file = TFile.Open("../DeltaPhiGunPt100dPhi3_0/DeltaPhi_Analysed.root")

h1dw2m  = file.Get("dttriganalyzer/histBtiTrgWhm2Stat4")
h1dw1m  = file.Get("dttriganalyzer/histBtiTrgWhm1Stat1")
h1dw0   = file.Get("dttriganalyzer/histBtiTrgWh0Stat1")
h1dw1p  = file.Get("dttriganalyzer/histBtiTrgWhp1Stat1")
h1dw2p  = file.Get("dttriganalyzer/histBtiTrgWhp2Stat4")

h1dw2mFilter  = file.Get("dttriganalyzer/histBtiTrgWhm2Stat4BxFilt")
h1dw1mFilter  = file.Get("dttriganalyzer/histBtiTrgWhm1Stat1BxFilt")
h1dw0Filter   = file.Get("dttriganalyzer/histBtiTrgWh0Stat1BxFilt")
h1dw1pFilter  = file.Get("dttriganalyzer/histBtiTrgWhp1Stat1BxFilt")
h1dw2pFilter  = file.Get("dttriganalyzer/histBtiTrgWhp2Stat4BxFilt")

h1dFiltBtiPerEvt = file.Get("dttriganalyzer/h1dFilteredBtiHitsPerEvt")

h1dw1m.Add(h1dw0)
h1dw1m.Add(h1dw1p)
h1dw1m.SetTitle("Hits per Sector")

h1dw1mFilter.Add(h1dw0Filter)
h1dw1mFilter.Add(h1dw1pFilter)
h1dw1mFilter.SetTitle("Hits per Sector, BX 16")

#h1dw1m.GetXaxis().SetTitle("Sector")
#h1dw1m.GetYaxis().SetTitle("# Entries")

canv = TCanvas("Test")
h1dw1m.SetLineWidth(3)
h1dw1m.Draw()
canv.SaveAs("h1dBtiPerSect.png")


canv = TCanvas("Test")
h1dw1mFilter.SetLineWidth(3)
h1dw1mFilter.Draw()
canv.SaveAs("h1dBtiPerSectFilter.png")

canv = TCanvas("Test")
h1dFiltBtiPerEvt.SetLineWidth(3)
h1dFiltBtiPerEvt.Draw()
canv.SaveAs("h1dFilteredBtiHitsPerEvt.png")

print "Unfiltered: %f" % (h1dw1m.Integral())
print "Filtered: %f" % (h1dw1mFilter.Integral())