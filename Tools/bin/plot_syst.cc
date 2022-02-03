#ifdef __CINT__
#include "interface/sampleList.hh"
#else
#include "diphoton-analysis/Tools/interface/sampleList.hh" 
#include "diphoton-analysis/Tools/interface/utilities.hh" 
#endif

#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"

#include <string>

TH1F* plot_one(int year, int numSigma, bool endcap, const std::string& syst_type, bool unweighted = false);
void plot_syst(const std::string & syst_type);

int main(int argc, char *argv[])
{
  std::string syst_type;

  if(argc > 2) {
    std::cout << "Syntax: plot_syst.exe [egm/pileup]" << std::endl;
    return -1;
  }
  else if(argc == 2) {
    syst_type = argv[1];
  }

  plot_syst(syst_type);
}

void plot_syst(const std::string & syst_type = "egm")
{
  init();

  gStyle->SetErrorX(0.5);

  std::vector<TCanvas*> canvases;

  for (int year : {2016, 2017, 2018}) {
    for (bool endcap : {true, false} ) {
      canvases.push_back(new TCanvas(std::to_string(year).c_str(), std::to_string(year).c_str(), (int)((1./0.7)*600)));

      TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1,1);
      pad1->SetBottomMargin(0);
      pad1->Draw();

      TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1,0.3);
      pad2->SetBottomMargin(0.25);
      pad2->SetTopMargin(0);
      pad2->Draw();

      pad1->cd();

      TH1F * up1sigma = plot_one(year, 1, endcap, syst_type);
      TH1F * nominal = plot_one(year, 0, endcap, syst_type);
      TH1F * down1sigma = plot_one(year, -1, endcap, syst_type);
      TH1F * unweighted = plot_one(year, 0, endcap, syst_type, true);
      nominal->SetMarkerSize(1);
      nominal->Draw("e");
      nominal->SetTitle(";m_{#gamma#gamma} (GeV);Photons/(50 GeV)");

      unweighted->SetLineStyle(kDotted);
      unweighted->Draw("hist same");
      up1sigma->SetLineStyle(kDashed);
      up1sigma->Draw("hist same");
      down1sigma->SetLineStyle(kDashDotted);
      down1sigma->Draw("hist same");

      TLegend *leg = new TLegend(0.55, 0.5, 0.95, 0.9);
      leg->AddEntry(nominal, "Nominal", "L");
      leg->AddEntry(unweighted, "Before efficiency weighting", "L");
      leg->AddEntry(up1sigma, "Efficiency up 1#sigma", "L");
      leg->AddEntry(down1sigma, "Efficiency down 1#sigma", "L");
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      leg->Draw();


      TLatex *lat = new TLatex;
      lat->DrawLatexNDC(0.7, 0.4, std::to_string(year).c_str());
      lat->DrawLatexNDC(0.7, 0.3, endcap ? "barrel-endcap" : "barrel-barrel");

      pad2->cd();

      TH1F *ratio = dynamic_cast<TH1F*>(nominal->Clone("ratio"));
      TH1F *ratioUpError = dynamic_cast<TH1F*>(up1sigma->Clone("ratioError"));
      TH1F *ratioDownError = dynamic_cast<TH1F*>(down1sigma->Clone("ratioError"));
      ratio->GetYaxis()->SetTitle("Ratio");
      for(int i=0; i<=ratio->GetNbinsX(); i++) {
	double content = nominal->GetBinContent(i);
	double error = nominal->GetBinError(i);
	double up_content = up1sigma->GetBinContent(i);
	double down_content = down1sigma->GetBinContent(i);
	if(content != 0) {
	  ratio->SetBinContent(i, 1.0);
	  ratio->SetBinError(i, error/content);
	  ratioUpError->SetBinContent(i, up_content/content);
	  ratioDownError->SetBinContent(i, down_content/content);
	  ratioUpError->SetBinError(i, 0.0);
	  ratioDownError->SetBinError(i, 0.0);
	}
	else {
	  ratio->SetBinContent(i, 0.0);
	  ratio->SetBinError(i, 0.0);
	  ratioUpError->SetBinContent(i, 1.0);
	  ratioDownError->SetBinContent(i, 1.0);
	  ratioUpError->SetBinError(i, 0.0);
	  ratioDownError->SetBinError(i, 0.0);
	}
      }
      if(syst_type=="egm") {
	ratio->GetYaxis()->SetRangeUser(0.75, 1.25);
      }
      else {
	ratio->GetYaxis()->SetRangeUser(0.95, 1.05);
      }
      ratio->Draw();
      ratioUpError->SetMarkerSize(0);
      ratioUpError->SetLineColor(kBlack);
      ratioDownError->SetMarkerSize(0);
      ratioDownError->SetLineColor(kBlack);
      ratioDownError->SetFillColor(kWhite);
      ratioDownError->SetFillStyle(kFSolid);
      gStyle->SetErrorX(0.5);
      ratioUpError->Draw("same");
      ratioDownError->Draw("same");
      ratio->Draw("same");
      ratio->GetXaxis()->SetTitleSize(ratio->GetXaxis()->GetTitleSize()/0.7);
      ratio->GetXaxis()->SetTitleOffset(ratio->GetXaxis()->GetTitleOffset()/0.7);
      ratio->GetYaxis()->SetLabelSize(ratio->GetYaxis()->GetLabelSize()/0.7);
      ratio->GetYaxis()->SetTitleSize(ratio->GetYaxis()->GetTitleSize()/0.7);
      ratio->GetYaxis()->SetTitleOffset(ratio->GetYaxis()->GetTitleOffset()/0.7);
    
      std::string filename(syst_type + "_syst_gg_");
      filename += (endcap ? "BE_" : "BB_") + std::to_string(year) + ".pdf";
      canvases.back()->Print(filename.c_str());
      filename.replace(filename.find(".pdf"), filename.size(), ".png");
      canvases.back()->Print(filename.c_str());
    }
  }
}

