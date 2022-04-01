import ROOT as r

xsec = {"500To1000_TuneCUEP8M1": 0.109534, "1000To2000_TuneCUEP8M1": 0.0101229, "2000To4000_TuneCUEP8M1": 0.000474448, "4000To13000_TuneCUEP8M1": 5.505e-06,
        "500To1000_TuneCP2": 1.344e-01, "1000To2000_TuneCP2": 1.357e-02, "2000To4000_TuneCP2": 6.736e-04, "4000To13000_TuneCP2": 8.627e-06}
n_entries = {"500To1000_TuneCUEP8M1": 814000.0, "1000To2000_TuneCUEP8M1": 400000.0, "2000To4000_TuneCUEP8M1": 199400.0, "4000To13000_TuneCUEP8M1": 94000,
             "500To1000_TuneCP2": 983900.0, "1000To2000_TuneCP2": 392000.0, "2000To4000_TuneCP2": 200000.0, "4000To13000_TuneCP2": 100000}

f = {}
h = {}

for key in xsec.keys():
    f[key] = r.TFile("diphoton_mass_" + key + ".root")

out_file = r.TFile("tune_ratio.root", "recreate")

regions = ["all", "BB", "BE"]
bins = ["500To1000", "1000To2000", "2000To4000", "4000To13000"]
hist_types = ["TuneCUEP8M1", "TuneCUEP8M1_weighted", "TuneCP2"]
for region in regions:
    for key in f.keys():
        if "TuneCUEP8M1" in key:
            h[key + "_weighted"] = f[key].Get("gen/diphoton_mass_weighted_" + region)
            h[key + "_weighted"].Scale(xsec[key]/n_entries[key])
        h[key] = f[key].Get("gen/diphoton_mass_" + region)
        h[key].Scale(xsec[key]/n_entries[key])
        print(key, h[key].Integral())

    for hist_type in hist_types:
        for bin in bins:
            hist_name = bin + "_" + hist_type
            # clone first histogram of a given type; add the rest
            if hist_type not in h.keys():
                print(hist_name)
                h[hist_type] = h[hist_name].Clone()
            else:
                print(hist_name)
                h[hist_type].Add(h[hist_name])

    ratio = h["TuneCP2"].Clone("ratio_" + region)
    ratio.Divide(h["TuneCUEP8M1"])
    ratio.SetTitle(";m_{#gamma#gamma} (GeV);#sigma(CP2)/#sigma(CUEP8M1)")

    c = r.TCanvas("c", "c")
    ratio.GetYaxis().SetRangeUser(0., 5.)
    ratio.Draw()
    ratio.Write()

    ratio_weighted = h["TuneCP2"].Clone("ratio_weighted_" + region)
    ratio_weighted.Divide(h["TuneCUEP8M1_weighted"])
    ratio_weighted.SetMarkerColor(r.kRed)
    ratio_weighted.SetLineColor(r.kRed)
    ratio_weighted.Draw("same")
    ratio_weighted.Fit("pol0")
    ratio_weighted.Write()

    leg = r.TLegend(0.3, 0.5, 0.6, 0.85)
    leg.AddEntry(ratio, "Unweighted")
    leg.AddEntry(ratio_weighted, "Weighted to PDF from CP2")
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.Draw()

    c.Print("tune_ratio_" + region + ".pdf")
    c.Print("tune_ratio_" + region + ".png")

out_file.Close()
    
