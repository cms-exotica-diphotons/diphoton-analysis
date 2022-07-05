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
        basename=in_filename.rsplit("/",1)[1].split("_TuneCP2")[0]
        fTree=tfileIn.Get("diphoton/fTree")
        h_pt125=tfileIn.Get("diphoton/h_pt125")
        h_photonID=tfileIn.Get("diphoton/h_photonID")
        h_eta=tfileIn.Get("diphoton/h_eta")
        h_mass = ROOT.TH1F("h_mass","h_mass",1,0,2)
        h_deltaR = ROOT.TH1F("h_deltaR","h_deltaR",1,0,2)
        h_HLT = ROOT.TH1F("h_HLT","h_HLT",1,0,2)

        project(fTree,h_mass,"1","isGood*(Photon1.pt>125 && Photon2.pt>125)*((Diphoton.Minv > 230 && Diphoton.isEBEB)||(Diphoton.Minv > 330 && Diphoton.isEBEE)||(Diphoton.Minv > 330 && Diphoton.isEEEB))")
        project(fTree,h_deltaR,"1","isGood*(Photon1.pt>125 && Photon2.pt>125)*((Diphoton.Minv > 230 && Diphoton.isEBEB)||(Diphoton.Minv > 330 && Diphoton.isEBEE)||(Diphoton.Minv > 330 && Diphoton.isEEEB))*(Diphoton.deltaR > 0.45)")
        project(fTree,h_HLT,"1","isGood*(Photon1.pt>125 && Photon2.pt>125)*((Diphoton.Minv > 230 && Diphoton.isEBEB)||(Diphoton.Minv > 330 && Diphoton.isEBEE)||(Diphoton.Minv > 330 && Diphoton.isEEEB))*(Diphoton.deltaR > 0.45)*(HLT_DoublePhoton70>0 || HLT_ECALHT800>0)")

        h_cutflow = ROOT.TH1F("h_cutflow",basename,6,0,6)
        h_cutflow.GetXaxis().SetBinLabel(1,"pt125")
        h_cutflow.GetXaxis().SetBinLabel(2,"photonID")
        h_cutflow.GetXaxis().SetBinLabel(3,"EBEB||EBEE")
        h_cutflow.GetXaxis().SetBinLabel(4,"M>230(330)")
        h_cutflow.GetXaxis().SetBinLabel(5,"dR>0.45")
        h_cutflow.GetXaxis().SetBinLabel(6,"HLT")
        h_cutflow.GetXaxis().SetLabelSize(0.055)

        h_cutflow.SetBinContent(1,float(h_pt125.Integral())    /float(fTree.GetEntries()))
        h_cutflow.SetBinContent(2,float(h_photonID.Integral()) /float(fTree.GetEntries()))
        h_cutflow.SetBinContent(3,float(h_eta.Integral())      /float(fTree.GetEntries()))
        h_cutflow.SetBinContent(4,float(h_mass.Integral())     /float(fTree.GetEntries()))
        h_cutflow.SetBinContent(5,float(h_deltaR.Integral())   /float(fTree.GetEntries()))
        h_cutflow.SetBinContent(6,float(h_HLT.Integral())      /float(fTree.GetEntries()))

        ROOT.gStyle.SetOptStat(0)
        c1 = ROOT.TCanvas()
        h_cutflow.Draw()
        h_cutflow.GetYaxis().SetRangeUser(0.3,1)
        h_cutflow.GetYaxis().SetTitle("Efficiency")
        c1.SaveAs("output/plots/cutFlow/cutFlow_%s.png"%(basename))
        tfileIn.Close()
