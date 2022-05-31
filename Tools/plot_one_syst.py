import ROOT as r

sample = "gg"
syst = "eff"

regions = ["BB", "BE"]
years = [2016, 2017, 2018]

hists = []

c = r.TCanvas("c", "c")
c.Divide(3, 2)
index = 0
for region in regions:
    for year in years:
        index += 1
        c.cd(index)
        c.SetLogy()
        filename = "datacards/Minv_histos_{}_{}.root".format(region, year)
        f = r.TFile(filename)

        hist_name = region + "/" + sample
        print("Getting hist " + hist_name)
        hists.append(f.Get(hist_name))
        hists[-1].SetDirectory(0)
        hists[-1].SetTitle(";m_{#gamma#gamma} (GeV);Events / 50 GeV")
        hists[-1].Draw("hist")

        hist_name_up = hist_name + "_" + syst + "Up"
        hists.append(f.Get(hist_name_up))
        hists[-1].SetDirectory(0)
        hists[-1].SetLineColor(r.kRed)
        hists[-1].Draw("hist same")

        hist_name_down = hist_name + "_" + syst + "Down"
        hists.append(f.Get(hist_name_down))
        hists[-1].SetDirectory(0)
        hists[-1].SetLineColor(r.kBlue)
        hists[-1].Draw("hist same")

out_file = "plots/syst_" + sample + "_" + syst 
c.Print(out_file + ".pdf")
c.Print(out_file + ".png")
