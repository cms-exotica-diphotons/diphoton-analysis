import ROOT as r
import importlib
tdrStyle = importlib.import_module('diphoton-analysis.FakeRateAnalysis.setTDRStyle')

directory = '/eos/uscms/store/user/cawest/fake_rate_2EEbins/'

template_var = 'sieie'
pt_bin = 'pt130To150'
iso_sideband = 'chIso5To10'
years = [2016, 2017, 2018]
regions = ['EB', 'EE1', 'EE2']
datasets = ['diphoton_fake_rate_real_templates_all_GGJets_GJets', 'jetht', 'doublemuon']
colors = {2016: r.kBlack, 2017: r.kBlue, 2018: r.kRed}
files = []
hists = []

tdrStyle.setTDRStyle()
r.gROOT.SetBatch()

for region in regions:
    for dataset in datasets:
        c = r.TCanvas()
        leg = r.TLegend(0.6, 0.6, 0.9, 0.9)
        leg.SetBorderSize(0)
        leg.SetFillColor(0)
        hist_max = 0.
        for year in years:
            filename = '{}/{}_fakerate_{}_nPV0-200_newDenomDef.root'.format(directory, dataset, year)
            histname = '{}{}_faketemplate_{}_{}'.format(template_var, region, pt_bin, iso_sideband)
            # real templates have a different naming convention
            if 'real' in dataset:
                filename = '{}/{}_{}_nPV0-200_MiniAOD_histograms.root'.format(directory, dataset, year)
                histname = '{}{}_realtemplate_{}'.format(template_var, region, pt_bin)
            files.append(r.TFile(filename))
            hists.append(files[-1].Get(histname))
            hists[-1].SetMarkerColor(colors[year])
            hists[-1].SetLineColor(colors[year])
            hists[-1].GetXaxis().SetTitle('#sigma_{i#eta i#eta}')
            hists[-1].GetYaxis().SetTitle('Normalized entries')
            leg.AddEntry(hists[-1], str(year), 'L')
            max = hists[-1].GetMaximum()
            if max > hist_max:
                hist_max = max
                hists[-1].GetYaxis().SetRangeUser(0, 1.3*hist_max)
            if year == years[0]:
                hists[-1].Draw('hist')
                if region == 'EB':
                    hists[-1].GetXaxis().SetRangeUser(0, 0.025)
            else:
                hists[-1].Draw('hist same')
            leg.Draw()
            out_filename = 'plots/{}_comparison_{}_{}_{}_{}.pdf'.format(template_var, region, dataset, pt_bin, iso_sideband)
        c.Print(out_filename)
