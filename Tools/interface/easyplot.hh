#ifndef EASYPLOT_HH
#define EASYPLOT_HH

#include "sampleList.hh"

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"

#include <string>
#include <vector>
#include <iostream>

TString reformat(TString input);


class sample {
  
public:
  sample(std::string name, std::string label, std::string year, std::string extraWeight, std::string extraCut);
  sample();

  TChain* chain();
  std::string name() { return m_name; }
  std::string label() { return m_label; }
  std::string year() { return m_year; }
  std::string extraWeight() { return m_extraWeight; }
  std::string extraCut() { return m_extraCut; }
  int lineStyle() { return m_lineStyle; }
  int lineColor() { return m_lineColor; }
  int fillStyle() { return m_fillStyle; }
  int fillColor() { return m_fillColor; }
  int markerColor() { return m_markerColor; }
  void setLabel(std::string label) { m_label = label; }

  bool isData;
  bool isDataDrivenBarrel;
  bool isDataDrivenEndcap;
  bool drawAsData;
  bool drawAsMC;

  int m_markerColor;

private:
  std::string m_name;
  std::string m_label;
  std::string m_year;
  std::string m_extraWeight;
  std::string m_extraCut;
  int m_lineStyle;
  int m_lineColor;
  int m_fillStyle;
  int m_fillColor;
};

sample::sample(std::string name, std::string label, std::string year, std::string extraWeight="1.0", std::string extraCut="1"):
  m_name(name),
  m_label(label),
  m_year(year),
  m_extraWeight(extraWeight),
  m_extraCut(extraCut),
  m_lineStyle(lineStyles[m_name]),
  m_lineColor(lineColors[m_name]),
  m_fillStyle(fillStyles[m_name]),
  m_fillColor(fillColors[m_name])
{
  isData = isDataDrivenBarrel = isDataDrivenEndcap = drawAsData = drawAsMC = false;
  if(name.find("data")!=std::string::npos) isData = true;
}

// make compiler happy
sample::sample() {}

TChain* sample::chain()
{
  // use 2018 MC samples for "2018_newjson"
  if (m_year == "2018_newjson" && !isData) return chains[m_name + "_2018"];
  else return chains[m_name + "_" + m_year];
}


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
  bool is2017_2018Data();

  std::vector<sample> m_samples;
  std::string m_variable;
  std::string m_cut;
  int m_nbins;
  double m_xmin;
  double m_xmax;
  double m_lumi;
};

plot::plot(std::vector<sample> samples, std::string variable, std::string cut, int nbins, double xmin, double xmax):
  m_samples(samples),
  m_variable(variable),
  m_cut(cut),
  m_nbins(nbins),
  m_xmin(xmin),
  m_xmax(xmax),
  m_lumi(1.0)
{ 

  if(is2016Data()) m_lumi = luminosity["2016"];
  if(is2017Data()) m_lumi = luminosity["2017"];
  if(is2018Data()) m_lumi = luminosity["2018"];
  if(is2018Data_newjson()) m_lumi = luminosity["2018_newjson"];
  if(is2017_2018Data()) m_lumi = luminosity["2017"] + luminosity["2018"];
}

