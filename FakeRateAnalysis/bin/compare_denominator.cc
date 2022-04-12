#include "PhysicsTools/Utilities/macros/setTDRStyle.C"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"

#include <map>

void compare_denominator();

int main(int argc, char *argv[])
{
  compare_denominator();
}

void compare_denominator()
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
      canvases.back()->SetLogy();
      TLegend *leg = new TLegend(0.55, 0.40, 0.85, 0.7);
      bool first = true;
      for(auto dataset : datasets) {
	TFile *f = TFile::Open(Form("fakeRatePlots_%s_nPV%s.root", dataset.c_str(), pvCut.c_str()));
  	const TString graphName(Form("phoPt%s_denominator_varbin", region.c_str()));
	TH1D *hist = dynamic_cast<TH1D*>(f->Get(graphName));
	hist->Scale(1/hist->Integral());
	// const TString graphName(Form("bkgvspt%s_chIso5To10", region.c_str()));
	// TGraphAsymmErrors *hist = dynamic_cast<TGraphAsymmErrors*>(f->Get(graphName));
	//	hist->SetMinimum(0.0);
	hist->SetMaximum(graphMax[region]);
	hist->GetXaxis()->SetRangeUser(0., 800.);
	hist->SetMarkerStyle(styles[dataset]);
	hist->SetMarkerColor(colors[dataset]);
	hist->SetLineColor(colors[dataset]);
	hist->SetTitle(";p_{T} (GeV);Denominator (normalized)");
	if(first) hist->Draw("L");
	else hist->Draw("L same");
	first = false;
	leg->AddEntry(hist, datasetLabel[dataset].c_str(), "LPE");
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
      TString filename(Form("plots/compare_denominator_%s_%s.pdf", region.c_str(), pvCut.c_str()));
      filename.ReplaceAll("-", "to");
      canvases.back()->Print(filename);
    }
  }    
    
}
