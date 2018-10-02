#ifdef __CINT__
#include "interface/tdrstyle.hh"
#include "interface/sampleList.hh"
#else
#include "diphoton-analysis/Tools/interface/tdrstyle.hh"
#include "diphoton-analysis/Tools/interface/sampleList.hh"
#endif

#include "TCanvas.h"
#include "TEfficiency.h"
#include "TH1.h"
#include "TLatex.h"

#include <iostream>
#include <algorithm>

void oneHist(const std::string& varname, TChain *ch, const std::string& year);
int efficiency(const std::string& year, const std::string& variable);

int main()
{
  setTDRStyle();
  // initialize chains
  init();

  //  std::vector<std::string> years = {"2015", "2016", "2017"};
  std::vector<std::string> years = {"2018"};
  std::vector<std::string> variables = {"Photon2.pt", "Photon2.eta"};

  for(auto iyear : years) {
    for(auto ivar : variables) {
      efficiency(iyear, ivar);
    }
  }

  return 0;
}

int efficiency(const std::string& year = "2016", const std::string& variable = "Photon2.pt")
{
  std::cout << "Calculating trigger turn-on for " << variable 
	    << " in " << year << " data." << std::endl;


  std::string chainName("data_");
  chainName += year;
  std::cout << "Processing " << chains[chainName]->GetEntries() << " entries." << std::endl;

  oneHist(variable, chains[chainName], year);

  return 0;
}


void oneHist(const std::string& varname, TChain *ch, const std::string& year)
{
  int nbins = 200;
  std::map<std::string, double> min;
  min["Photon2.pt"] = 0.0;
  min["Photon2.eta"] = -2.5;
  std::map<std::string, double> max;
  max["Photon2.pt"] = 1000.0;
  max["Photon2.eta"] = 2.5;

  std::string histnames[2] = {"numerator", "denominator"};
  std::vector<TH1F*> hists;
  
  for(int i = 0; i < 2; i++) {
    hists.push_back(new TH1F(histnames[i].c_str(), histnames[i].c_str(), nbins, min[varname], max[varname]));
  }

  std::string numerator(varname);
  numerator += ">>numerator";
  std::string denominator(varname);
  denominator += ">>denominator";

  TString numeratorCut("isGood && HLT_DoublePhoton60");
  if(year.find("2017") != std::string::npos || year.find("2018") != std::string::npos) {
    //    numeratorCut = "isGood && HLT_DoublePhoton85 && HLT_DoublePhoton33_CaloIdL";
    numeratorCut = "isGood && HLT_DoublePhoton70 && HLT_DoublePhoton33_CaloIdL && abs(Photon1.eta)<2.5 && abs(Photon2.eta)<2.5";
    if(varname.find("eta") != std::string::npos) numeratorCut += "&& Photon2.pt>80";
  }
  ch->Draw(numerator.c_str() , numeratorCut);
  if(year.find("2017") != std::string::npos || year.find("2018") != std::string::npos) {
    TString denominatorCut("isGood && HLT_DoublePhoton33_CaloIdL && abs(Photon1.eta)<2.5 && abs(Photon2.eta)<2.5");
    if(varname.find("eta") != std::string::npos) denominatorCut += "&& Photon2.pt>80";
    ch->Draw(denominator.c_str(), denominatorCut);
  }
  else {
    ch->Draw(denominator.c_str(), "isGood && HLT_DoublePhoton40");
  }
  // add overflow
  for(int i = 0; i < 2; i++) {
    int maxBin = hists[i]->GetNbinsX();
    hists[i]->SetBinContent(maxBin, hists[i]->GetBinContent(maxBin) + hists[i]->GetBinContent(maxBin+1));
  }

  TCanvas *c0 = new TCanvas;
  c0->SetLogy();
  hists[0]->SetLineColor(kRed);
  hists[1]->SetLineColor(kBlue);
  hists[0]->Draw();
  hists[1]->Draw("same");
  // latex can't figure out what to do with files
  // with more than one period in them
  std::string varForFilename(varname);
  std::replace(varForFilename.begin(), varForFilename.end(), '.', '_');
  c0->Print(Form("plots/eff_input_%s_%s.pdf", year.c_str(), varForFilename.c_str()));

  TCanvas *c1 = new TCanvas;
  TEfficiency *eff = new TEfficiency(*hists[0], *hists[1]);
  eff->Draw("AP");
  eff->SetTitle(";p_{T}(#gamma_{2}) (GeV);Efficiency");

  TLatex *lat = new TLatex;
  lat->SetTextSize(0.038);
  lat->DrawLatexNDC(0.17, 0.96, "#font[62]{CMS} #scale[0.8]{#font[52]{Preliminary}}");
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.70, 0.96, Form("%1.1f fb^{-1} (13 TeV)", luminosity2018));

  c1->Print(Form("plots/eff_%s_%s.pdf", year.c_str(), varForFilename.c_str()));
}