// set luminosity to 2016 luminosity if one of the samples in the plot contains 2016 data
bool plot::is2016Data()
{
  for(auto isample : m_samples) {
    if(isample.year().find("2016") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2017 luminosity if one of the samples in the plot contains 2017 data
bool plot::is2017Data()
{
  for(auto isample : m_samples) {
    if(isample.year().find("2017") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2018 luminosity if one of the samples in the plot contains 2018 data
bool plot::is2018Data()
{
  for(auto isample : m_samples) {
    if(isample.year().find("2018") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2018 luminosity if one of the samples in the plot contains 2018 data
bool plot::is2018Data_newjson()
{
  for(auto isample : m_samples) {
    if(isample.year().find("2018_newjson") != std::string::npos) return true;
  }

  return false;
}

// set luminosity to 2017+2018 luminosity if one of the samples in the plot contains 2017+2018 data
bool plot::is2017_2018Data()
{
  for(auto isample : m_samples) {
    if(isample.year().find("2017_2018") != std::string::npos) return true;
  }

  return false;
}


void plot::output(const std::string& outputDirectory, const std::string& extraString)
{
  gStyle->SetErrorX(0.5);

  TCanvas *c = new TCanvas(m_variable.c_str(), m_variable.c_str(), 600, (int)((1./0.7)*600));
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1,1);
  pad1->SetBottomMargin(0);
  pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1,0.3);
  pad2->SetBottomMargin(0.25);
  pad2->SetTopMargin(0);
  pad2->Draw();

  pad1->cd();
  std::vector<TH1D*> hists;

  THStack *hs = new THStack("hs", "hs");
  TH1D *sum = new TH1D("sum", "sum", m_nbins, m_xmin, m_xmax);
  TString dataHistName;
  for(auto isample : m_samples) {
    TString newCut(m_cut.c_str());
    if(isample.isData) newCut = Form("(%s)*((%s)*(%s)*(Diphoton.Minv < 1000))",
				     isample.extraWeight().c_str(), m_cut.c_str(), isample.extraCut().c_str());
    else newCut = Form("weightAll*%6.6e*(%s)*((%s)*(%s))",
		       luminosity[isample.year()], isample.extraWeight().c_str(), m_cut.c_str(), isample.extraCut().c_str());
    if(isample.isData || isample.drawAsData) dataHistName = isample.name();
    hists.push_back(new TH1D(isample.name().c_str(), isample.label().c_str(), m_nbins, m_xmin, m_xmax));
    std::cout << "Creating histogram " << isample.name() << " for variable " << m_variable << std::endl;
    if(isample.isDataDrivenBarrel || isample.isDataDrivenEndcap) {
      std::map<std::string, std::string> histNameDD;
      histNameDD["Diphoton.Minv"] = "Minv";
      histNameDD["Minv"] = "Minv";
      histNameDD["Diphoton.qt"] = "qt";
      histNameDD["abs(Diphoton.deltaPhi)"] = "absDeltaPhi";
      histNameDD["Diphoton.deltaEta"] = "deltaEta";
      histNameDD["Diphoton.deltaR"] = "deltaR";
      histNameDD["Photon1.pt"] = "pt1";
      histNameDD["Photon1.scEta"] = "scEta1";
      histNameDD["Photon1.phi"] = "phi1";
      histNameDD["Photon2.pt"] = "pt2";
      histNameDD["Photon2.scEta"] = "scEta2";
      histNameDD["Photon2.phi"] = "phi2";
      TString filename(Form("data/fakes_%s_average.root", isample.year().c_str()));
      TFile *g = TFile::Open(filename);
      if(isample.isDataDrivenBarrel) g->GetObject(Form("BB/BB_%s", histNameDD[m_variable].c_str()), hists.back());
      else g->GetObject(Form("BE/BE_%s", histNameDD[m_variable].c_str()), hists.back());
      hists.back()->SetTitle("Data-driven #gammaj+jj");
    }
    else {
      isample.chain()->Project(isample.name().c_str(), m_variable.c_str(), newCut.Data());
    }
    if(!(isample.isData) || (isample.isData && isample.drawAsMC)) {
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

  bool foundData = false;
  // draw data histogram on top
  for(auto ihist : hists) {
    TString name(ihist->GetName());
    TString label(ihist->GetTitle());
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
      if(binWidthD < 0.01) yTitle = Form("Events / %1.3f", binWidthD);
      else if(binWidthD < 0.1) yTitle = Form("Events / %1.2f", binWidthD);
      else yTitle = Form("Events / %1.1f", binWidthD);

    }
    if(m_variable.find("Minv")!=std::string::npos ||
       m_variable.find("qt")!=std::string::npos ||
       m_variable.find("pt")!=std::string::npos )  yTitle=Form("Events / %d GeV", binWidth);
    ihist->GetYaxis()->SetTitle(reformat(yTitle));
    ihist->GetYaxis()->SetTitleOffset(1.35);

    if(!foundData && name.EqualTo(dataHistName)) {
      ihist->SetMarkerColor(kBlack);
      ihist->Draw("e");
      //      ihist->GetYaxis()->SetRangeUser(ihist->GetMinimum(), std::max(sum->GetMaximum(), ihist->GetMaximum())*1.1);
      leg->AddEntry(ihist, label, "ELP");
      foundData = true;
    }
    else {
      // temporary hack! remove me!
      // ihist->SetFillStyle(3344);
      // ihist->SetFillColor(kBlack);
      leg->AddEntry(ihist, label, "F");
      // temporary hack! remove me!
      //      leg->AddEntry(sum, "Data (2018C re-reco)", "F");
    }
    //    if(label.EqualTo("Data (2017)")) ihist->SetFillStyle(3344);
  }

  hs->Draw("hist,same");

  sum->SetMarkerSize(0);
  sum->SetLineColor(kBlack);
  sum->SetFillColor(kBlack);
  sum->SetFillStyle(3344);
  sum->Draw("E2,same");

  TH1D *ratio = nullptr;
  TH1D *ratioError = nullptr;
  // draw data histogram on top
  foundData = false;
  for(auto ihist : hists) {
    TString name(ihist->GetName());
    if(name.Contains("data") && !foundData) {
      foundData = true;
      ihist->Draw("e,same");
      ratio = dynamic_cast<TH1D*>(ihist->Clone("ratio"));
      ratioError = dynamic_cast<TH1D*>(ihist->Clone("ratioError"));
      ratio->GetYaxis()->SetTitle("Ratio");
      for(int i=0; i<=ratio->GetNbinsX(); i++) {
	double content = sum->GetBinContent(i);
	if(content != 0) {
	  ratio->SetBinContent(i, ratio->GetBinContent(i)/content);
	  ratio->SetBinError(i, ratio->GetBinError(i)/content);
	  ratioError->SetBinContent(i, 1.0);
	  ratioError->SetBinError(i, sum->GetBinError(i)/content);
	}
	else {
	  ratio->SetBinContent(i, 0.0);
	  ratio->SetBinError(i, 0.0);
	  ratioError->SetBinContent(i, 1.0);
	  ratioError->SetBinError(i, 0.0);
	}
      }
    }
  }
  
  leg->Draw();

  c->RedrawAxis();

  TLatex *lat = new TLatex;
  lat->SetTextSize(0.038);
  lat->DrawLatexNDC(0.17, 0.96, "#font[62]{CMS} #scale[0.8]{#font[52]{Preliminary}}");
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.70, 0.96, Form("%1.1f fb^{-1} (13 TeV)", luminosity[m_samples.front().year()]));

  // draw ratio
  pad2->cd();
  ratio->GetXaxis()->SetTitle(reformat(m_variable.c_str()));
  ratio->GetYaxis()->SetRangeUser(0., 2.1);
  ratio->Draw();
  ratioError->SetMarkerSize(0);
  ratioError->SetLineColor(kBlack);
  ratioError->SetFillColor(kBlack);
  ratioError->SetFillStyle(3344);
  gStyle->SetErrorX(0.5);
  ratioError->Draw("E2,same");
  ratio->GetXaxis()->SetTitleSize(ratio->GetXaxis()->GetTitleSize()/0.7);
  ratio->GetXaxis()->SetTitleOffset(ratio->GetXaxis()->GetTitleOffset()/0.7);
  ratio->GetYaxis()->SetLabelSize(ratio->GetYaxis()->GetLabelSize()/0.7);
  ratio->GetYaxis()->SetTitleSize(ratio->GetYaxis()->GetTitleSize()/0.7);
  ratio->GetYaxis()->SetTitleOffset(ratio->GetYaxis()->GetTitleOffset()/0.7);
  TLine *line = new TLine(ratio->GetXaxis()->GetXmin(), 1.0, ratio->GetXaxis()->GetXmax(), 1.0);
  line->SetLineColor(kRed);
  line->SetLineStyle(kDashed);
  line->Draw();
  ratio->Draw("same");

  c->Print(Form("%s/%s_%s_lin.pdf", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
  c->Print(Form("%s/%s_%s_lin.png", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
  c->Print(Form("%s/%s_%s.root", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
  pad1->SetLogy();
  c->Print(Form("%s/%s_%s_log.pdf", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
  c->Print(Form("%s/%s_%s_log.png", outputDirectory.c_str(), variable().c_str(), extraString.c_str()));
}

TString reformat(TString input)
{
  TString output=input;
  if(input.Contains("Minv") || input.Contains("pt") || input.Contains("qt")) output+=" (GeV)";
  output.ReplaceAll("Diphoton.Minv", "m_{#gamma#gamma}");
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
