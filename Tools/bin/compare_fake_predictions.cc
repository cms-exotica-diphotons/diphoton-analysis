#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"

#include <string>
#include <vector>

void compare_fake_predictions();

int main()
{
  compare_fake_predictions();

  return 0;
}

void compare_fake_predictions()
{
  setTDRStyle();

  std::vector<std::string> fake_types({"average", "jetht", "doublemuon"});
  std::vector<std::string> regions({"BB", "BE"});
  std::vector<int> years({2018, 2017, 2016});
  std::vector<TFile*> files;
  std::vector<std::string> hist_names({"Minv", "pt1", "pt2", "qt", "absDeltaPhi", "deltaEta", "deltaR", "scEta1", "phi1", "scEta2", "phi2"});
  std::map<std::string, std::string> pretty_names;
  pretty_names["Minv"] = "m_{#gamma#gamma} (GeV)";
  pretty_names["pt1"] = "p_{T1} (GeV)";
  pretty_names["pt2"] = "p_{T2} (GeV)";
  pretty_names["qt"] = "q_{T,#gamma#gamma} (GeV)";
  pretty_names["absDeltaPhi"] = "|#Delta#phi|";
  pretty_names["deltaEta"] = "#Delta#eta";
  pretty_names["scEta1"] = "#eta_{SC,1}";
  pretty_names["phi1"] = "#phi_{1}";
  pretty_names["scEta2"] = "#eta_{SC,2}";
  pretty_names["phi2"] = "#phi_{2}";

  std::vector<TH1D*> hists;
  std::vector<TH1D*> ratios;
  std::vector<TCanvas*> canvases;
  std::map<int, int> color;
  color[2016] = kBlack;
  color[2017] = kBlue;
  color[2018] = kRed;
  
  for(const auto& fake_type : fake_types) {
    for(const auto& region : regions) {
      for(const auto& hist_name : hist_names) {
	TH1D* first_year = nullptr;
	std::string id_str = hist_name + "_" + region + "_" + fake_type;
	canvases.push_back(new TCanvas(id_str.c_str(), id_str.c_str(), 600, (int)((1./0.7)*600)));
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1,1);
	pad1->SetBottomMargin(0);
	pad1->Draw();

	TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1,0.3);
	pad2->SetBottomMargin(0.25);
	pad2->SetTopMargin(0);
	pad2->Draw();


	TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.9);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	TLatex *lat = new TLatex;
	double max = 0;
	for(int year : years) {
	  pad1->cd();
	  files.push_back(TFile::Open(Form("data/fakes_%d_%s.root", year, fake_type.c_str())));
	  hists.push_back((TH1D*)files.back()->Get(Form("%s/%s_%s", region.c_str(), region.c_str(), hist_name.c_str())));
	  hists.back()->SetDirectory(nullptr);
	  hists.back()->SetLineColor(color[year]);
	  hists.back()->SetMarkerColor(color[year]);
	  hists.back()->Scale(1/luminosity[std::to_string(year)]);
	  // scale down 2017 and 2018 for ease of visualization
	  if(year == 2017 or year == 2018) hists.back()->Scale(0.5);
	  hists.back()->GetXaxis()->SetTitle(pretty_names[hist_name].c_str());
	  hists.back()->GetYaxis()->SetTitle("Entries/(1 fb^{-1})");
	  if(!first_year) {
	    hists.back()->Draw();
	    first_year = hists.back();
	  }
	  else hists.back()->Draw("same");
	  double histMax = hists.back()->GetMaximum();
	  if(histMax > max) {
	    max = histMax;
	    hists.back()->GetYaxis()->SetRangeUser(0, 1.25*max);
	  }
	  std::string year_str = std::to_string(year);
	  // scale down 2017 and 2018 for ease of visualization
	  if(year!=2016) {
	    year_str += "/2";
	  }
	  leg->AddEntry(hists.back(), year_str.c_str());
	  lat->DrawLatexNDC(0.6, 0.5, region.c_str());
	  lat->DrawLatexNDC(0.6, 0.4, fake_type.c_str());
	  
	  pad2->cd();
	  ratios.push_back((TH1D*)hists.back()->Clone());
	  ratios.back()->Divide(first_year);
	  ratios.back()->GetYaxis()->SetRangeUser(0., 2.);
	  ratios.back()->GetYaxis()->SetTitle("Ratio to 2018");
	  ratios.back()->Draw("same");
	  TLine *l = new TLine(ratios.back()->GetXaxis()->GetXmin(), 1, ratios.back()->GetXaxis()->GetXmax(), 1);
	  l->SetLineStyle(kDashed);
	  l->SetLineColor(kBlack);
	  l->Draw();
	}
	pad1->cd();
	leg->Draw();

	canvases.back()->Print(Form("plots/compare_fake_pred_%s.pdf", id_str.c_str()));
	canvases.back()->Print(Form("plots/compare_fake_pred_%s.png", id_str.c_str()));

	first_year = nullptr;
      }
    }
  }
}
