from ROOT import gROOT,gStyle

def setPlotStyle():
    gStyle.SetPadGridX(1)
    gStyle.SetPadGridY(1)
    gStyle.SetOptStat(1110)