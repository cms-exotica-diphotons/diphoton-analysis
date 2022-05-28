#ifdef __CINT__
#include "interface/tdrstyle.hh"
#else
#include "diphoton-analysis/Tools/interface/tdrstyle.hh"
#endif

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TROOT.h"

#include <iostream>

TH1F* getHist(TFile *file, const int year, const std::string& type, const std::string& region, const std::string& histName);
TH1F* getTH1F(TGraphAsymmErrors *gr);
TH1F* getTH1F(TH1F *h);

const float binWidth = 50; // GeV

void plot_blinded(const std::string& years_to_plot);

int main(void)
{
  plot_blinded("all");
  plot_blinded("2016");
  plot_blinded("2017");
  plot_blinded("2018");

  return 0;
}

void plot_blinded(const std::string& years_to_plot)
{
  std::map<std::string, int> fillColors;
  fillColors["gg"] = kCyan;
  fillColors["gj"] = kBlue;
  fillColors["jj"] = kSpring;
  fillColors["vg"] = kOrange;
  fillColors["dy"] = kYellow;
  fillColors["ttg"] = kMagenta;

  const double xmin = 500.;
  setTDRStyle();
  gROOT->ForceStyle();
  gStyle->SetOptStat(0);

  std::string type("shapes_fit_b");

  TFile *f = TFile::Open("../../HiggsAnalysis/CombinedLimit/fitDiagnosticsADDGravToGG_MS-5000_NED-4_KK-1_lowmass.root");

  std::vector<int> years_all = {2016, 2017, 2018};
  std::vector<int> years;
  if(years_to_plot == "all") years = years_all;
  else years.push_back(std::atoi(years_to_plot.c_str()));

  std::vector<std::string> regions = {"BB", "BE"};
  std::vector<TH1F*> histsBackground, histsData, histsGG, histsGJ, histsVG, histsTTG, histsDY;

  std::map<std::string, TH1F*> sumBackground, sumData, sumGG, sumGJ, sumVG, sumTTG, sumDY;
  std::map<std::string, THStack*> stacks;
  for(const auto& region : regions) {
    sumBackground[region] = sumData[region] = nullptr;
    for(const auto& year : years) {
      histsBackground.push_back(getHist(f, year, type, region, "total_background"));
      histsData.push_back(getHist(f, year, type, region, "data"));
      histsGG.push_back(getHist(f, year, type, region, "gg"));
      histsGJ.push_back(getHist(f, year, type, region, "gj"));
      histsVG.push_back(getHist(f, year, type, region, "vg"));
      histsTTG.push_back(getHist(f, year, type, region, "ttg"));
      histsDY.push_back(getHist(f, year, type, region, "dy"));
      if(sumBackground[region] == nullptr) sumBackground[region] = histsBackground.back();
      else sumBackground[region]->Add(histsBackground.back());
      if(sumData[region] == nullptr) sumData[region] = histsData.back();
      else sumData[region]->Add(histsData.back());
      if(sumGG[region] == nullptr) sumGG[region] = histsGG.back();
      else sumGG[region]->Add(histsGG.back());
      if(sumGJ[region] == nullptr) sumGJ[region] = histsGJ.back();
      else sumGJ[region]->Add(histsGJ.back());
      if(sumVG[region] == nullptr) sumVG[region] = histsVG.back();
      else sumVG[region]->Add(histsVG.back());
      if(sumTTG[region] == nullptr) sumTTG[region] = histsTTG.back();
      else sumTTG[region]->Add(histsTTG.back());
      if(sumDY[region] == nullptr) sumDY[region] = histsDY.back();
      else sumDY[region]->Add(histsDY.back());
      sumDY[region]->SetFillColor(fillColors["dy"]);
      sumGG[region]->SetFillColor(fillColors["gg"]);
      sumGJ[region]->SetFillColor(fillColors["gj"]);
      sumVG[region]->SetFillColor(fillColors["vg"]);
      sumTTG[region]->SetFillColor(fillColors["ttg"]);
      stacks[region] = new THStack("hs", "hs");
      stacks[region]->Add(sumDY[region]);
      stacks[region]->Add(sumTTG[region]);
      stacks[region]->Add(sumVG[region]);
      stacks[region]->Add(sumGJ[region]);
      stacks[region]->Add(sumGG[region]);
    }
  }

  std::map<std::string, TCanvas*> canvases;
  std::map<std::string, std::string> prettyName;
  prettyName["BB"] = "EB-EB";
  prettyName["BE"] = "EB-EE";
  for(const auto& region : regions) {
    canvases[region] = new TCanvas;
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1,1);
    pad1->SetBottomMargin(0);
    pad1->Draw();

    TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1,0.3);
    pad2->SetBottomMargin(0.25);
    pad2->SetTopMargin(0);
    pad2->Draw();

    pad1->cd();
    sumBackground[region]->SetTitle(Form(";m_{#gamma#gamma} (GeV); Events / %d GeV", static_cast<int>(binWidth)));
    sumBackground[region]->GetXaxis()->SetRangeUser(xmin, 1000);    
    sumBackground[region]->Draw("hist");
    sumBackground[region]->GetYaxis()->SetRangeUser(0., 1.3*sumBackground[region]->GetMaximum());
    stacks[region]->Draw("hist same");
    sumData[region]->SetLineColor(kBlack);
    sumData[region]->SetMarkerStyle(kFullCircle);
    sumData[region]->GetXaxis()->SetRangeUser(xmin, 1000);    
    sumData[region]->Draw("same");
    TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.9);
    leg->AddEntry(sumData[region], "Data", "ELP");
    leg->AddEntry(sumGG[region], "#gamma#gamma", "F");
    leg->AddEntry(sumGJ[region], "#gamma+j, j+j", "F");
    leg->AddEntry(sumVG[region], "V#gamma", "F");
    leg->AddEntry(sumTTG[region], "t#bar{t}#gamma", "F");
    leg->AddEntry(sumDY[region], "DY", "F");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();
    TLatex *lat = new TLatex();
    lat->DrawLatexNDC(0.4, 0.8, prettyName[region].c_str());

    std::string yearString = std::to_string(years.front());
    if(years.size() > 1) {
      yearString += "-" + std::to_string(years.back());
    }
    lat->DrawLatexNDC(0.4, 0.7, yearString.c_str());

    pad2->cd();

    TH1F* ratio = dynamic_cast<TH1F*>(sumData[region]->Clone("ratio"));
    float chi2 = 0.0;
    for(int i = 1; i <= ratio->GetNbinsX(); i++ ) {
      float data = sumData[region]->GetBinContent(i);
      float dataError = sumData[region]->GetBinError(i);
      float background = sumBackground[region]->GetBinContent(i);
      ratio->SetBinContent(i, data/background);
      ratio->SetBinError(i, dataError/background);
      float pull = 0.0;
      if(data > 0.0) pull = (data - background) / sqrt(data);
      chi2 += pull*pull;
    }
    std::cout << "chi^2/ndof (" << region << "): " 
	      << chi2 << "/" << ratio->GetNbinsX() << std::endl;
    ratio->SetTitle(";m_{#gamma#gamma} (GeV); Ratio");
    ratio->GetXaxis()->SetRangeUser(xmin, 1000);    
    ratio->GetYaxis()->SetRangeUser(0.5, 1.5);
    ratio->GetXaxis()->SetTitleSize(ratio->GetXaxis()->GetTitleSize()/0.7);
    ratio->GetXaxis()->SetTitleOffset(ratio->GetXaxis()->GetTitleOffset()/0.7);
    ratio->GetYaxis()->SetLabelSize(ratio->GetYaxis()->GetLabelSize()/0.7);
    ratio->GetYaxis()->SetTitleSize(ratio->GetYaxis()->GetTitleSize()/0.7);
    ratio->GetYaxis()->SetTitleOffset(ratio->GetYaxis()->GetTitleOffset()/0.7);
    ratio->Draw();



    TLine *line = new TLine(xmin, 1.0, ratio->GetXaxis()->GetXmax(), 1.0);
    line->SetLineColor(kRed);
    line->SetLineStyle(kDashed);
    line->SetLineWidth(2);
    line->Draw();
    ratio->Draw("same");

    pad1->cd();
    lat->DrawLatexNDC(0.4, 0.6, Form("#chi^{2} = %2.1f", chi2));

    pad1->RedrawAxis();

    std::string histName("plots/mgg_");
    histName += region;
    for(auto year : years) {
      histName += "_";
      histName += std::to_string(year);
    }
    histName += ".pdf";
    canvases[region]->Print(histName.c_str());
    histName.replace(histName.find(".pdf"), histName.size(), ".png");
    canvases[region]->Print(histName.c_str());
  }
}

