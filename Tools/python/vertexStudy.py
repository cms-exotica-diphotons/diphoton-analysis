#!/usr/bin/env python
import ROOT
import argparse

parser = argparse.ArgumentParser(description='')
parser.add_argument('in_filenames',nargs="+",help='input filenames')
args = parser.parse_args()

def project(tree, h, var, cut):
    print 'projecting var: %s, cut: %s from tree: %s into hist: %s'%(var, cut, tree.GetName(), h.GetName())
    tree.Project(h.GetName(),var,cut)


if __name__ == "__main__":

    for in_filename in args.in_filenames:
        tfileIn = ROOT.TFile.Open(in_filename)
        thetree=tfileIn.Get("HighMassDiphoton")
        basename=in_filename.rsplit("/",1)[1].split(".root")[0]

        h_vzdiff = ROOT.TH1D("h_vzdiff",basename,100, 0, 20)

        project(thetree, h_vzdiff, "abs(gen1vz-pvvz)", "")
        nTotal = h_vzdiff.Integral()
        n_dz10 = h_vzdiff.Integral(h_vzdiff.FindBin(0),h_vzdiff.FindBin(10))
        print 'dz < 10 = %d/%d (%.1f)'%(n_dz10, nTotal, (n_dz10/nTotal)*100)

        c1 = ROOT.TCanvas()
        c1.SetLogy()
        h_vzdiff.Draw()
        h_vzdiff.GetXaxis().SetTitle("|z_{gen}-z_{reco}| [mm]")
        leg = ROOT.TLegend(0.4,0.6,0.7,0.7)
        leg.SetHeader("dz < 10mm = %d/%d (%.1f%%)"%(n_dz10, nTotal, (n_dz10/nTotal)*100))
        leg.SetBorderSize(0)
        leg.SetTextSize(0.05)
        leg.Draw()
        c1.SaveAs("output/plots/vertexCheck/vertex_%s.png"%(basename))

        tfileIn.Close()
