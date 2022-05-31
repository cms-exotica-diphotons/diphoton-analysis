#include "PhysicsTools/Utilities/macros/setTDRStyle.C"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"

#include <iostream>
#include <map>

void compare_pv_bin(int year);

int main(int argc, char *argv[])
{
  int data_year;

  if(argc!=2) {
    std::cout << "Syntax: compare_pv_bin.exe [2015/2016/2017/2018]" << std::endl;
    return -1;
  }
  else {
    data_year = std::atoi(argv[1]);
    if(data_year != 2015 and data_year != 2016 and data_year != 2017 and data_year != 2018) {
      std::cout << "Only '2015', '2016', '2017', and '2018' are allowed years." << std::endl;
      return -1;
    }
  }

  compare_pv_bin(data_year);
}

void compare_pv_bin(int year)
{
  setTDRStyle();

  const std::string iso("chIso5To10");

  std::vector<std::string> datasets = {"jetht", "doublemuon"};
  std::vector<std::string> regions = {"EB", "EE", "EE1", "EE2"};
  std::vector<std::string> pvCuts = {"0-22", "23-27"};
  if(year == 2016) {
    pvCuts.push_back("28-200");
  }
  else {
    pvCuts.push_back("28-32");
    pvCuts.push_back("33-37");
    pvCuts.push_back("38-200");
  }

  std::vector<TCanvas*> canvases;
  std::map<std::string, int> colors;
  colors["jetht"] = kBlue;
  colors["doublemuon"] = kBlack;
  std::map<std::string, std::string> isoLabel;
  isoLabel["chIso5To10"] = "5 < Iso_{Ch} < 10 GeV";
  std::map<std::string, std::string> datasetLabel;
  datasetLabel["jetht"] = std::to_string(year) + " JetHT";
  datasetLabel["doublemuon"] = std::to_string(year) + " DoubleMuon";
  std::map<std::string, double> graphMax;
  graphMax["EB"] = 0.3;
  graphMax["EE"] = 0.9;
  graphMax["EE1"] = 0.9;
  graphMax["EE2"] = 0.9;

  for(auto pvCut : pvCuts) {
    for(auto region : regions) {
      canvases.push_back(new TCanvas);
      TLegend *leg = new TLegend(0.55, 0.45, 0.9, 0.7);
      bool first = true;
      for(auto dataset : datasets) {
	TFile *f = TFile::Open(Form("fakeRatePlots_%s_%d_nPV%s.root", dataset.c_str(), year, pvCut.c_str()));
	const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
	TGraphAsymmErrors *gr = dynamic_cast<TGraphAsymmErrors*>(f->Get(graphName));
	gr->SetMinimum(0.0);
	gr->SetMaximum(graphMax[region]);
	gr->GetXaxis()->SetRangeUser(0., 800.);
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
      else if (region == "EE") label->DrawLatexNDC(0.55, 0.8, "ECAL endcap");
      else if (region == "EE1") label->DrawLatexNDC(0.55, 0.8, "EE (low eta)");
      else if (region == "EE2") label->DrawLatexNDC(0.55, 0.8, "EE (high eta)");
      //      label->DrawLatexNDC(0.55, 0.75, isoLabel[iso].c_str());
      TString filename(Form("plots/compare_pv_%s_%d_%s.pdf", region.c_str(), year, pvCut.c_str()));
      filename.ReplaceAll("-", "to");
      canvases.back()->Print(filename);
    }
  }    
}
