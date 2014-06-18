from ROOT import ROOT,gROOT,TCanvas,TFile,TH1D,TLegend,THStack,TPaveText
import sys

sys.path.append('../../plotProducers')
import PlotStyle

PlotStyle.setPlotStyle()

file = TFile.Open("DeltaPhi_Analysed.root")


h1dFiltBtiPerEvtId1Sl1 = file.Get("dttriganalyzer/h1dFilteredBtiHitsPerEvtId1Sl1")
h1dFiltBtiPerEvtId1Sl2 = file.Get("dttriganalyzer/h1dFilteredBtiHitsPerEvtId1Sl2")
h1dFiltBtiPerEvtId2Sl1 = file.Get("dttriganalyzer/h1dFilteredBtiHitsPerEvtId2Sl1")
h1dFiltBtiPerEvtId2Sl2 = file.Get("dttriganalyzer/h1dFilteredBtiHitsPerEvtId2Sl2")
h1dFiltBtiPerEvtBothIdSl1 = file.Get("dttriganalyzer/h1dFilteredBtiHitsPerEvtBothIdSl1")

h1dBtiPerEvtId1Sl1 = file.Get("dttriganalyzer/h1dBtiHitsPerEvtId1Sl1")
h1dBtiPerEvtId2Sl1 = file.Get("dttriganalyzer/h1dBtiHitsPerEvtId2Sl1")
h1dBtiPerEvtBothIdSl1 = file.Get("dttriganalyzer/h1dBtiHitsPerEvtBothIdSl1")

h1dBtiPerEvtId1Sl1.SetLineWidth(3)
h1dBtiPerEvtId2Sl1.SetLineWidth(3)
h1dBtiPerEvtBothIdSl1.SetLineWidth(3)

h1dFiltBtiPerEvtId1Sl1.SetLineWidth(3)
h1dFiltBtiPerEvtId1Sl2.SetLineWidth(3)
h1dFiltBtiPerEvtId2Sl1.SetLineWidth(3)
h1dFiltBtiPerEvtId2Sl2.SetLineWidth(3)
h1dFiltBtiPerEvtBothIdSl1.SetLineWidth(3)

canv = TCanvas("ID1",'ID1')
canv.cd(1).SetLogy()

h1dFiltBtiPerEvtId1Sl1.SetStats(0)
h1dFiltBtiPerEvtId1Sl1.SetTitle('Number of BX filtered HTRG per Event for Stat. 1, Track Id 1')
h1dFiltBtiPerEvtId1Sl1.GetXaxis().SetRangeUser(0,10)
h1dFiltBtiPerEvtId1Sl1.Draw()
h1dFiltBtiPerEvtId1Sl2.SetLineColor(ROOT.kRed)
h1dFiltBtiPerEvtId1Sl2.Draw('Same')
legend = TLegend(0.75,0.75,0.9,0.9)
legend.AddEntry(h1dFiltBtiPerEvtId1Sl1,'SL 1','l')
legend.AddEntry(h1dFiltBtiPerEvtId1Sl2,'SL 2','l')
legend.Draw()
canv.SaveAs("@sampleName@_h1dFilteredBtiHitsPerEvtID1.png")

canv2 = TCanvas("ID2",'ID2')
canv2.cd(1).SetLogy()
stack = THStack('btiFilteredID1Stack','Number of BX filtered HTRG per Event for ID 2')

h1dFiltBtiPerEvtId2Sl1.SetStats(0)
h1dFiltBtiPerEvtId2Sl1.SetTitle('Number of BX filtered HTRG per Event for Stat. 1, Track Id 2')
h1dFiltBtiPerEvtId2Sl1.GetXaxis().SetRangeUser(0,10)
#h1dFiltBtiPerEvtId2Sl1.Draw()
h1dFiltBtiPerEvtId2Sl2.SetLineColor(ROOT.kRed)
#h1dFiltBtiPerEvtId2Sl2.Draw('Same')

stack.Add(h1dFiltBtiPerEvtId2Sl1)
stack.Add(h1dFiltBtiPerEvtId2Sl2)

stack.Draw()
stack.GetXaxis().SetTitle(h1dFiltBtiPerEvtId2Sl1.GetXaxis().GetTitle())
stack.GetYaxis().SetTitle(h1dFiltBtiPerEvtId2Sl1.GetYaxis().GetTitle())
stack.GetXaxis().SetRangeUser(0,10)

legend = TLegend(0.75,0.75,0.9,0.9)
legend.AddEntry(h1dFiltBtiPerEvtId2Sl1,'SL 1','l')
legend.AddEntry(h1dFiltBtiPerEvtId2Sl2,'SL 2','l')
legend.Draw()

