#ifdef __CINT__
#include "interface/tdrstyle.hh"
#include "interface/utilities.hh"
#else
#include "diphoton-analysis/Tools/interface/tdrstyle.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"
#endif

#include "TCanvas.h"
#include "TLegend.h"
#include "TROOT.h"

void kfactorStatError(const TString& fitFunc, const TString& region, const TString& scales);

int main()
{
  kfactorStatError("pol3", "BB", "R1F1");
  kfactorStatError("pol3", "BE", "R1F1");

  return 0;
}

void kfactorStatError(const TString& fitFunc="pol3", const TString& region="BB", const TString& scales="R1F1")
{
  setTDRStyle();
  gROOT->ForceStyle();

  unsigned int nbins = 100;
  double mmin = 500;
  double mmax = 4000;


  TString filename(Form("data/kfactor_%s_%s_125GeV_NNPDF.root", region.Data(), scales.Data()));
  TFile *file = TFile::Open(filename);
  TString fitName(Form("TFitResult-id1-%s",fitFunc.Data()));
  // barrel-endcap has different indexing, for technical reasons
  if(region.EqualTo("BE")) fitName.ReplaceAll("id1", "id15");
  TFitResult* fitResult = static_cast<TFitResult*>(file->Get(fitName));
  TF1* fit = static_cast<TF1*>(file->Get(fitFunc));

  TCanvas *c = new TCanvas;

  fit->SetLineColor(kBlack);
  fit->SetLineWidth(2);
  fit->SetTitle(";m_{#gamma#gamma};k-factor variations");
  fit->SetMinimum(0);
  fit->SetMaximum(3.5);
  fit->Draw();

  const int npars = fit->GetNpar();

  TF1 *fUp[npars];
  TF1 *fDown[npars];
  TH1D *central = new TH1D("central", "central", nbins, mmin, mmax);
  central->Eval(fit);
  TH1D *errorHists[npars][2];
  TH1D *errorHistsSum[2];
  
  int colors[5] = {kBlue, kBlack, kOrange, kCyan, kRed};

  for(int iPar=0; iPar<fit->GetNpar(); iPar++) {
    fUp[iPar] = eigenvectorVariation(true, iPar, fit, fitResult);
    fDown[iPar] = eigenvectorVariation(false, iPar, fit, fitResult);
    fUp[iPar]->SetLineColor(colors[iPar]);
    fDown[iPar]->SetLineColor(colors[iPar]);
    fUp[iPar]->SetLineStyle(kDashed);
    fDown[iPar]->SetLineStyle(kDashed);
    fUp[iPar]->SetLineWidth(1);
    fDown[iPar]->SetLineWidth(1);
    fUp[iPar]->Draw("same");
    fDown[iPar]->Draw("same");

    errorHists[iPar][0] = new TH1D(Form("hDown_par%d", iPar), Form("hDown_par%d", iPar), nbins, mmin, mmax);
    errorHists[iPar][1] = new TH1D(Form("hUp_par%d", iPar), Form("hUp_par%d", iPar), nbins, mmin, mmax);
    errorHists[iPar][0]->SetLineColor(colors[iPar]);
    errorHists[iPar][1]->SetLineColor(colors[iPar]);
    errorHists[iPar][0]->Eval(fUp[iPar]);
    errorHists[iPar][0]->Add(central, -1.0);
    errorHists[iPar][0]->Divide(fit);
    errorHists[iPar][1]->Eval(fDown[iPar]);
    errorHists[iPar][1]->Add(central, -1.0);
    errorHists[iPar][1]->Divide(fit);
  }

  TLegend *leg = new TLegend(0.35, 0.15, 0.65, 0.40);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(fit, "Default", "L");
  leg->AddEntry(errorHists[0][0], "#pm1#sigma, eigenvector 0", "L");
  leg->AddEntry(errorHists[1][0], "#pm1#sigma, eigenvector 1", "L");
  leg->AddEntry(errorHists[2][0], "#pm1#sigma, eigenvector 2", "L");
  leg->AddEntry(errorHists[3][0], "#pm1#sigma, eigenvector 3", "L");
  leg->Draw();

  c->Print(Form("plots/kfactor_variations_%s_%s.pdf", region.Data(), scales.Data()));

  TCanvas *cRatio = new TCanvas;
  errorHists[0][0]->SetTitle(";m_{#gamma#gamma} (GeV);Relative uncertainty");
  errorHists[0][0]->Draw();
  errorHists[0][0]->GetYaxis()->SetRangeUser(-0.1, 0.1);
  errorHists[0][1]->Draw("same");
  errorHists[1][0]->Draw("same");
  errorHists[1][1]->Draw("same");
  errorHists[2][0]->Draw("same");
  errorHists[2][1]->Draw("same");
  errorHists[3][0]->Draw("same");
  errorHists[3][1]->Draw("same");

  errorHistsSum[0] = new TH1D("hSumUp", "hSumUp", nbins, mmin, mmax);
  errorHistsSum[1] = new TH1D("hSumDown", "hSumDown", nbins, mmin, mmax);

  for(unsigned int ibin = 0; ibin <= nbins; ibin++) {
    double binContent = 0.0;
    for(int iPar = 0; iPar < npars; iPar++) {
      double averageError = (fabs(errorHists[iPar][0]->GetBinContent(ibin))+fabs(errorHists[iPar][0]->GetBinContent(ibin)))/2.0;
      binContent = sqrt(binContent*binContent+averageError*averageError);
      errorHistsSum[0]->SetBinContent(ibin, binContent);
      errorHistsSum[1]->SetBinContent(ibin, -binContent);
    }
  }
  errorHistsSum[0]->SetLineWidth(2);
  errorHistsSum[1]->SetLineWidth(2);
  errorHistsSum[0]->SetLineColor(kBlack);
  errorHistsSum[1]->SetLineColor(kBlack);
  
  errorHistsSum[0]->Draw("same");
  errorHistsSum[1]->Draw("same");

  TLegend *legRatio = new TLegend(0.35, 0.15, 0.65, 0.40);
  legRatio->SetBorderSize(0);
  legRatio->SetFillStyle(0);
  legRatio->AddEntry(fit, "Total uncertainty", "L");
  legRatio->AddEntry(errorHists[0][0], "#pm1#sigma, eigenvector 0", "L");
  legRatio->AddEntry(errorHists[1][0], "#pm1#sigma, eigenvector 1", "L");
  legRatio->AddEntry(errorHists[2][0], "#pm1#sigma, eigenvector 2", "L");
  legRatio->AddEntry(errorHists[3][0], "#pm1#sigma, eigenvector 3", "L");
  legRatio->Draw();

  cRatio->Print(Form("plots/kfactor_variations_uncertainty_%s_%s.pdf", region.Data(), scales.Data()));

}
