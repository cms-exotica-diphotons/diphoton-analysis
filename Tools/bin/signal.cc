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
void plotUnpar_fix_du(int year, int spin, std::string du, bool bkgSub);

bool runUnparticles = true;

int main()
{
  init(false, true);

  if (!runUnparticles){
    std::cout << "Plotting ADD samples" << std::endl;
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

  if (runUnparticles){
    std::cout << "Plotting Unparticles" << std::endl;
    plotUnpar_fix_du(2017, 0, "1p1", false);
    plotUnpar_fix_du(2017, 0, "1p5", false);
    plotUnpar_fix_du(2017, 0, "1p9", false);

    plotUnpar_fix_du(2017, 2, "1p1", false);
    plotUnpar_fix_du(2017, 2, "1p5", false);
    plotUnpar_fix_du(2017, 2, "1p9", false);

    // subtract background
    plotUnpar_fix_du(2017, 0, "1p1", true);
    plotUnpar_fix_du(2017, 0, "1p5", true);
    plotUnpar_fix_du(2017, 0, "1p9", true);

    plotUnpar_fix_du(2017, 2, "1p1", true);
    plotUnpar_fix_du(2017, 2, "1p5", true);
    plotUnpar_fix_du(2017, 2, "1p9", true);

  }


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

std::map<std::string, std::vector<int>> lambdaUmap = {{"Spin0_du1p1", {10000, 4000, 8000}},
                                                {"Spin0_du1p5", {2000, 2500, 3500}},
                                                {"Spin0_du1p9", {2000, 2500, 3500}},
                                                {"Spin2_du1p1", {2000, 2500, 3000}},
                                                {"Spin2_du1p5", {2000, 2500, 3000}},
                                                {"Spin2_du1p9", {2000, 2500, 3500}}
                                               };


void plotUnpar_fix_du(int year, int spin, std::string du, bool bkgSub){

  // Plot settings
  int nBins = 260;
  double xMin = 0.0;
  double xMax = 13000;

  TString barrelCut("weightAll*isGood*(Diphoton.Minv>230 && Photon1.pt>75 && Photon2.pt>75 && abs(Photon1.eta)<1.4442 && abs(Photon2.eta)<1.4442)");
  if(bkgSub) barrelCut = "weightAll*isGood*(Diphoton.Minv>500 && Photon1.pt>75 && Photon2.pt>75 && abs(Photon1.eta)<1.4442 && abs(Photon2.eta)<1.4442)";

  if(year == 2017 or year == 2018) {
    // It rejects gluon-initiated contributions to the GG background,
    // as those contributions are not included in ADD samples.
    // If included, then at low invariant masses, the (S + interference + B)_ADD - B_GG contribution will be negative.
    // (?) Is this necessary for the unparticles
    barrelCut+="*(pdf_id1 != 21 && pdf_id2 != 21)";
  }

  TCanvas *c = new TCanvas;
  c->SetLogy();
  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9);
  l->SetBorderSize(0);
  l->SetFillStyle(0);

  // Draw SM background first
  TH1F *histSM = new TH1F("gg70", "gg70", nBins, xMin, xMax);
  chains["gg70_"+std::to_string(year)]->Project("gg70", "Diphoton.Minv", barrelCut);
  TLatex *lat = new TLatex;


 // Draw Signal
 std::string spin_du = "Spin" + std::to_string(spin) + "_du" + du;
 std::vector<int> lambdaUs = lambdaUmap[spin_du];

 for(size_t i=0; i<lambdaUs.size(); i++) {
      TString sample(Form("UnparToGG_%s_LambdaU-%d_TuneCP2_13TeV_pythia8_%d", spin_du.c_str(), lambdaUs.at(i), year));
      std::cout << "Getting histogram " << sample << std::endl;
      TH1F *sighist = new TH1F(sample, sample, nBins, xMin, xMax);
      chains[sample.Data()]->Project(sample, "Minv",  barrelCut);
      sighist->SetTitle(";m_{#gamma#gamma} (GeV);Events / 50 GeV");
      sighist->SetLineColor(kBlue-4+i%4);
      sighist->SetMarkerColor(kBlue-4+i%4);

      if(bkgSub) sighist->Add(histSM, -1.0);
      sighist->GetYaxis()->SetRangeUser(1e-8, 2000);

      if(i==0) {
        sighist->Draw();
        lat->DrawLatexNDC(0.6, 0.87, Form("spin = %d, du = %s", spin, du.c_str()));
      }

      else sighist->Draw("same");

      l->AddEntry(sample, Form("#Lambda_{U} = %d GeV", lambdaUs.at(i)), "EP");
 }
 l->Draw();

 TString outputFilename(Form("plots/UnparToGG_%s_TuneCP2_13TeV_pythia8_%d.pdf", spin_du.c_str(), year));
 if(bkgSub) {
   outputFilename = Form("plots/UnparToGG_%s_TuneCP2_13TeV_pythia8_%d.pdf", spin_du.c_str(), year);
 }
 c->Print(outputFilename);

}