TH1F* plot_one(int year, int numSigma, bool endcap, const std::string& syst_type, bool unweighted)
{
  std::map<int, std::string> sigmaLabel;
  sigmaLabel[1] = "_up1sigma";
  sigmaLabel[0] = "_nominal";
  sigmaLabel[-1] = "_down1sigma";
  if(unweighted) {
    sigmaLabel[0] = "_unweighted";
  }

  std::string pt_cut("125");
  std::string hlt_cut("HLT_DoublePhoton70 > 0");
  if(year == 2016) hlt_cut = "HLT_DoublePhoton60 > 0";
  std::string minv_cut("Diphoton.Minv > 500");
  std::string kinematic_cuts("Photon1.pt>" + pt_cut + " && Photon2.pt>" + pt_cut + "&&" + minv_cut);
  std::string id_cuts("Photon1.r9_5x5 > 0.8 && Photon2.r9_5x5 > 0.8");
  std::string eta_cuts_BB("abs(Photon1.scEta)<1.4442 && abs(Photon2.scEta)<1.4442");
  std::string eta_cuts_BE("( !(abs(Photon1.scEta)<1.4442 && abs(Photon2.scEta)<1.4442) && ((abs(Photon1.scEta)<1.4442 && (abs(Photon2.scEta)>1.566&&abs(Photon2.scEta)<2.5)) || (abs(Photon2.scEta)<1.4442 && (abs(Photon1.scEta)>1.566&&abs(Photon1.scEta)<2.5))))");
  std::string basic_cuts = hlt_cut + "&&" + kinematic_cuts + "&&" + id_cuts + "&& isGood";
  if(endcap) {
    basic_cuts += "&&" + eta_cuts_BE;
  }
  else {
    basic_cuts += "&&" + eta_cuts_BB;
  }
  
  std::string histName("hist_" + syst_type + "_" + std::to_string(year) + sigmaLabel[numSigma]);
  TH1F * hist = new TH1F(histName.c_str(), histName.c_str(), 40, 0, 2000);
  TString weight("1");
  if(!unweighted) {
    if(syst_type == "egm") {
      weight = scale_factor_cut(year, numSigma);
    }
    else if (syst_type == "pileup") {
      weight = npv_reweight_str(year, numSigma);
    }
    else {
      std::cout << "Unknown weight type" << std::endl;
    }
    std::cout << weight << std::endl;
  }
  TString allCuts = Form("(%s)*(%s)*weightAll", weight.Data(), basic_cuts.c_str());

  chains["gg_" + std::to_string(year)]->Draw(("Minv>>" + histName).c_str(), allCuts.Data(), "hist");
  
  return hist;
}
