#ifndef EASYPLOT_HH
#define EASYPLOT_HH

#include "sampleList.hh"

#include "TCanvas.h"
#include "TChain.h"
#include "TH1.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TString.h"

#include <string>
#include <vector>
#include <iostream>

TString reformat(TString input);


class sample {

public:
  sample(std::string name, std::string label, std::string extraWeight, std::string extraCut);
  sample();

  TChain* chain() { return chains[m_name]; }
  std::string name() { return m_name; }
  std::string extraWeight() { return m_extraWeight; }
  std::string extraCut() { return m_extraCut; }
  int lineStyle() { return m_lineStyle; }
  int lineColor() { return m_lineColor; }
  int fillStyle() { return m_fillStyle; }
  int fillColor() { return m_fillColor; }
  int markerColor() { return m_markerColor; }

  bool isData;
  bool drawAsData;

  int m_markerColor;

private:
  std::string m_name;
  std::string m_label;
  std::string m_extraWeight;
  std::string m_extraCut;
  int m_lineStyle;
  int m_lineColor;
  int m_fillStyle;
  int m_fillColor;
};

sample::sample(std::string name, std::string label, std::string extraWeight="1.0", std::string extraCut="1"):
  m_name(name),
  m_label(label),
  m_extraWeight(extraWeight),
  m_extraCut(extraCut),
  m_lineStyle(lineStyles[m_name]),
  m_lineColor(lineColors[m_name]),
  m_fillStyle(fillStyles[m_name]),
  m_fillColor(fillColors[m_name])
{
  isData = false;
  drawAsData = false;
  if(name.find("data")!=std::string::npos) isData = true;
}

// make compiler happy
sample::sample() {}

class plot {

public:
  plot(std::vector<sample> samples, std::string variable, std::string cut, int nbins, double xmin, double xmax);
  void output(const std::string& outputDirectory, const std::string& extraString);
  std::string variable() { return m_variable; }
  std::string cut() {return m_cut; }

private:
  bool is2016Data();
  bool is2017Data();
  bool is2018Data();
  bool is2018Data_newjson();

  std::vector<sample> m_samples;
  std::string m_variable;
  std::string m_cut;
  int m_nbins;
  double m_xmin;
  double m_xmax;

};

plot::plot(std::vector<sample> samples, std::string variable, std::string cut, int nbins, double xmin, double xmax):
  m_samples(samples),
  m_variable(variable),
  m_cut(cut),
  m_nbins(nbins),
  m_xmin(xmin),
  m_xmax(xmax)
{

  if(is2016Data()) luminosity = luminosity2016;
  if(is2017Data()) luminosity = luminosity2017;
  if(is2018Data()) luminosity = luminosity2018;
  if(is2018Data_newjson()) luminosity = luminosity2018_newjson;
}