canv2.SaveAs("@sampleName@_h1dFilteredBtiHitsPerEvtID2.png")

##Draw a histogram stack for all SL1 information in Station 1
canv3 = TCanvas("SL1",'SL1')
canv3.cd(1).SetLogy()
stack = THStack('btiFilteredSl1Stack','Number of BX filtered HTRG per Event for Stat. 1, SL1')

h1dFiltBtiPerEvtBothIdSl1.SetFillColor(ROOT.kBlue)
h1dFiltBtiPerEvtBothIdSl1.SetLineColor(ROOT.kBlue)
h1dFiltBtiPerEvtBothIdSl1.SetFillStyle(1001)
h1dFiltBtiPerEvtId1Sl1.SetLineColor(ROOT.kRed)
h1dFiltBtiPerEvtId1Sl1.SetFillStyle(1001)
h1dFiltBtiPerEvtId1Sl1.SetFillColor(ROOT.kRed)
h1dFiltBtiPerEvtId2Sl1.SetLineColor(ROOT.kGreen)
h1dFiltBtiPerEvtId2Sl1.SetFillStyle(1001)
h1dFiltBtiPerEvtId2Sl1.SetFillColor(ROOT.kGreen)

h1dFiltBtiPerEvtBothIdSl1.GetXaxis().SetRangeUser(0,10)

stack.Add(h1dFiltBtiPerEvtBothIdSl1)
stack.Add(h1dFiltBtiPerEvtId1Sl1)
stack.Add(h1dFiltBtiPerEvtId2Sl1)

stack.Draw()
stack.GetXaxis().SetTitle(h1dFiltBtiPerEvtBothIdSl1.GetXaxis().GetTitle())
stack.GetYaxis().SetTitle(h1dFiltBtiPerEvtBothIdSl1.GetYaxis().GetTitle())
stack.GetXaxis().SetRangeUser(0,10)

#Legend
legend = TLegend(0.65,0.65,0.9,0.9)
legend.AddEntry(h1dFiltBtiPerEvtId1Sl1,'SimTrack ID 1','f')
legend.AddEntry(h1dFiltBtiPerEvtId2Sl1,'SimTrack ID 2','f')
legend.AddEntry(h1dFiltBtiPerEvtBothIdSl1,'Both SimTrack IDs','f')
legend.Draw()

#tList = stack.GetHists()
#entryCounter = 0
#for i in xrange(tList.GetSize()):
#    print tList.At(i).Integral()
#    entryCounter += tList.At(i).Integral()

text = TPaveText(0.65,0.45,0.9,0.65,'NDC')
#text.AddText('Seen Entries: %d' % entryCounter)
text.AddText('Efficiency per 50k Evts')
text.AddText('ID1: %.2f %%' % ((h1dFiltBtiPerEvtId1Sl1.Integral())/50000.*100))
text.AddText('ID2: %.2f %%' % ((h1dFiltBtiPerEvtId2Sl1.Integral())/50000.*100))
text.AddText('Both ID: %.2f %%' % ((h1dFiltBtiPerEvtBothIdSl1.Integral())/50000.*100))
text.SetBorderSize(1)
text.Draw()

sampleStringArray = '@sampleName@'.split('_')

text2 = TPaveText(0.65,0.4,0.9,0.45,'NDC')
text2.AddText('#Delta#phi = %s' % ( sampleStringArray[-2][-1] + '.' + sampleStringArray[-1] ))
text2.SetBorderSize(1)
text2.Draw()

canv3.Update()

canv3.SaveAs("@sampleName@_h1dFilteredBtiHitsPerEvtSL1.png")

print "Id 1 SL1: %.2f %%" % (h1dBtiPerEvtId1Sl1.Integral()/50000*100)
print "Id 2 SL1: %.2f %%" % (h1dBtiPerEvtId2Sl1.Integral()/50000*100)
print "Id 1 Filtered SL1: %.2f %%" % (h1dFiltBtiPerEvtId1Sl1.Integral()/50000*100)
#print "Id 1 Filtered SL2: %.2f %%" % (h1dFiltBtiPerEvtId1Sl2.Integral()/50000*100)
print "Id 2 Filtered SL1: %.2f %%" % (h1dFiltBtiPerEvtId2Sl1.Integral()/50000*100)
#print "Id 2 Filtered SL2: %.2f %%" % (h1dFiltBtiPerEvtId2Sl2.Integral()/50000*100)

