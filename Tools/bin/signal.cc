#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include "TCanvas.h"
#include "TString.h"
#include "TH1.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"

void allSamples(const std::string &region);
void oneSignal(int ned, int kk, bool bkgSub);
TString prettyNameADD(const TString& name);

int main()
{
  init(false, true);

  oneSignal(2, 1, false);
  oneSignal(2, 4, false);
  oneSignal(4, 1, false);

  oneSignal(2, 1, true);
  oneSignal(2, 4, true);
  oneSignal(4, 1, true);

  // use "ned" to encode year and
  // "kk" to encode positive and negative interference
  oneSignal(2017, 1, false);
  oneSignal(2018, 1, false);

  oneSignal(2017, 0, false);
  oneSignal(2018, 0, false);

  oneSignal(2017, 1, true);
  oneSignal(2018, 1, true);

  oneSignal(2017, 0, true);
  oneSignal(2018, 0, true);

}

TString prettyNameADD(const TString& name)
{
  TString newName(name);
  newName.ReplaceAll("ADDGravToGG_", "");
  newName.ReplaceAll("MS-", "M_{S} = ");
  newName.ReplaceAll("_NED-", " GeV, N_{ED} = ");
  newName.ReplaceAll("_KK-", ", KK = ");

  return newName;
}

void oneSignal(int ned, int kk, bool bkgSub)
{
  int year = ned;
  if(ned != 2017 && ned != 2018) year = 2016;

  int nBins = 260;
  double xMin = 0.0;
  double xMax = 13000.;

  TString barrelCut("weightAll*isGood*(Diphoton.Minv>230 && Photon1.pt>75 && Photon2.pt>75 && abs(Photon1.eta)<1.4442 && abs(Photon2.eta)<1.4442)");
  if(bkgSub) barrelCut = "weightAll*isGood*(Diphoton.Minv>500 && Photon1.pt>75 && Photon2.pt>75 && abs(Photon1.eta)<1.4442 && abs(Photon2.eta)<1.4442)";
  // gluon-gluon contributions should not be included in the background subtraction
  if(year == 2017 or year == 2018) {
    barrelCut+="*(pdf_id1 != 21 && pdf_id2 != 21)";
  }
  std::vector<int> stringScales = {3000, 3500, 4000, 4500, 5000, 5500, 6000};
  // samples beyond 6 TeV not available for Hewett- convention
  if(!(ned==2 && kk==4)) {
    stringScales.push_back(7000);
    stringScales.push_back(8000);
    stringScales.push_back(9000);
    stringScales.push_back(10000);
    stringScales.push_back(11000);
  }
  TCanvas *c = new TCanvas;
  c->SetLogy();
  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9);
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  // draw SM background first
  TH1F *histSM = new TH1F("gg70", "gg70", nBins, xMin, xMax);
  chains["gg70_" + std::to_string(year)]->Project("gg70", "Diphoton.Minv", barrelCut);
  TLatex * lat = new TLatex;
  for(size_t i=0; i<stringScales.size(); i++) {
    TString sample(Form("ADDGravToGG_MS-%d_NED-%d_KK-%d", stringScales.at(i), ned, kk));
    if(year == 2017 || year == 2018) {
      sample = Form("ADDGravToGG_NegInt-%d_LambdaT-%d_TuneCP2_13TeV-pythia8_%d", kk, stringScales.at(i), ned);
      if(stringScales.at(i) < 4000) continue;
    }
    std::cout << "Getting histogram " << sample << std::endl;
    TH1F *hist = new TH1F(sample, sample, nBins, xMin, xMax);
    chains[sample.Data()]->Project(sample, "Minv",  barrelCut);
    hist->SetTitle(";m_{#gamma#gamma} (GeV);Events / 50 GeV");
    hist->SetLineColor(kBlue-4+i%4);
    hist->SetMarkerColor(kBlue-4+i%4);
    if(bkgSub) hist->Add(histSM, -1.0);
    hist->GetYaxis()->SetRangeUser(1e-8, 2000);
    if(i==0) {
      hist->Draw();
      lat->DrawLatexNDC(0.6, 0.87, Form("N_{ED} = %d, KK = %d", ned, kk));
    }
    else hist->Draw("same");  
    if(year == 2017 || year == 2018) l->AddEntry(sample, Form("#Lambda_{T} = %d GeV", stringScales.at(i)), "EP");
    else l->AddEntry(sample, Form("M_{S} = %d GeV", stringScales.at(i)), "EP");
  }
  l->Draw();
  
  TString outputFilename(Form("plots/ADDGravToGG_NED-%d_KK-%d.pdf", ned, kk));
  if(bkgSub) {
    outputFilename = Form("plots/ADDGravToGG_NED-%d_KK-%d_bkg_sub.pdf", ned, kk);
  }
  c->Print(outputFilename);
}

