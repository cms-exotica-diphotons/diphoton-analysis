#ifdef __CINT__
#include "interface/tdrstyle.hh"
#else
#include "diphoton-analysis/Tools/interface/tdrstyle.hh"
#endif

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TLegend.h"
#include "TLine.h"
#include "TROOT.h"

void plot_pdf_uncert();

int main()
{

  plot_pdf_uncert();

  return 0;
}

void plot_pdf_uncert()
{
  setTDRStyle();
  gROOT->ForceStyle();
  
  std::vector<std::string> regions = {"BB", "BE"};
  std::vector<std::string> variations = {"Up", "Down"};
  std::map<std::string, TH1F*> hists;

  std::vector<std::string> orders = {"LO", "nlo"};
  for(const auto& order : orders) {
    TCanvas *c = new TCanvas(order.c_str(), order.c_str());
    for(const auto& region : regions) {
      std::string filename("data/pdf_uncert_" + order + "_" + region + ".root");
      TFile *f = TFile::Open(filename.c_str());
      for(const auto& variation : variations) {
	std::string histName(region + "/errors" + variation);
	hists[histName] = dynamic_cast<TH1F*>(f->Get(histName.c_str()));
	hists[histName]->SetDirectory(nullptr);
	if(region == "BB") hists[histName]->SetLineColor(kBlack);
	else hists[histName]->SetLineColor(kRed);

	if(hists.size() == 1 ) {
	  hists[histName]->Draw();
	  hists[histName]->SetTitle(";m_{#gamma#gamma} (GeV);PDF uncertainty");
	}
	else hists[histName]->Draw("same");
	hists[histName]->SetStats(kFALSE);
      }
    }

    TLegend *leg = new TLegend(0.25, 0.7, 0.6, 0.95);
    leg->AddEntry(hists["BB/errorsUp"], "Barrel-barrel", "L");
    leg->AddEntry(hists["BE/errorsUp"], "Barrel-endcap", "L");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    TLine *line = new TLine(500., 0., 6000., 0.);
    line->SetLineStyle(kDashed);
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw();

    c->Update();

    c->Print(Form("plots/pdf_uncertainty_band_%s.pdf", order.c_str()));

    hists.clear();
  }


}


