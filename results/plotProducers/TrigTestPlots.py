from ROOT import gROOT,TCanvas,TFile,TH1D

gROOT.SetStyle("Pub")

canv = TCanvas("Test")
canv.Draw()

file = TFile.Open("../DeltaPhiGunPt100dPhi3_0/DeltaPhi_Analysed.root")

h1dw2m  = file.Get("dttriganalyzer/histBtiTrgWhm2Stat4")
h1dw1m  = file.Get("dttriganalyzer/histBtiTrgWhm1Stat1")
h1dw0   = file.Get("dttriganalyzer/histBtiTrgWh0Stat1")
h1dw1p  = file.Get("dttriganalyzer/histBtiTrgWhp1Stat1")
h1dw2p  = file.Get("dttriganalyzer/histBtiTrgWhp2Stat4")


h1dw2m.Add(h1dw1m)
h1dw2m.Add(h1dw0)
h1dw2m.Add(h1dw1p)
h1dw2m.Add(h1dw2p)

h1dw2m.SetTitle("Hits per Station")
h1dw2m.GetXaxis().SetTitle("Sector")
h1dw2m.GetYaxis().SetTitle("# Entries")

h1dw2m.Draw()