TH1F* getHist(TFile *file, const int year, const std::string& type, const std::string& region, const std::string& histName)
{
  std::string channel = type + "/" + region + "_" + std::to_string(year);
  std::string fullHistName = channel + "/" + histName;
  TH1F *hist;
  if(histName == "data") {
    hist = getTH1F(dynamic_cast<TGraphAsymmErrors*>(file->Get(fullHistName.c_str())));
  }
  else {
    hist = getTH1F(dynamic_cast<TH1F*>(file->Get(fullHistName.c_str())));
  }

  return hist;
}

TH1F* getTH1F(TGraphAsymmErrors *gr)
{
  int npoints = gr->GetN();
  TH1F *hist = new TH1F(gr->GetName(), gr->GetName(), npoints, 0, npoints*binWidth);
  for (int i = 1; i <= npoints; i++) {
    hist->SetBinContent(i, gr->GetY()[i-1]);
    hist->SetBinError(i, sqrt(gr->GetY()[i-1]));
  }

  return hist;
}

TH1F* getTH1F(TH1F *h)
{
  int npoints = h->GetNbinsX();
  TH1F *hist = new TH1F(h->GetName(), h->GetName(), npoints, 0, npoints*binWidth);
  for (int i = 1; i <= npoints; i++) {
    float binContent = h->GetBinContent(i);
    hist->SetBinContent(i, binContent);
    hist->SetBinError(i, sqrt(binContent));
  }

  return hist;
}
