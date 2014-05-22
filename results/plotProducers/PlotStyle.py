from ROOT import gROOT,gStyle

def setPlotStyle():
    gROOT.SetStyle("Pub")
    gStyle.SetPadGridX(1)
    gStyle.SetPadGridY(1)
    gStyle.SetHistLineWidth(3)