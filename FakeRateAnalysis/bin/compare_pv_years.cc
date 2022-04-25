#include "PhysicsTools/Utilities/macros/setTDRStyle.C"

#include "TAxis.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TLatex.h"
#include "TLegend.h"

#include <map>

void compare_pv_years();

int main(int argc, char *argv[])
{
  compare_pv_years();
}

void compare_pv_years()
{
  setTDRStyle();

  const std::string iso("chIso5To10");

  std::vector<std::string> datasets = {"jetht_2017", "doublemuon_2017", "jetht_2018", "doublemuon_2018"};
  std::vector<std::string> regions = {"EB", "EE"};
  std::vector<std::string> pvCuts = {"0-22", "23-27", "28-32", "33-37", "38-200"};

  std::vector<TCanvas*> canvases;
  std::map<std::string, int> colors;
  colors["jetht_2017"] = kBlue;
  colors["doublemuon_2017"] = kBlack;
  colors["jetht_2018"] = kBlue;
  colors["doublemuon_2018"] = kBlack;
  std::map<std::string, int> styles;
  styles["jetht_2017"] = kFullCircle;
  styles["doublemuon_2017"] = kFullCircle;
  styles["jetht_2018"] = kOpenCircle;
  styles["doublemuon_2018"] = kOpenCircle;
  std::map<std::string, std::string> isoLabel;
  isoLabel["chIso5To10"] = "5 < Iso_{Ch} < 10 GeV";
  std::map<std::string, std::string> datasetLabel;
  datasetLabel["jetht_2017"] = "JetHT (2017)";
  datasetLabel["doublemuon_2017"] = "DoubleMuon (2017)";
  datasetLabel["jetht_2018"] = "JetHT (2018)";
  datasetLabel["doublemuon_2018"] = "DoubleMuon (2018)";
  std::map<std::string, double> graphMax;
  graphMax["EB"] = 0.3;
  graphMax["EE"] = 0.65;

  for(auto pvCut : pvCuts) {
    for(auto region : regions) {
      canvases.push_back(new TCanvas);
      TLegend *leg = new TLegend(0.55, 0.40, 0.85, 0.7);
      bool first = true;
      for(auto dataset : datasets) {
	TFile *f = TFile::Open(Form("fakeRatePlots_%s_nPV%s.root", dataset.c_str(), pvCut.c_str()));
	const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
	TGraphAsymmErrors *gr = dynamic_cast<TGraphAsymmErrors*>(f->Get(graphName));
	gr->SetMinimum(0.0);
	gr->SetMaximum(graphMax[region]);
	gr->GetXaxis()->SetRangeUser(0., 800.);
	gr->SetMarkerStyle(styles[dataset]);
	gr->SetMarkerColor(colors[dataset]);
	gr->SetLineColor(colors[dataset]);
	gr->SetTitle(";p_{T} (GeV);Fake rate");
	if(first) gr->Draw("ALP");
	else gr->Draw("LP same");
	first = false;
	leg->AddEntry(gr, datasetLabel[dataset].c_str(), "LPE");
      }
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();

      TLatex *label = new TLatex;
      TString cut(pvCut.c_str());
      cut.ReplaceAll("-", " #leq n_{PV} #leq ");
      label->DrawLatexNDC(0.55, 0.85, cut);
      if (region == "EB") label->DrawLatexNDC(0.55, 0.8, "ECAL barrel");
      else label->DrawLatexNDC(0.55, 0.8, "ECAL endcap");
      //      label->DrawLatexNDC(0.55, 0.75, isoLabel[iso].c_str());
      TString filename(Form("plots/compare_pv_years_%s_%s.pdf", region.c_str(), pvCut.c_str()));
      filename.ReplaceAll("-", "to");
      canvases.back()->Print(filename);
    }
  }    

  // TFile *f_jetht = TFile::Open("../../DataFakeRateAnalysis/analysis/jetht_fakerate_Run2018Ctest_nPV0-22_newDenomDef.root");
  // TH1D *h_jetht = dynamic_cast<TH1D*>(f_jetht->Get("npv"));
  // TFile *f_doublemuon = TFile::Open("../../DataFakeRateAnalysis/analysis/doublemuon_fakerate_Run2018Ctest_nPV0-22_newDenomDef.root");
  // TH1D *h_doublemuon = dynamic_cast<TH1D*>(f_doublemuon->Get("npv"));
  // h_jetht->Scale(1/h_jetht->Integral());
  // h_jetht->GetXaxis()->SetRangeUser(0, 150);
  // h_jetht->SetTitle(";n_{PV};Normalized events");
  // h_doublemuon->Scale(1/h_doublemuon->Integral());
  // h_doublemuon->SetLineColor(kRed);
    
}