// set luminosity to 2016 luminosity if one of the samples in the plot contains 2016 data
bool plot::is2016Data()
{
  for(auto isample : m_samples) {
    if(isample.name().find("2016") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2017 luminosity if one of the samples in the plot contains 2017 data
bool plot::is2017Data()
{
  for(auto isample : m_samples) {
    if(isample.name().find("2017") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2018 luminosity if one of the samples in the plot contains 2018 data
bool plot::is2018Data()
{
  for(auto isample : m_samples) {
    if(isample.name().find("2018") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2018 luminosity if one of the samples in the plot contains 2018 data
bool plot::is2018Data_newjson()
{
  for(auto isample : m_samples) {
    if(isample.name().find("2018_newjson") != std::string::npos) return true;
  }

  return false;
}

void plot::output(const std::string& outputDirectory, const std::string& extraString)
{
  gStyle->SetErrorX(0.5);

  TCanvas *c = new TCanvas;
  std::vector<TH1D*> hists;

  THStack *hs = new THStack("hs", "hs");
  TH1D *sum = new TH1D("sum", "sum", m_nbins, m_xmin, m_xmax);
  TString dataHistName;

  for(auto isample : m_samples) {

    TString newCut(m_cut.c_str());
    if(isample.isData) newCut = Form("(%s)*((%s)*(%s))",
				     isample.extraWeight().c_str(), m_cut.c_str(), isample.extraCut().c_str());
    else newCut = Form("weightAll*%6.6e*(%s)*((%s)*(%s))",
				     luminosity, isample.extraWeight().c_str(), m_cut.c_str(), isample.extraCut().c_str());
    if(isample.isData || isample.drawAsData) dataHistName = isample.name();
    hists.push_back(new TH1D(isample.name().c_str(), isample.name().c_str(), m_nbins, m_xmin, m_xmax));
    std::cout << "Creating histogram " << isample.name() << " for variable " << m_variable << std::endl;
    isample.chain()->Project(isample.name().c_str(), m_variable.c_str(), newCut.Data());
    if(!isample.isData) {
      sum->Add(hists.back());
      std::cout << "Adding histogram: " << hists.back()->GetName() << std::endl;
    }
    std::cout << "Integral (" << isample.name() << "): " << hists.back()->Integral() << std::endl;
    std::cout << "Sum: " << sum->Integral() << std::endl;
    hists.back()->SetLineStyle(isample.lineStyle());
    hists.back()->SetLineColor(isample.lineColor());
    hists.back()->SetFillStyle(isample.fillStyle());
    hists.back()->SetFillColor(isample.fillColor());
    hists.back()->SetMarkerColor(isample.markerColor());
    // move overflow to last bin
    float lastBin = hists.back()->GetBinContent(hists.back()->GetNbinsX());
    float overflow = hists.back()->GetBinContent(hists.back()->GetNbinsX()+1);
    hists.back()->SetBinContent(hists.back()->GetNbinsX(), lastBin + overflow);
    hists.back()->SetBinContent(hists.back()->GetNbinsX()+1, 0.0);

    // don't stack the data histogram
    if(!isample.isData && !isample.drawAsData) hs->Add(hists.back());
  }
  TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  // draw data histogram on top
  for(auto ihist : hists) {
    TString name(ihist->GetName());
    ihist->SetLineColor(kBlack);
    ihist->GetXaxis()->SetNdivisions(505);
    ihist->GetXaxis()->SetTitle(reformat(m_variable.c_str()));
    //    ihist->SetTitle(reformat(m_cut.c_str()));

    int binWidth=static_cast<int>((m_xmax-m_xmin)/m_nbins);
    TString yTitle("Events");
    if(binWidth!=1) Form("Events / %d", binWidth);
    // if the bin width was rounded to zero, use a double instead
    if(binWidth==0) {
      double binWidthD = static_cast<double>((m_xmax-m_xmin)/m_nbins);
      yTitle = Form("Events / %1.1f", binWidthD);
    }
    if(m_variable.find("Minv")!=std::string::npos ||
       m_variable.find("qt")!=std::string::npos ||
       m_variable.find("pt")!=std::string::npos )  yTitle=Form("Events / %d GeV", binWidth);
    ihist->GetYaxis()->SetTitle(reformat(yTitle));
    ihist->GetYaxis()->SetTitleOffset(1.35);

    if(name.EqualTo(dataHistName)) {
      ihist->SetMarkerColor(kBlack);
      ihist->Draw("e");
      //      ihist->GetYaxis()->SetRangeUser(ihist->GetMinimum(), std::max(sum->GetMaximum(), ihist->GetMaximum())*1.1);
      leg->AddEntry(ihist, prettyName[ihist->GetName()].c_str(), "ELP");
    }
    else {
      leg->AddEntry(ihist, prettyName[ihist->GetName()].c_str(), "F");
    }
  }

  hs->Draw("hist,same");
  sum->SetMarkerSize(0);
  sum->SetLineColor(kBlack);
  sum->SetFillColor(kBlack);
  sum->SetFillStyle(3344);
  sum->Draw("E2,same");

  // draw data histogram on top
  for(auto ihist : hists) {
    TString name(ihist->GetName());
    if(name.Contains("data")) ihist->Draw("e,same");
  }

  leg->Draw();

  c->RedrawAxis();

  TLatex *lat = new TLatex;
  lat->SetTextSize(0.038);
  lat->DrawLatexNDC(0.17, 0.96, "#font[62]{CMS} #scale[0.8]{#font[52]{Preliminary}}");
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.70, 0.96, Form("%1.1f fb^{-1} (13 TeV)", luminosity));

  c->Print(Form("%s/%s_%s_lin.pdf", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
  c->Print(Form("%s/%s_%s.root", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
  c->SetLogy();
  c->Print(Form("%s/%s_%s_log.pdf", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
}

TString reformat(TString input)
{
  TString output=input;
  if(input.Contains("Minv") || input.Contains("pt") || input.Contains("qt")) output+=" (GeV)";
  output.ReplaceAll("Minv", "m_{#gamma#gamma}");
  output.ReplaceAll("Photon1.pt", "p_{T1}");
  output.ReplaceAll("Photon1.phi", "#phi_{1}");
  output.ReplaceAll("Photon1.eta", "#eta_{1}");
  output.ReplaceAll("nPV", "n_{PV}");
  output.ReplaceAll("Photon2.pt", "p_{T2}");
  output.ReplaceAll("Photon2.phi", "#phi_{2}");
  output.ReplaceAll("Photon2.eta", "#eta_{2}");
  output.ReplaceAll("Diphoton.qt", "q_{T,#gamma#gamma}");
  output.ReplaceAll("Diphoton.deltaPhi", "#Delta#phi_{#gamma#gamma}");
  output.ReplaceAll("Diphoton.deltaEta", "#Delta#eta_{#gamma#gamma}");
  output.ReplaceAll("Diphoton.deltaR", "#DeltaR_{#gamma#gamma}");
  output.ReplaceAll("abs(Diphoton.cosThetaStar)", "|cos(#theta*)_{#gamma#gamma}|");

  return output;
}


#endif
