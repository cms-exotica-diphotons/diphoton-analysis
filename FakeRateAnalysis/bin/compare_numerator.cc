#include "PhysicsTools/Utilities/macros/setTDRStyle.C"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"

#include <map>

void compare_numerator();

int main(int argc, char *argv[])
{
  compare_numerator();
}

void compare_numerator()
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
  std::vector<TGraphAsymmErrors*> graph_list;

  for(auto pvCut : pvCuts) {
    for(auto region : regions) {
      canvases.push_back(new TCanvas);
      canvases.back()->SetLogy();
      TLegend *leg = new TLegend(0.55, 0.40, 0.85, 0.7);
      bool first = true;
      for(auto dataset : datasets) {
	TFile *f = TFile::Open(Form("fakeRatePlots_%s_nPV%s.root", dataset.c_str(), pvCut.c_str()));
	const TString graphName(Form("bkgvspt%s_chIso5To10", region.c_str()));
	graph_list.push_back(dynamic_cast<TGraphAsymmErrors*>(f->Get(graphName)));
	graph_list.back()->SetMinimum(0.0);
	// normalize graph to 1
	for(int i = 0; i < graph_list.back()->GetN(); i++) {
	  graph_list.back()->GetY()[i] = graph_list.back()->GetY()[i]/graph_list.back()->Integral();
	  graph_list.back()->GetEYhigh()[i] = graph_list.back()->GetEYhigh()[i]/graph_list.back()->Integral();
	  graph_list.back()->GetEYlow()[i] = graph_list.back()->GetEYlow()[i]/graph_list.back()->Integral();
	}
	//	graph_list.back()->SetMaximum(graphMax[region]);
	graph_list.back()->GetXaxis()->SetRangeUser(0., 800.);
	graph_list.back()->SetMarkerStyle(styles[dataset]);
	graph_list.back()->SetMarkerColor(colors[dataset]);
	graph_list.back()->SetLineColor(colors[dataset]);
	graph_list.back()->SetTitle(";p_{T} (GeV);Numerator (normalized)");
	if(first) graph_list.back()->Draw("ALP");
	else graph_list.back()->Draw("LP same");
	first = false;
	leg->AddEntry(graph_list.back(), datasetLabel[dataset].c_str(), "LPE");
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
      TString filename(Form("plots/compare_numerator_%s_%s.pdf", region.c_str(), pvCut.c_str()));
      filename.ReplaceAll("-", "to");
      canvases.back()->Print(filename);
    }
  }    
    
}
