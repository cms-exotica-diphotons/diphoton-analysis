#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include "TCanvas.h"
#include "TString.h"
#include "TH1.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"

void plotUnpar_fix_du(int year, int spin, std::string du, bool bkgSub);

int main()
{
  init(false, true);

    std::cout << "Plotting Unparticles" << std::endl;
    plotUnpar_fix_du(2017, 0, "1p1", false);

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

  // if(year == 2017 or year == 2018) {
  //   // It rejects gluon-initiated contributions to the GG background,
  //   // as those contributions are not included in ADD samples.
  //   // If included, then at low invariant masses, the (S + interference + B)_ADD - B_GG contribution will be negative.
  //   // (?) Is this necessary for the unparticles
  //   barrelCut+="*(pdf_id1 != 21 && pdf_id2 != 21)";
  // }

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
   outputFilename = Form("plots/UnparToGG_%s_TuneCP2_13TeV_pythia8_%d_bkg_sub.pdf", spin_du.c_str(), year);
 }
 c->Print(outputFilename);

}
