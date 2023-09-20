#include <TCanvas.h>
#include <TPaveStats.h>
#include <TStyle.h>
#include <TH1.h>
#include <TFile.h>
#include <iostream>
#include <TROOT.h>
// #include "CMSlumi.hh"
#include <map>
#include <string>

TFile *rootfile=0;
// std::string year = "2017";
TString year = "2018";
std::string stryear = "2018";
TString yr = "18";

///eos/cms/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/DataHistogram

TH1* getHist(const char* name, int ANATYPE)
{
  rootfile=0;
  // 2016
  // 2017
  if(ANATYPE==0) rootfile=new TFile("Test"+ year +"_SMGGLOPythia.root"); // SM background done
  if(ANATYPE==1) rootfile=new TFile("Test"+ year +"_negInt-1_lT-4000.root"); //
  if(ANATYPE==2) rootfile=new TFile("Test"+ year +"_negInt-0_lT-4000.root"); //
  if(ANATYPE==3) rootfile=new TFile("Test"+ year +"_negInt-1_lT-6000.root"); //
  if(ANATYPE==4) rootfile=new TFile("Test"+ year +"_negInt-0_lT-6000.root"); //

  // if(ANATYPE==0) rootfile=new TFile(Form("Test{%s}_SMGGLOPythia.root", year).Data()); // SM background done
  // if(ANATYPE==1) rootfile=new TFile(Form("Test{%s}_negInt-1_lT-4000.root", year).Data()); //
  // if(ANATYPE==2) rootfile=new TFile(Form("Test{%s}_negInt-0_lT-4000.root", year).Data()); //
  // if(ANATYPE==3) rootfile=new TFile(Form("Test{%s}_negInt-1_lT-6000.root", year).Data()); //
  // if(ANATYPE==4) rootfile=new TFile(Form("Test{%s}_negInt-0_lT-6000.root", year).Data()); //
  // 2018

  assert(rootfile);
  rootfile->cd();
  TH1* h=dynamic_cast<TH1*>( gROOT->FindObject(name) );
  if(!h)
    std::cout << "Cannot find object " << name << std::endl;
  assert(h);
  return h;
}

TH1* combine(TH1 *hNegLo, TH1 *hPosLo, TH1 *hNegHi, TH1 *hPosHi, TH1 *hbkg, double lambdaTlo, double lambdaThi){
  TString name=hbkg->GetName();
  name+=TString("_Comb");
  TH1D* hComb=(TH1D*)hbkg->Clone(name);
  for(int bin=0; bin<=hComb->GetNbinsX()+1; bin++){
    double valLo=0.5*(hPosLo->GetBinContent(bin)+hNegLo->GetBinContent(bin))-hbkg->GetBinContent(bin);
    double valHi=0.5*(hPosHi->GetBinContent(bin)+hNegHi->GetBinContent(bin))-hbkg->GetBinContent(bin);
    valLo*=std::pow(lambdaTlo, 8);
    valHi*=std::pow(lambdaThi, 8);
    double val;
    if(hComb->GetXaxis()->GetBinLowEdge(bin)<3000.) val=valLo;
    else val=valHi;
    hComb->SetBinContent(bin, val);
  }
  return hComb;
}

void plotClockwork(void){

  std::cout << "Plotting for year " << year << std::endl;
  std::map<std::string, std::string> lumi = {
      {"2018",   "59.7"},
      {"2017",   "41.5"},
      {"2016",   "36.3"},
      {"161718", "137.6"}
  };

  std::map<std::string, double> lumiNum = {
      {"2018",   59.7},
      {"2017",   41.5},
      {"2016",   36.3},
      {"161718", 137.6}
  };

  double luminosity = lumiNum[stryear];

  TCanvas *cEBEB=new TCanvas();
  gPad->SetLogy(1);

  TH1* h500_EBEB=combine(getHist("diphotonMinvEBEB_k500",1),getHist("diphotonMinvEBEB_k500",2), getHist("diphotonMinvEBEB_k500",3), getHist("diphotonMinvEBEB_k500",4), getHist("diphotonMinvEBEB_k500",0), 4000, 6000);
  TH1* h1000_EBEB=combine(getHist("diphotonMinvEBEB_k1000",1),getHist("diphotonMinvEBEB_k1000",2), getHist("diphotonMinvEBEB_k1000",3), getHist("diphotonMinvEBEB_k1000",4), getHist("diphotonMinvEBEB_k1000",0), 4000, 6000);
  TH1* h2000_EBEB=combine(getHist("diphotonMinvEBEB_k2000",1),getHist("diphotonMinvEBEB_k2000",2), getHist("diphotonMinvEBEB_k2000",3), getHist("diphotonMinvEBEB_k2000",4), getHist("diphotonMinvEBEB_k2000",0), 4000, 6000);
  TH1* h3000_EBEB=combine(getHist("diphotonMinvEBEB_k3000",1),getHist("diphotonMinvEBEB_k3000",2), getHist("diphotonMinvEBEB_k3000",3), getHist("diphotonMinvEBEB_k3000",4), getHist("diphotonMinvEBEB_k3000",0), 4000, 6000);
  TH1* h5000_EBEB=combine(getHist("diphotonMinvEBEB_k5000",1),getHist("diphotonMinvEBEB_k5000",2), getHist("diphotonMinvEBEB_k5000",3), getHist("diphotonMinvEBEB_k5000",4), getHist("diphotonMinvEBEB_k5000",0), 4000, 6000);

  h500_EBEB->SetLineWidth(2);
  h500_EBEB->SetLineColor(kYellow);
  h500_EBEB->Rebin(4);
  // h500_EBEB->Scale(38.5);
  h500_EBEB->Scale(luminosity);
  h500_EBEB->Draw("HIST");

  h1000_EBEB->SetLineWidth(2);
  h1000_EBEB->SetLineColor(kOrange);
  h1000_EBEB->Rebin(4);
  // h1000_EBEB->Scale(38.5);
  h1000_EBEB->Scale(luminosity);
  h1000_EBEB->Draw("HIST, SAME");

  h2000_EBEB->SetLineWidth(2);
  h2000_EBEB->SetLineColor(kRed);
  h2000_EBEB->Rebin(4);
  // h2000_EBEB->Scale(38.5);
  h2000_EBEB->Scale(luminosity);
  h2000_EBEB->Draw("HIST, SAME");

  h3000_EBEB->SetLineWidth(2);
  h3000_EBEB->SetLineColor(kGreen);
  h3000_EBEB->Rebin(4);
  // h3000_EBEB->Scale(38.5);
  h3000_EBEB->Scale(luminosity);
  h3000_EBEB->Draw("HIST, SAME");

  h5000_EBEB->SetLineWidth(2);
  h5000_EBEB->SetLineColor(kBlue);
  h5000_EBEB->Rebin(4);
  // h5000_EBEB->Scale(38.5);
  h5000_EBEB->Scale(luminosity);
  h5000_EBEB->Draw("HIST, SAME");

  h500_EBEB->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV]");
  h500_EBEB->GetYaxis()->SetTitle("Events/ 200 GeV");
  h500_EBEB->SetStats(0);

  TLegend* legEBEB = new TLegend(0.55,0.55,0.85,0.67);
  legEBEB->SetBorderSize(0);
  legEBEB->SetFillColor(0);
  legEBEB->SetFillStyle(0);
  legEBEB->SetTextFont(42);
  legEBEB->SetTextSize(0.035);
  legEBEB->AddEntry(h500_EBEB, "k = 500 GeV" ,"l");
  legEBEB->AddEntry(h1000_EBEB, "k = 1000 GeV" ,"l");
  legEBEB->AddEntry(h2000_EBEB, "k = 2000 GeV" ,"l");
  legEBEB->AddEntry(h3000_EBEB, "k = 3000 GeV" ,"l");
  legEBEB->AddEntry(h5000_EBEB, "k = 5000 GeV" ,"l");
  legEBEB->Draw();

  TLatex* cmst = new TLatex(0.58, 0.82, Form("#font[61]{CMS} #font[42]{%s} #font[42]{%s}", "EBEB", stryear.c_str()));
  cmst->SetNDC();
  cmst->SetTextSize(0.06);
  cmst->Draw();

  TLatex* clockworkEBEB = new TLatex(0.58, 0.76, Form("M_{5} = 10000 GeV"));
  clockworkEBEB->SetNDC();
  clockworkEBEB->SetTextSize(0.04);
  clockworkEBEB->Draw();
  TLatex* lumit = new TLatex(0.65, 0.92, Form("#font[42]{%s fb^{-1} (13 TeV)}", lumi[stryear].c_str()));
  lumit->SetNDC();
  lumit->SetTextSize(0.04);
  lumit->Draw();


  TCanvas *cEBEE=new TCanvas();
  gPad->SetLogy(1);

  TH1* h500_EBEE=combine(getHist("diphotonMinvEBEE_k500",1),getHist("diphotonMinvEBEE_k500",2), getHist("diphotonMinvEBEE_k500",3), getHist("diphotonMinvEBEE_k500",4), getHist("diphotonMinvEBEE_k500",0), 4000, 6000);
  TH1* h1000_EBEE=combine(getHist("diphotonMinvEBEE_k1000",1),getHist("diphotonMinvEBEE_k1000",2), getHist("diphotonMinvEBEE_k1000",3), getHist("diphotonMinvEBEE_k1000",4), getHist("diphotonMinvEBEE_k1000",0), 4000, 6000);
  TH1* h2000_EBEE=combine(getHist("diphotonMinvEBEE_k2000",1),getHist("diphotonMinvEBEE_k2000",2), getHist("diphotonMinvEBEE_k2000",3), getHist("diphotonMinvEBEE_k2000",4), getHist("diphotonMinvEBEE_k2000",0), 4000, 6000);
  TH1* h3000_EBEE=combine(getHist("diphotonMinvEBEE_k3000",1),getHist("diphotonMinvEBEE_k3000",2), getHist("diphotonMinvEBEE_k3000",3), getHist("diphotonMinvEBEE_k3000",4), getHist("diphotonMinvEBEE_k3000",0), 4000, 6000);
  TH1* h5000_EBEE=combine(getHist("diphotonMinvEBEE_k5000",1),getHist("diphotonMinvEBEE_k5000",2), getHist("diphotonMinvEBEE_k5000",3), getHist("diphotonMinvEBEE_k5000",4), getHist("diphotonMinvEBEE_k5000",0), 4000, 6000);

  h500_EBEE->SetLineWidth(2);
  h500_EBEE->SetLineColor(kYellow);
  h500_EBEE->Rebin(4);
  //h500_EBEE->Scale(38.5);
  h500_EBEE->Scale(luminosity);
  h500_EBEE->Draw("HIST");

  h1000_EBEE->SetLineWidth(2);
  h1000_EBEE->SetLineColor(kOrange);
  h1000_EBEE->Rebin(4);
  //h1000_EBEE->Scale(38.5);
  h1000_EBEE->Scale(luminosity);
  h1000_EBEE->Draw("HIST, SAME");

  h2000_EBEE->SetLineWidth(2);
  h2000_EBEE->SetLineColor(kRed);
  h2000_EBEE->Rebin(4);
  //h2000_EBEE->Scale(38.5);
  h2000_EBEE->Scale(luminosity);
  h2000_EBEE->Draw("HIST, SAME");

  h3000_EBEE->SetLineWidth(2);
  h3000_EBEE->SetLineColor(kGreen);
  h3000_EBEE->Rebin(4);
  // h3000_EBEE->Scale(38.5);
  h3000_EBEE->Scale(luminosity);
  h3000_EBEE->Draw("HIST, SAME");

  h5000_EBEE->SetLineWidth(2);
  h5000_EBEE->SetLineColor(kBlue);
  h5000_EBEE->Rebin(4);
  // h5000_EBEE->Scale(38.5);
  h5000_EBEE->Scale(luminosity);
  h5000_EBEE->Draw("HIST, SAME");

  h500_EBEE->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV]");
  h500_EBEE->GetYaxis()->SetTitle("Events/ 200 GeV");
  h500_EBEE->SetStats(0);

  TLegend* leg = new TLegend(0.55,0.55,0.85,0.67);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->AddEntry(h500_EBEE, "k = 500 GeV" ,"l");
  leg->AddEntry(h1000_EBEE, "k = 1000 GeV" ,"l");
  leg->AddEntry(h2000_EBEE, "k = 2000 GeV" ,"l");
  leg->AddEntry(h3000_EBEE, "k = 3000 GeV" ,"l");
  leg->AddEntry(h5000_EBEE, "k = 5000 GeV" ,"l");
  leg->Draw();

  TLatex* cmstEBEE = new TLatex(0.58, 0.82, Form("#font[61]{CMS} #font[42]{%s} #font[42]{%s}", "EBEE", stryear.c_str()));
  cmstEBEE->SetNDC();
  cmstEBEE->SetTextSize(0.06);
  cmstEBEE->Draw();

  TLatex* clockworkEBEE = new TLatex(0.58, 0.76, Form("M_{5} = 10000 GeV"));
  clockworkEBEE->SetNDC();
  clockworkEBEE->SetTextSize(0.04);
  clockworkEBEE->Draw();

  TLatex* lumitEBEE = new TLatex(0.65, 0.92, Form("#font[42]{%s fb^{-1} (13 TeV)}", lumi[stryear].c_str()));
  lumitEBEE->SetNDC();
  lumitEBEE->SetTextSize(0.04);
  lumitEBEE->Draw();

  cEBEB->SaveAs(year + "EBEB.png");
  cEBEB->SaveAs(year + "EBEB.pdf");

  cEBEE->SaveAs(year + "EBEE.png");
  cEBEE->SaveAs(year + "EBEE.pdf");

  // ======================================================================================= EXTRA stuff ==========================

//   // vector<TString> kvalue = {"0p1", "1", "10", "100", "500", "1000", "2000", "3000", "4000", "5000"};
//   TH1* h0p1_EBEB=combine(getHist("diphotonMinvEBEB_k0p1",1),getHist("diphotonMinvEBEB_k0p1",2), getHist("diphotonMinvEBEB_k0p1",3), getHist("diphotonMinvEBEB_k0p1",4), getHist("diphotonMinvEBEB_k0p1",0), 4000, 6000);
//   TH1* h1_EBEB=combine(getHist("diphotonMinvEBEB_k1",1),getHist("diphotonMinvEBEB_k1",2), getHist("diphotonMinvEBEB_k1",3), getHist("diphotonMinvEBEB_k1",4), getHist("diphotonMinvEBEB_k1",0), 4000, 6000);
//   TH1* h10_EBEB=combine(getHist("diphotonMinvEBEB_k10",1),getHist("diphotonMinvEBEB_k10",2), getHist("diphotonMinvEBEB_k10",3), getHist("diphotonMinvEBEB_k10",4), getHist("diphotonMinvEBEB_k10",0), 4000, 6000);
//   TH1* h100_EBEB=combine(getHist("diphotonMinvEBEB_k100",1),getHist("diphotonMinvEBEB_k100",2), getHist("diphotonMinvEBEB_k100",3), getHist("diphotonMinvEBEB_k100",4), getHist("diphotonMinvEBEB_k100",0), 4000, 6000);
//   TH1* h4000_EBEB=combine(getHist("diphotonMinvEBEB_k4000",1),getHist("diphotonMinvEBEB_k4000",2), getHist("diphotonMinvEBEB_k4000",3), getHist("diphotonMinvEBEB_k4000",4), getHist("diphotonMinvEBEB_k4000",0), 4000, 6000);
//
//   TH1* h0p1_EBEE=combine(getHist("diphotonMinvEBEE_k0p1",1),getHist("diphotonMinvEBEE_k0p1",2), getHist("diphotonMinvEBEE_k0p1",3), getHist("diphotonMinvEBEE_k0p1",4), getHist("diphotonMinvEBEE_k0p1",0), 4000, 6000);
//   TH1* h1_EBEE=combine(getHist("diphotonMinvEBEE_k1",1),getHist("diphotonMinvEBEE_k1",2), getHist("diphotonMinvEBEE_k1",3), getHist("diphotonMinvEBEE_k1",4), getHist("diphotonMinvEBEE_k1",0), 4000, 6000);
//   TH1* h10_EBEE=combine(getHist("diphotonMinvEBEE_k10",1),getHist("diphotonMinvEBEE_k10",2), getHist("diphotonMinvEBEE_k10",3), getHist("diphotonMinvEBEE_k10",4), getHist("diphotonMinvEBEE_k10",0), 4000, 6000);
//   TH1* h100_EBEE=combine(getHist("diphotonMinvEBEE_k100",1),getHist("diphotonMinvEBEE_k100",2), getHist("diphotonMinvEBEE_k100",3), getHist("diphotonMinvEBEE_k100",4), getHist("diphotonMinvEBEE_k100",0), 4000, 6000);
//   TH1* h4000_EBEE=combine(getHist("diphotonMinvEBEE_k4000",1),getHist("diphotonMinvEBEE_k4000",2), getHist("diphotonMinvEBEE_k4000",3), getHist("diphotonMinvEBEE_k4000",4), getHist("diphotonMinvEBEE_k4000",0), 4000, 6000);
//
//   //====================== Systematics =======================================
//   TH1* h0p1_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k0p1_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k0p1_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k0p1_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k0p1_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k0p1_energyScaleSystUp",0), 4000, 6000);
//   TH1* h1_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k1_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k1_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k1_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k1_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k1_energyScaleSystUp",0), 4000, 6000);
//   TH1* h10_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k10_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k10_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k10_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k10_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k100_energyScaleSystUp",0), 4000, 6000);
//   TH1* h100_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k100_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k100_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k100_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k100_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k100_energyScaleSystUp",0), 4000, 6000);
//   TH1* h500_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k500_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k500_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k500_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k500_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k500_energyScaleSystUp",0), 4000, 6000);
//   TH1* h1000_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k1000_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k1000_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k1000_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k1000_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k1000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h2000_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k2000_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k2000_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k2000_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k2000_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k2000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h3000_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k3000_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k3000_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k3000_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k3000_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k3000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h4000_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k4000_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k4000_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k4000_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k4000_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k4000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h5000_EBEB_energyScaleSystUp=combine(getHist("diphotonMinvEBEB_k5000_energyScaleSystUp",1),getHist("diphotonMinvEBEB_k5000_energyScaleSystUp",2), getHist("diphotonMinvEBEB_k5000_energyScaleSystUp",3), getHist("diphotonMinvEBEB_k5000_energyScaleSystUp",4), getHist("diphotonMinvEBEB_k5000_energyScaleSystUp",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k0p1_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k0p1_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k0p1_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k0p1_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k0p1_energyScaleSystUp",0), 4000, 6000);
//   TH1* h1_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k1_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k1_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k1_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k1_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k1_energyScaleSystUp",0), 4000, 6000);
//   TH1* h10_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k10_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k10_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k10_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k10_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k10_energyScaleSystUp",0), 4000, 6000);
//   TH1* h100_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k100_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k100_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k100_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k100_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k100_energyScaleSystUp",0), 4000, 6000);
//   TH1* h500_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k500_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k500_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k500_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k500_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k500_energyScaleSystUp",0), 4000, 6000);
//   TH1* h1000_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k1000_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k1000_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k1000_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k1000_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k1000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h2000_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k2000_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k2000_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k2000_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k2000_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k2000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h3000_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k3000_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k3000_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k3000_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k3000_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k3000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h4000_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k4000_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k4000_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k4000_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k4000_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k4000_energyScaleSystUp",0), 4000, 6000);
//   TH1* h5000_EBEE_energyScaleSystUp=combine(getHist("diphotonMinvEBEE_k5000_energyScaleSystUp",1),getHist("diphotonMinvEBEE_k5000_energyScaleSystUp",2), getHist("diphotonMinvEBEE_k5000_energyScaleSystUp",3), getHist("diphotonMinvEBEE_k5000_energyScaleSystUp",4), getHist("diphotonMinvEBEE_k5000_energyScaleSystUp",0), 4000, 6000);
//
//   // == energyScaleSystDown
//   TH1* h0p1_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k0p1_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k0p1_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k0p1_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k0p1_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k0p1_energyScaleSystDown",0), 4000, 6000);
//   TH1* h1_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k1_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k1_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k1_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k1_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k1_energyScaleSystDown",0), 4000, 6000);
//   TH1* h10_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k10_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k10_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k10_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k10_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k100_energyScaleSystDown",0), 4000, 6000);
//   TH1* h100_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k100_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k100_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k100_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k100_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k100_energyScaleSystDown",0), 4000, 6000);
//   TH1* h500_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k500_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k500_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k500_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k500_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k500_energyScaleSystDown",0), 4000, 6000);
//   TH1* h1000_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k1000_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k1000_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k1000_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k1000_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k1000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h2000_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k2000_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k2000_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k2000_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k2000_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k2000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h3000_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k3000_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k3000_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k3000_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k3000_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k3000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h4000_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k4000_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k4000_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k4000_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k4000_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k4000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h5000_EBEB_energyScaleSystDown=combine(getHist("diphotonMinvEBEB_k5000_energyScaleSystDown",1),getHist("diphotonMinvEBEB_k5000_energyScaleSystDown",2), getHist("diphotonMinvEBEB_k5000_energyScaleSystDown",3), getHist("diphotonMinvEBEB_k5000_energyScaleSystDown",4), getHist("diphotonMinvEBEB_k5000_energyScaleSystDown",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k0p1_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k0p1_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k0p1_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k0p1_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k0p1_energyScaleSystDown",0), 4000, 6000);
//   TH1* h1_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k1_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k1_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k1_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k1_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k1_energyScaleSystDown",0), 4000, 6000);
//   TH1* h10_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k10_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k10_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k10_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k10_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k10_energyScaleSystDown",0), 4000, 6000);
//   TH1* h100_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k100_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k100_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k100_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k100_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k100_energyScaleSystDown",0), 4000, 6000);
//   TH1* h500_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k500_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k500_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k500_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k500_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k500_energyScaleSystDown",0), 4000, 6000);
//   TH1* h1000_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k1000_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k1000_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k1000_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k1000_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k1000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h2000_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k2000_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k2000_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k2000_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k2000_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k2000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h3000_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k3000_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k3000_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k3000_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k3000_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k3000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h4000_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k4000_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k4000_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k4000_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k4000_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k4000_energyScaleSystDown",0), 4000, 6000);
//   TH1* h5000_EBEE_energyScaleSystDown=combine(getHist("diphotonMinvEBEE_k5000_energyScaleSystDown",1),getHist("diphotonMinvEBEE_k5000_energyScaleSystDown",2), getHist("diphotonMinvEBEE_k5000_energyScaleSystDown",3), getHist("diphotonMinvEBEE_k5000_energyScaleSystDown",4), getHist("diphotonMinvEBEE_k5000_energyScaleSystDown",0), 4000, 6000);
//
//   // == energySigmaUp
//   TH1* h0p1_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k0p1_energySigmaUp",1),getHist("diphotonMinvEBEB_k0p1_energySigmaUp",2), getHist("diphotonMinvEBEB_k0p1_energySigmaUp",3), getHist("diphotonMinvEBEB_k0p1_energySigmaUp",4), getHist("diphotonMinvEBEB_k0p1_energySigmaUp",0), 4000, 6000);
//   TH1* h1_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k1_energySigmaUp",1),getHist("diphotonMinvEBEB_k1_energySigmaUp",2), getHist("diphotonMinvEBEB_k1_energySigmaUp",3), getHist("diphotonMinvEBEB_k1_energySigmaUp",4), getHist("diphotonMinvEBEB_k1_energySigmaUp",0), 4000, 6000);
//   TH1* h10_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k10_energySigmaUp",1),getHist("diphotonMinvEBEB_k10_energySigmaUp",2), getHist("diphotonMinvEBEB_k10_energySigmaUp",3), getHist("diphotonMinvEBEB_k10_energySigmaUp",4), getHist("diphotonMinvEBEB_k100_energySigmaUp",0), 4000, 6000);
//   TH1* h100_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k100_energySigmaUp",1),getHist("diphotonMinvEBEB_k100_energySigmaUp",2), getHist("diphotonMinvEBEB_k100_energySigmaUp",3), getHist("diphotonMinvEBEB_k100_energySigmaUp",4), getHist("diphotonMinvEBEB_k100_energySigmaUp",0), 4000, 6000);
//   TH1* h500_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k500_energySigmaUp",1),getHist("diphotonMinvEBEB_k500_energySigmaUp",2), getHist("diphotonMinvEBEB_k500_energySigmaUp",3), getHist("diphotonMinvEBEB_k500_energySigmaUp",4), getHist("diphotonMinvEBEB_k500_energySigmaUp",0), 4000, 6000);
//   TH1* h1000_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k1000_energySigmaUp",1),getHist("diphotonMinvEBEB_k1000_energySigmaUp",2), getHist("diphotonMinvEBEB_k1000_energySigmaUp",3), getHist("diphotonMinvEBEB_k1000_energySigmaUp",4), getHist("diphotonMinvEBEB_k1000_energySigmaUp",0), 4000, 6000);
//   TH1* h2000_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k2000_energySigmaUp",1),getHist("diphotonMinvEBEB_k2000_energySigmaUp",2), getHist("diphotonMinvEBEB_k2000_energySigmaUp",3), getHist("diphotonMinvEBEB_k2000_energySigmaUp",4), getHist("diphotonMinvEBEB_k2000_energySigmaUp",0), 4000, 6000);
//   TH1* h3000_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k3000_energySigmaUp",1),getHist("diphotonMinvEBEB_k3000_energySigmaUp",2), getHist("diphotonMinvEBEB_k3000_energySigmaUp",3), getHist("diphotonMinvEBEB_k3000_energySigmaUp",4), getHist("diphotonMinvEBEB_k3000_energySigmaUp",0), 4000, 6000);
//   TH1* h4000_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k4000_energySigmaUp",1),getHist("diphotonMinvEBEB_k4000_energySigmaUp",2), getHist("diphotonMinvEBEB_k4000_energySigmaUp",3), getHist("diphotonMinvEBEB_k4000_energySigmaUp",4), getHist("diphotonMinvEBEB_k4000_energySigmaUp",0), 4000, 6000);
//   TH1* h5000_EBEB_energySigmaUp=combine(getHist("diphotonMinvEBEB_k5000_energySigmaUp",1),getHist("diphotonMinvEBEB_k5000_energySigmaUp",2), getHist("diphotonMinvEBEB_k5000_energySigmaUp",3), getHist("diphotonMinvEBEB_k5000_energySigmaUp",4), getHist("diphotonMinvEBEB_k5000_energySigmaUp",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k0p1_energySigmaUp",1),getHist("diphotonMinvEBEE_k0p1_energySigmaUp",2), getHist("diphotonMinvEBEE_k0p1_energySigmaUp",3), getHist("diphotonMinvEBEE_k0p1_energySigmaUp",4), getHist("diphotonMinvEBEE_k0p1_energySigmaUp",0), 4000, 6000);
//   TH1* h1_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k1_energySigmaUp",1),getHist("diphotonMinvEBEE_k1_energySigmaUp",2), getHist("diphotonMinvEBEE_k1_energySigmaUp",3), getHist("diphotonMinvEBEE_k1_energySigmaUp",4), getHist("diphotonMinvEBEE_k1_energySigmaUp",0), 4000, 6000);
//   TH1* h10_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k10_energySigmaUp",1),getHist("diphotonMinvEBEE_k10_energySigmaUp",2), getHist("diphotonMinvEBEE_k10_energySigmaUp",3), getHist("diphotonMinvEBEE_k10_energySigmaUp",4), getHist("diphotonMinvEBEE_k10_energySigmaUp",0), 4000, 6000);
//   TH1* h100_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k100_energySigmaUp",1),getHist("diphotonMinvEBEE_k100_energySigmaUp",2), getHist("diphotonMinvEBEE_k100_energySigmaUp",3), getHist("diphotonMinvEBEE_k100_energySigmaUp",4), getHist("diphotonMinvEBEE_k100_energySigmaUp",0), 4000, 6000);
//   TH1* h500_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k500_energySigmaUp",1),getHist("diphotonMinvEBEE_k500_energySigmaUp",2), getHist("diphotonMinvEBEE_k500_energySigmaUp",3), getHist("diphotonMinvEBEE_k500_energySigmaUp",4), getHist("diphotonMinvEBEE_k500_energySigmaUp",0), 4000, 6000);
//   TH1* h1000_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k1000_energySigmaUp",1),getHist("diphotonMinvEBEE_k1000_energySigmaUp",2), getHist("diphotonMinvEBEE_k1000_energySigmaUp",3), getHist("diphotonMinvEBEE_k1000_energySigmaUp",4), getHist("diphotonMinvEBEE_k1000_energySigmaUp",0), 4000, 6000);
//   TH1* h2000_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k2000_energySigmaUp",1),getHist("diphotonMinvEBEE_k2000_energySigmaUp",2), getHist("diphotonMinvEBEE_k2000_energySigmaUp",3), getHist("diphotonMinvEBEE_k2000_energySigmaUp",4), getHist("diphotonMinvEBEE_k2000_energySigmaUp",0), 4000, 6000);
//   TH1* h3000_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k3000_energySigmaUp",1),getHist("diphotonMinvEBEE_k3000_energySigmaUp",2), getHist("diphotonMinvEBEE_k3000_energySigmaUp",3), getHist("diphotonMinvEBEE_k3000_energySigmaUp",4), getHist("diphotonMinvEBEE_k3000_energySigmaUp",0), 4000, 6000);
//   TH1* h4000_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k4000_energySigmaUp",1),getHist("diphotonMinvEBEE_k4000_energySigmaUp",2), getHist("diphotonMinvEBEE_k4000_energySigmaUp",3), getHist("diphotonMinvEBEE_k4000_energySigmaUp",4), getHist("diphotonMinvEBEE_k4000_energySigmaUp",0), 4000, 6000);
//   TH1* h5000_EBEE_energySigmaUp=combine(getHist("diphotonMinvEBEE_k5000_energySigmaUp",1),getHist("diphotonMinvEBEE_k5000_energySigmaUp",2), getHist("diphotonMinvEBEE_k5000_energySigmaUp",3), getHist("diphotonMinvEBEE_k5000_energySigmaUp",4), getHist("diphotonMinvEBEE_k5000_energySigmaUp",0), 4000, 6000);
//
//   // == energySigmaDown
//   TH1* h0p1_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k0p1_energySigmaDown",1),getHist("diphotonMinvEBEB_k0p1_energySigmaDown",2), getHist("diphotonMinvEBEB_k0p1_energySigmaDown",3), getHist("diphotonMinvEBEB_k0p1_energySigmaDown",4), getHist("diphotonMinvEBEB_k0p1_energySigmaDown",0), 4000, 6000);
//   TH1* h1_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k1_energySigmaDown",1),getHist("diphotonMinvEBEB_k1_energySigmaDown",2), getHist("diphotonMinvEBEB_k1_energySigmaDown",3), getHist("diphotonMinvEBEB_k1_energySigmaDown",4), getHist("diphotonMinvEBEB_k1_energySigmaDown",0), 4000, 6000);
//   TH1* h10_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k10_energySigmaDown",1),getHist("diphotonMinvEBEB_k10_energySigmaDown",2), getHist("diphotonMinvEBEB_k10_energySigmaDown",3), getHist("diphotonMinvEBEB_k10_energySigmaDown",4), getHist("diphotonMinvEBEB_k100_energySigmaDown",0), 4000, 6000);
//   TH1* h100_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k100_energySigmaDown",1),getHist("diphotonMinvEBEB_k100_energySigmaDown",2), getHist("diphotonMinvEBEB_k100_energySigmaDown",3), getHist("diphotonMinvEBEB_k100_energySigmaDown",4), getHist("diphotonMinvEBEB_k100_energySigmaDown",0), 4000, 6000);
//   TH1* h500_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k500_energySigmaDown",1),getHist("diphotonMinvEBEB_k500_energySigmaDown",2), getHist("diphotonMinvEBEB_k500_energySigmaDown",3), getHist("diphotonMinvEBEB_k500_energySigmaDown",4), getHist("diphotonMinvEBEB_k500_energySigmaDown",0), 4000, 6000);
//   TH1* h1000_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k1000_energySigmaDown",1),getHist("diphotonMinvEBEB_k1000_energySigmaDown",2), getHist("diphotonMinvEBEB_k1000_energySigmaDown",3), getHist("diphotonMinvEBEB_k1000_energySigmaDown",4), getHist("diphotonMinvEBEB_k1000_energySigmaDown",0), 4000, 6000);
//   TH1* h2000_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k2000_energySigmaDown",1),getHist("diphotonMinvEBEB_k2000_energySigmaDown",2), getHist("diphotonMinvEBEB_k2000_energySigmaDown",3), getHist("diphotonMinvEBEB_k2000_energySigmaDown",4), getHist("diphotonMinvEBEB_k2000_energySigmaDown",0), 4000, 6000);
//   TH1* h3000_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k3000_energySigmaDown",1),getHist("diphotonMinvEBEB_k3000_energySigmaDown",2), getHist("diphotonMinvEBEB_k3000_energySigmaDown",3), getHist("diphotonMinvEBEB_k3000_energySigmaDown",4), getHist("diphotonMinvEBEB_k3000_energySigmaDown",0), 4000, 6000);
//   TH1* h4000_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k4000_energySigmaDown",1),getHist("diphotonMinvEBEB_k4000_energySigmaDown",2), getHist("diphotonMinvEBEB_k4000_energySigmaDown",3), getHist("diphotonMinvEBEB_k4000_energySigmaDown",4), getHist("diphotonMinvEBEB_k4000_energySigmaDown",0), 4000, 6000);
//   TH1* h5000_EBEB_energySigmaDown=combine(getHist("diphotonMinvEBEB_k5000_energySigmaDown",1),getHist("diphotonMinvEBEB_k5000_energySigmaDown",2), getHist("diphotonMinvEBEB_k5000_energySigmaDown",3), getHist("diphotonMinvEBEB_k5000_energySigmaDown",4), getHist("diphotonMinvEBEB_k5000_energySigmaDown",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k0p1_energySigmaDown",1),getHist("diphotonMinvEBEE_k0p1_energySigmaDown",2), getHist("diphotonMinvEBEE_k0p1_energySigmaDown",3), getHist("diphotonMinvEBEE_k0p1_energySigmaDown",4), getHist("diphotonMinvEBEE_k0p1_energySigmaDown",0), 4000, 6000);
//   TH1* h1_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k1_energySigmaDown",1),getHist("diphotonMinvEBEE_k1_energySigmaDown",2), getHist("diphotonMinvEBEE_k1_energySigmaDown",3), getHist("diphotonMinvEBEE_k1_energySigmaDown",4), getHist("diphotonMinvEBEE_k1_energySigmaDown",0), 4000, 6000);
//   TH1* h10_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k10_energySigmaDown",1),getHist("diphotonMinvEBEE_k10_energySigmaDown",2), getHist("diphotonMinvEBEE_k10_energySigmaDown",3), getHist("diphotonMinvEBEE_k10_energySigmaDown",4), getHist("diphotonMinvEBEE_k10_energySigmaDown",0), 4000, 6000);
//   TH1* h100_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k100_energySigmaDown",1),getHist("diphotonMinvEBEE_k100_energySigmaDown",2), getHist("diphotonMinvEBEE_k100_energySigmaDown",3), getHist("diphotonMinvEBEE_k100_energySigmaDown",4), getHist("diphotonMinvEBEE_k100_energySigmaDown",0), 4000, 6000);
//   TH1* h500_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k500_energySigmaDown",1),getHist("diphotonMinvEBEE_k500_energySigmaDown",2), getHist("diphotonMinvEBEE_k500_energySigmaDown",3), getHist("diphotonMinvEBEE_k500_energySigmaDown",4), getHist("diphotonMinvEBEE_k500_energySigmaDown",0), 4000, 6000);
//   TH1* h1000_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k1000_energySigmaDown",1),getHist("diphotonMinvEBEE_k1000_energySigmaDown",2), getHist("diphotonMinvEBEE_k1000_energySigmaDown",3), getHist("diphotonMinvEBEE_k1000_energySigmaDown",4), getHist("diphotonMinvEBEE_k1000_energySigmaDown",0), 4000, 6000);
//   TH1* h2000_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k2000_energySigmaDown",1),getHist("diphotonMinvEBEE_k2000_energySigmaDown",2), getHist("diphotonMinvEBEE_k2000_energySigmaDown",3), getHist("diphotonMinvEBEE_k2000_energySigmaDown",4), getHist("diphotonMinvEBEE_k2000_energySigmaDown",0), 4000, 6000);
//   TH1* h3000_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k3000_energySigmaDown",1),getHist("diphotonMinvEBEE_k3000_energySigmaDown",2), getHist("diphotonMinvEBEE_k3000_energySigmaDown",3), getHist("diphotonMinvEBEE_k3000_energySigmaDown",4), getHist("diphotonMinvEBEE_k3000_energySigmaDown",0), 4000, 6000);
//   TH1* h4000_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k4000_energySigmaDown",1),getHist("diphotonMinvEBEE_k4000_energySigmaDown",2), getHist("diphotonMinvEBEE_k4000_energySigmaDown",3), getHist("diphotonMinvEBEE_k4000_energySigmaDown",4), getHist("diphotonMinvEBEE_k4000_energySigmaDown",0), 4000, 6000);
//   TH1* h5000_EBEE_energySigmaDown=combine(getHist("diphotonMinvEBEE_k5000_energySigmaDown",1),getHist("diphotonMinvEBEE_k5000_energySigmaDown",2), getHist("diphotonMinvEBEE_k5000_energySigmaDown",3), getHist("diphotonMinvEBEE_k5000_energySigmaDown",4), getHist("diphotonMinvEBEE_k5000_energySigmaDown",0), 4000, 6000);
//
//   // == energyScaleGain
//   TH1* h0p1_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k0p1_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k0p1_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k0p1_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k0p1_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k0p1_energyScaleGainUp",0), 4000, 6000);
//   TH1* h1_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k1_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k1_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k1_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k1_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k1_energyScaleGainUp",0), 4000, 6000);
//   TH1* h10_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k10_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k10_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k10_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k10_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k100_energyScaleGainUp",0), 4000, 6000);
//   TH1* h100_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k100_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k100_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k100_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k100_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k100_energyScaleGainUp",0), 4000, 6000);
//   TH1* h500_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k500_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k500_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k500_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k500_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k500_energyScaleGainUp",0), 4000, 6000);
//   TH1* h1000_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k1000_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k1000_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k1000_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k1000_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k1000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h2000_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k2000_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k2000_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k2000_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k2000_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k2000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h3000_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k3000_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k3000_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k3000_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k3000_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k3000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h4000_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k4000_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k4000_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k4000_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k4000_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k4000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h5000_EBEB_energyScaleGainUp=combine(getHist("diphotonMinvEBEB_k5000_energyScaleGainUp",1),getHist("diphotonMinvEBEB_k5000_energyScaleGainUp",2), getHist("diphotonMinvEBEB_k5000_energyScaleGainUp",3), getHist("diphotonMinvEBEB_k5000_energyScaleGainUp",4), getHist("diphotonMinvEBEB_k5000_energyScaleGainUp",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k0p1_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k0p1_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k0p1_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k0p1_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k0p1_energyScaleGainUp",0), 4000, 6000);
//   TH1* h1_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k1_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k1_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k1_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k1_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k1_energyScaleGainUp",0), 4000, 6000);
//   TH1* h10_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k10_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k10_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k10_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k10_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k10_energyScaleGainUp",0), 4000, 6000);
//   TH1* h100_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k100_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k100_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k100_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k100_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k100_energyScaleGainUp",0), 4000, 6000);
//   TH1* h500_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k500_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k500_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k500_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k500_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k500_energyScaleGainUp",0), 4000, 6000);
//   TH1* h1000_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k1000_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k1000_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k1000_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k1000_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k1000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h2000_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k2000_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k2000_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k2000_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k2000_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k2000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h3000_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k3000_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k3000_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k3000_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k3000_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k3000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h4000_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k4000_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k4000_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k4000_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k4000_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k4000_energyScaleGainUp",0), 4000, 6000);
//   TH1* h5000_EBEE_energyScaleGainUp=combine(getHist("diphotonMinvEBEE_k5000_energyScaleGainUp",1),getHist("diphotonMinvEBEE_k5000_energyScaleGainUp",2), getHist("diphotonMinvEBEE_k5000_energyScaleGainUp",3), getHist("diphotonMinvEBEE_k5000_energyScaleGainUp",4), getHist("diphotonMinvEBEE_k5000_energyScaleGainUp",0), 4000, 6000);
//
//   TH1* h0p1_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k0p1_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k0p1_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k0p1_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k0p1_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k0p1_energyScaleGainDown",0), 4000, 6000);
//   TH1* h1_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k1_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k1_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k1_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k1_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k1_energyScaleGainDown",0), 4000, 6000);
//   TH1* h10_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k10_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k10_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k10_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k10_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k100_energyScaleGainDown",0), 4000, 6000);
//   TH1* h100_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k100_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k100_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k100_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k100_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k100_energyScaleGainDown",0), 4000, 6000);
//   TH1* h500_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k500_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k500_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k500_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k500_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k500_energyScaleGainDown",0), 4000, 6000);
//   TH1* h1000_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k1000_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k1000_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k1000_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k1000_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k1000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h2000_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k2000_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k2000_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k2000_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k2000_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k2000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h3000_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k3000_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k3000_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k3000_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k3000_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k3000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h4000_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k4000_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k4000_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k4000_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k4000_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k4000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h5000_EBEB_energyScaleGainDown=combine(getHist("diphotonMinvEBEB_k5000_energyScaleGainDown",1),getHist("diphotonMinvEBEB_k5000_energyScaleGainDown",2), getHist("diphotonMinvEBEB_k5000_energyScaleGainDown",3), getHist("diphotonMinvEBEB_k5000_energyScaleGainDown",4), getHist("diphotonMinvEBEB_k5000_energyScaleGainDown",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k0p1_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k0p1_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k0p1_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k0p1_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k0p1_energyScaleGainDown",0), 4000, 6000);
//   TH1* h1_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k1_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k1_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k1_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k1_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k1_energyScaleGainDown",0), 4000, 6000);
//   TH1* h10_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k10_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k10_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k10_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k10_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k10_energyScaleGainDown",0), 4000, 6000);
//   TH1* h100_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k100_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k100_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k100_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k100_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k100_energyScaleGainDown",0), 4000, 6000);
//   TH1* h500_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k500_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k500_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k500_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k500_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k500_energyScaleGainDown",0), 4000, 6000);
//   TH1* h1000_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k1000_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k1000_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k1000_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k1000_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k1000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h2000_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k2000_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k2000_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k2000_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k2000_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k2000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h3000_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k3000_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k3000_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k3000_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k3000_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k3000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h4000_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k4000_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k4000_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k4000_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k4000_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k4000_energyScaleGainDown",0), 4000, 6000);
//   TH1* h5000_EBEE_energyScaleGainDown=combine(getHist("diphotonMinvEBEE_k5000_energyScaleGainDown",1),getHist("diphotonMinvEBEE_k5000_energyScaleGainDown",2), getHist("diphotonMinvEBEE_k5000_energyScaleGainDown",3), getHist("diphotonMinvEBEE_k5000_energyScaleGainDown",4), getHist("diphotonMinvEBEE_k5000_energyScaleGainDown",0), 4000, 6000);
//
//   // == eff
//   TH1* h0p1_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k0p1_effUp",1),getHist("diphotonMinvEBEB_k0p1_effUp",2), getHist("diphotonMinvEBEB_k0p1_effUp",3), getHist("diphotonMinvEBEB_k0p1_effUp",4), getHist("diphotonMinvEBEB_k0p1_effUp",0), 4000, 6000);
//   TH1* h1_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k1_effUp",1),getHist("diphotonMinvEBEB_k1_effUp",2), getHist("diphotonMinvEBEB_k1_effUp",3), getHist("diphotonMinvEBEB_k1_effUp",4), getHist("diphotonMinvEBEB_k1_effUp",0), 4000, 6000);
//   TH1* h10_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k10_effUp",1),getHist("diphotonMinvEBEB_k10_effUp",2), getHist("diphotonMinvEBEB_k10_effUp",3), getHist("diphotonMinvEBEB_k10_effUp",4), getHist("diphotonMinvEBEB_k100_effUp",0), 4000, 6000);
//   TH1* h100_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k100_effUp",1),getHist("diphotonMinvEBEB_k100_effUp",2), getHist("diphotonMinvEBEB_k100_effUp",3), getHist("diphotonMinvEBEB_k100_effUp",4), getHist("diphotonMinvEBEB_k100_effUp",0), 4000, 6000);
//   TH1* h500_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k500_effUp",1),getHist("diphotonMinvEBEB_k500_effUp",2), getHist("diphotonMinvEBEB_k500_effUp",3), getHist("diphotonMinvEBEB_k500_effUp",4), getHist("diphotonMinvEBEB_k500_effUp",0), 4000, 6000);
//   TH1* h1000_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k1000_effUp",1),getHist("diphotonMinvEBEB_k1000_effUp",2), getHist("diphotonMinvEBEB_k1000_effUp",3), getHist("diphotonMinvEBEB_k1000_effUp",4), getHist("diphotonMinvEBEB_k1000_effUp",0), 4000, 6000);
//   TH1* h2000_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k2000_effUp",1),getHist("diphotonMinvEBEB_k2000_effUp",2), getHist("diphotonMinvEBEB_k2000_effUp",3), getHist("diphotonMinvEBEB_k2000_effUp",4), getHist("diphotonMinvEBEB_k2000_effUp",0), 4000, 6000);
//   TH1* h3000_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k3000_effUp",1),getHist("diphotonMinvEBEB_k3000_effUp",2), getHist("diphotonMinvEBEB_k3000_effUp",3), getHist("diphotonMinvEBEB_k3000_effUp",4), getHist("diphotonMinvEBEB_k3000_effUp",0), 4000, 6000);
//   TH1* h4000_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k4000_effUp",1),getHist("diphotonMinvEBEB_k4000_effUp",2), getHist("diphotonMinvEBEB_k4000_effUp",3), getHist("diphotonMinvEBEB_k4000_effUp",4), getHist("diphotonMinvEBEB_k4000_effUp",0), 4000, 6000);
//   TH1* h5000_EBEB_effUp=combine(getHist("diphotonMinvEBEB_k5000_effUp",1),getHist("diphotonMinvEBEB_k5000_effUp",2), getHist("diphotonMinvEBEB_k5000_effUp",3), getHist("diphotonMinvEBEB_k5000_effUp",4), getHist("diphotonMinvEBEB_k5000_effUp",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k0p1_effUp",1),getHist("diphotonMinvEBEE_k0p1_effUp",2), getHist("diphotonMinvEBEE_k0p1_effUp",3), getHist("diphotonMinvEBEE_k0p1_effUp",4), getHist("diphotonMinvEBEE_k0p1_effUp",0), 4000, 6000);
//   TH1* h1_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k1_effUp",1),getHist("diphotonMinvEBEE_k1_effUp",2), getHist("diphotonMinvEBEE_k1_effUp",3), getHist("diphotonMinvEBEE_k1_effUp",4), getHist("diphotonMinvEBEE_k1_effUp",0), 4000, 6000);
//   TH1* h10_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k10_effUp",1),getHist("diphotonMinvEBEE_k10_effUp",2), getHist("diphotonMinvEBEE_k10_effUp",3), getHist("diphotonMinvEBEE_k10_effUp",4), getHist("diphotonMinvEBEE_k10_effUp",0), 4000, 6000);
//   TH1* h100_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k100_effUp",1),getHist("diphotonMinvEBEE_k100_effUp",2), getHist("diphotonMinvEBEE_k100_effUp",3), getHist("diphotonMinvEBEE_k100_effUp",4), getHist("diphotonMinvEBEE_k100_effUp",0), 4000, 6000);
//   TH1* h500_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k500_effUp",1),getHist("diphotonMinvEBEE_k500_effUp",2), getHist("diphotonMinvEBEE_k500_effUp",3), getHist("diphotonMinvEBEE_k500_effUp",4), getHist("diphotonMinvEBEE_k500_effUp",0), 4000, 6000);
//   TH1* h1000_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k1000_effUp",1),getHist("diphotonMinvEBEE_k1000_effUp",2), getHist("diphotonMinvEBEE_k1000_effUp",3), getHist("diphotonMinvEBEE_k1000_effUp",4), getHist("diphotonMinvEBEE_k1000_effUp",0), 4000, 6000);
//   TH1* h2000_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k2000_effUp",1),getHist("diphotonMinvEBEE_k2000_effUp",2), getHist("diphotonMinvEBEE_k2000_effUp",3), getHist("diphotonMinvEBEE_k2000_effUp",4), getHist("diphotonMinvEBEE_k2000_effUp",0), 4000, 6000);
//   TH1* h3000_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k3000_effUp",1),getHist("diphotonMinvEBEE_k3000_effUp",2), getHist("diphotonMinvEBEE_k3000_effUp",3), getHist("diphotonMinvEBEE_k3000_effUp",4), getHist("diphotonMinvEBEE_k3000_effUp",0), 4000, 6000);
//   TH1* h4000_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k4000_effUp",1),getHist("diphotonMinvEBEE_k4000_effUp",2), getHist("diphotonMinvEBEE_k4000_effUp",3), getHist("diphotonMinvEBEE_k4000_effUp",4), getHist("diphotonMinvEBEE_k4000_effUp",0), 4000, 6000);
//   TH1* h5000_EBEE_effUp=combine(getHist("diphotonMinvEBEE_k5000_effUp",1),getHist("diphotonMinvEBEE_k5000_effUp",2), getHist("diphotonMinvEBEE_k5000_effUp",3), getHist("diphotonMinvEBEE_k5000_effUp",4), getHist("diphotonMinvEBEE_k5000_effUp",0), 4000, 6000);
//
//   TH1* h0p1_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k0p1_effDown",1),getHist("diphotonMinvEBEB_k0p1_effDown",2), getHist("diphotonMinvEBEB_k0p1_effDown",3), getHist("diphotonMinvEBEB_k0p1_effDown",4), getHist("diphotonMinvEBEB_k0p1_effDown",0), 4000, 6000);
//   TH1* h1_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k1_effDown",1),getHist("diphotonMinvEBEB_k1_effDown",2), getHist("diphotonMinvEBEB_k1_effDown",3), getHist("diphotonMinvEBEB_k1_effDown",4), getHist("diphotonMinvEBEB_k1_effDown",0), 4000, 6000);
//   TH1* h10_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k10_effDown",1),getHist("diphotonMinvEBEB_k10_effDown",2), getHist("diphotonMinvEBEB_k10_effDown",3), getHist("diphotonMinvEBEB_k10_effDown",4), getHist("diphotonMinvEBEB_k100_effDown",0), 4000, 6000);
//   TH1* h100_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k100_effDown",1),getHist("diphotonMinvEBEB_k100_effDown",2), getHist("diphotonMinvEBEB_k100_effDown",3), getHist("diphotonMinvEBEB_k100_effDown",4), getHist("diphotonMinvEBEB_k100_effDown",0), 4000, 6000);
//   TH1* h500_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k500_effDown",1),getHist("diphotonMinvEBEB_k500_effDown",2), getHist("diphotonMinvEBEB_k500_effDown",3), getHist("diphotonMinvEBEB_k500_effDown",4), getHist("diphotonMinvEBEB_k500_effDown",0), 4000, 6000);
//   TH1* h1000_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k1000_effDown",1),getHist("diphotonMinvEBEB_k1000_effDown",2), getHist("diphotonMinvEBEB_k1000_effDown",3), getHist("diphotonMinvEBEB_k1000_effDown",4), getHist("diphotonMinvEBEB_k1000_effDown",0), 4000, 6000);
//   TH1* h2000_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k2000_effDown",1),getHist("diphotonMinvEBEB_k2000_effDown",2), getHist("diphotonMinvEBEB_k2000_effDown",3), getHist("diphotonMinvEBEB_k2000_effDown",4), getHist("diphotonMinvEBEB_k2000_effDown",0), 4000, 6000);
//   TH1* h3000_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k3000_effDown",1),getHist("diphotonMinvEBEB_k3000_effDown",2), getHist("diphotonMinvEBEB_k3000_effDown",3), getHist("diphotonMinvEBEB_k3000_effDown",4), getHist("diphotonMinvEBEB_k3000_effDown",0), 4000, 6000);
//   TH1* h4000_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k4000_effDown",1),getHist("diphotonMinvEBEB_k4000_effDown",2), getHist("diphotonMinvEBEB_k4000_effDown",3), getHist("diphotonMinvEBEB_k4000_effDown",4), getHist("diphotonMinvEBEB_k4000_effDown",0), 4000, 6000);
//   TH1* h5000_EBEB_effDown=combine(getHist("diphotonMinvEBEB_k5000_effDown",1),getHist("diphotonMinvEBEB_k5000_effDown",2), getHist("diphotonMinvEBEB_k5000_effDown",3), getHist("diphotonMinvEBEB_k5000_effDown",4), getHist("diphotonMinvEBEB_k5000_effDown",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k0p1_effDown",1),getHist("diphotonMinvEBEE_k0p1_effDown",2), getHist("diphotonMinvEBEE_k0p1_effDown",3), getHist("diphotonMinvEBEE_k0p1_effDown",4), getHist("diphotonMinvEBEE_k0p1_effDown",0), 4000, 6000);
//   TH1* h1_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k1_effDown",1),getHist("diphotonMinvEBEE_k1_effDown",2), getHist("diphotonMinvEBEE_k1_effDown",3), getHist("diphotonMinvEBEE_k1_effDown",4), getHist("diphotonMinvEBEE_k1_effDown",0), 4000, 6000);
//   TH1* h10_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k10_effDown",1),getHist("diphotonMinvEBEE_k10_effDown",2), getHist("diphotonMinvEBEE_k10_effDown",3), getHist("diphotonMinvEBEE_k10_effDown",4), getHist("diphotonMinvEBEE_k10_effDown",0), 4000, 6000);
//   TH1* h100_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k100_effDown",1),getHist("diphotonMinvEBEE_k100_effDown",2), getHist("diphotonMinvEBEE_k100_effDown",3), getHist("diphotonMinvEBEE_k100_effDown",4), getHist("diphotonMinvEBEE_k100_effDown",0), 4000, 6000);
//   TH1* h500_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k500_effDown",1),getHist("diphotonMinvEBEE_k500_effDown",2), getHist("diphotonMinvEBEE_k500_effDown",3), getHist("diphotonMinvEBEE_k500_effDown",4), getHist("diphotonMinvEBEE_k500_effDown",0), 4000, 6000);
//   TH1* h1000_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k1000_effDown",1),getHist("diphotonMinvEBEE_k1000_effDown",2), getHist("diphotonMinvEBEE_k1000_effDown",3), getHist("diphotonMinvEBEE_k1000_effDown",4), getHist("diphotonMinvEBEE_k1000_effDown",0), 4000, 6000);
//   TH1* h2000_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k2000_effDown",1),getHist("diphotonMinvEBEE_k2000_effDown",2), getHist("diphotonMinvEBEE_k2000_effDown",3), getHist("diphotonMinvEBEE_k2000_effDown",4), getHist("diphotonMinvEBEE_k2000_effDown",0), 4000, 6000);
//   TH1* h3000_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k3000_effDown",1),getHist("diphotonMinvEBEE_k3000_effDown",2), getHist("diphotonMinvEBEE_k3000_effDown",3), getHist("diphotonMinvEBEE_k3000_effDown",4), getHist("diphotonMinvEBEE_k3000_effDown",0), 4000, 6000);
//   TH1* h4000_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k4000_effDown",1),getHist("diphotonMinvEBEE_k4000_effDown",2), getHist("diphotonMinvEBEE_k4000_effDown",3), getHist("diphotonMinvEBEE_k4000_effDown",4), getHist("diphotonMinvEBEE_k4000_effDown",0), 4000, 6000);
//   TH1* h5000_EBEE_effDown=combine(getHist("diphotonMinvEBEE_k5000_effDown",1),getHist("diphotonMinvEBEE_k5000_effDown",2), getHist("diphotonMinvEBEE_k5000_effDown",3), getHist("diphotonMinvEBEE_k5000_effDown",4), getHist("diphotonMinvEBEE_k5000_effDown",0), 4000, 6000);
//
//   // == pileup
//   TH1* h0p1_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k0p1_pileupUp",1),getHist("diphotonMinvEBEB_k0p1_pileupUp",2), getHist("diphotonMinvEBEB_k0p1_pileupUp",3), getHist("diphotonMinvEBEB_k0p1_pileupUp",4), getHist("diphotonMinvEBEB_k0p1_pileupUp",0), 4000, 6000);
//   TH1* h1_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k1_pileupUp",1),getHist("diphotonMinvEBEB_k1_pileupUp",2), getHist("diphotonMinvEBEB_k1_pileupUp",3), getHist("diphotonMinvEBEB_k1_pileupUp",4), getHist("diphotonMinvEBEB_k1_pileupUp",0), 4000, 6000);
//   TH1* h10_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k10_pileupUp",1),getHist("diphotonMinvEBEB_k10_pileupUp",2), getHist("diphotonMinvEBEB_k10_pileupUp",3), getHist("diphotonMinvEBEB_k10_pileupUp",4), getHist("diphotonMinvEBEB_k100_pileupUp",0), 4000, 6000);
//   TH1* h100_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k100_pileupUp",1),getHist("diphotonMinvEBEB_k100_pileupUp",2), getHist("diphotonMinvEBEB_k100_pileupUp",3), getHist("diphotonMinvEBEB_k100_pileupUp",4), getHist("diphotonMinvEBEB_k100_pileupUp",0), 4000, 6000);
//   TH1* h500_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k500_pileupUp",1),getHist("diphotonMinvEBEB_k500_pileupUp",2), getHist("diphotonMinvEBEB_k500_pileupUp",3), getHist("diphotonMinvEBEB_k500_pileupUp",4), getHist("diphotonMinvEBEB_k500_pileupUp",0), 4000, 6000);
//   TH1* h1000_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k1000_pileupUp",1),getHist("diphotonMinvEBEB_k1000_pileupUp",2), getHist("diphotonMinvEBEB_k1000_pileupUp",3), getHist("diphotonMinvEBEB_k1000_pileupUp",4), getHist("diphotonMinvEBEB_k1000_pileupUp",0), 4000, 6000);
//   TH1* h2000_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k2000_pileupUp",1),getHist("diphotonMinvEBEB_k2000_pileupUp",2), getHist("diphotonMinvEBEB_k2000_pileupUp",3), getHist("diphotonMinvEBEB_k2000_pileupUp",4), getHist("diphotonMinvEBEB_k2000_pileupUp",0), 4000, 6000);
//   TH1* h3000_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k3000_pileupUp",1),getHist("diphotonMinvEBEB_k3000_pileupUp",2), getHist("diphotonMinvEBEB_k3000_pileupUp",3), getHist("diphotonMinvEBEB_k3000_pileupUp",4), getHist("diphotonMinvEBEB_k3000_pileupUp",0), 4000, 6000);
//   TH1* h4000_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k4000_pileupUp",1),getHist("diphotonMinvEBEB_k4000_pileupUp",2), getHist("diphotonMinvEBEB_k4000_pileupUp",3), getHist("diphotonMinvEBEB_k4000_pileupUp",4), getHist("diphotonMinvEBEB_k4000_pileupUp",0), 4000, 6000);
//   TH1* h5000_EBEB_pileupUp=combine(getHist("diphotonMinvEBEB_k5000_pileupUp",1),getHist("diphotonMinvEBEB_k5000_pileupUp",2), getHist("diphotonMinvEBEB_k5000_pileupUp",3), getHist("diphotonMinvEBEB_k5000_pileupUp",4), getHist("diphotonMinvEBEB_k5000_pileupUp",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k0p1_pileupUp",1),getHist("diphotonMinvEBEE_k0p1_pileupUp",2), getHist("diphotonMinvEBEE_k0p1_pileupUp",3), getHist("diphotonMinvEBEE_k0p1_pileupUp",4), getHist("diphotonMinvEBEE_k0p1_pileupUp",0), 4000, 6000);
//   TH1* h1_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k1_pileupUp",1),getHist("diphotonMinvEBEE_k1_pileupUp",2), getHist("diphotonMinvEBEE_k1_pileupUp",3), getHist("diphotonMinvEBEE_k1_pileupUp",4), getHist("diphotonMinvEBEE_k1_pileupUp",0), 4000, 6000);
//   TH1* h10_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k10_pileupUp",1),getHist("diphotonMinvEBEE_k10_pileupUp",2), getHist("diphotonMinvEBEE_k10_pileupUp",3), getHist("diphotonMinvEBEE_k10_pileupUp",4), getHist("diphotonMinvEBEE_k10_pileupUp",0), 4000, 6000);
//   TH1* h100_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k100_pileupUp",1),getHist("diphotonMinvEBEE_k100_pileupUp",2), getHist("diphotonMinvEBEE_k100_pileupUp",3), getHist("diphotonMinvEBEE_k100_pileupUp",4), getHist("diphotonMinvEBEE_k100_pileupUp",0), 4000, 6000);
//   TH1* h500_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k500_pileupUp",1),getHist("diphotonMinvEBEE_k500_pileupUp",2), getHist("diphotonMinvEBEE_k500_pileupUp",3), getHist("diphotonMinvEBEE_k500_pileupUp",4), getHist("diphotonMinvEBEE_k500_pileupUp",0), 4000, 6000);
//   TH1* h1000_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k1000_pileupUp",1),getHist("diphotonMinvEBEE_k1000_pileupUp",2), getHist("diphotonMinvEBEE_k1000_pileupUp",3), getHist("diphotonMinvEBEE_k1000_pileupUp",4), getHist("diphotonMinvEBEE_k1000_pileupUp",0), 4000, 6000);
//   TH1* h2000_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k2000_pileupUp",1),getHist("diphotonMinvEBEE_k2000_pileupUp",2), getHist("diphotonMinvEBEE_k2000_pileupUp",3), getHist("diphotonMinvEBEE_k2000_pileupUp",4), getHist("diphotonMinvEBEE_k2000_pileupUp",0), 4000, 6000);
//   TH1* h3000_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k3000_pileupUp",1),getHist("diphotonMinvEBEE_k3000_pileupUp",2), getHist("diphotonMinvEBEE_k3000_pileupUp",3), getHist("diphotonMinvEBEE_k3000_pileupUp",4), getHist("diphotonMinvEBEE_k3000_pileupUp",0), 4000, 6000);
//   TH1* h4000_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k4000_pileupUp",1),getHist("diphotonMinvEBEE_k4000_pileupUp",2), getHist("diphotonMinvEBEE_k4000_pileupUp",3), getHist("diphotonMinvEBEE_k4000_pileupUp",4), getHist("diphotonMinvEBEE_k4000_pileupUp",0), 4000, 6000);
//   TH1* h5000_EBEE_pileupUp=combine(getHist("diphotonMinvEBEE_k5000_pileupUp",1),getHist("diphotonMinvEBEE_k5000_pileupUp",2), getHist("diphotonMinvEBEE_k5000_pileupUp",3), getHist("diphotonMinvEBEE_k5000_pileupUp",4), getHist("diphotonMinvEBEE_k5000_pileupUp",0), 4000, 6000);
//
//   TH1* h0p1_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k0p1_pileupDown",1),getHist("diphotonMinvEBEB_k0p1_pileupDown",2), getHist("diphotonMinvEBEB_k0p1_pileupDown",3), getHist("diphotonMinvEBEB_k0p1_pileupDown",4), getHist("diphotonMinvEBEB_k0p1_pileupDown",0), 4000, 6000);
//   TH1* h1_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k1_pileupDown",1),getHist("diphotonMinvEBEB_k1_pileupDown",2), getHist("diphotonMinvEBEB_k1_pileupDown",3), getHist("diphotonMinvEBEB_k1_pileupDown",4), getHist("diphotonMinvEBEB_k1_pileupDown",0), 4000, 6000);
//   TH1* h10_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k10_pileupDown",1),getHist("diphotonMinvEBEB_k10_pileupDown",2), getHist("diphotonMinvEBEB_k10_pileupDown",3), getHist("diphotonMinvEBEB_k10_pileupDown",4), getHist("diphotonMinvEBEB_k100_pileupDown",0), 4000, 6000);
//   TH1* h100_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k100_pileupDown",1),getHist("diphotonMinvEBEB_k100_pileupDown",2), getHist("diphotonMinvEBEB_k100_pileupDown",3), getHist("diphotonMinvEBEB_k100_pileupDown",4), getHist("diphotonMinvEBEB_k100_pileupDown",0), 4000, 6000);
//   TH1* h500_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k500_pileupDown",1),getHist("diphotonMinvEBEB_k500_pileupDown",2), getHist("diphotonMinvEBEB_k500_pileupDown",3), getHist("diphotonMinvEBEB_k500_pileupDown",4), getHist("diphotonMinvEBEB_k500_pileupDown",0), 4000, 6000);
//   TH1* h1000_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k1000_pileupDown",1),getHist("diphotonMinvEBEB_k1000_pileupDown",2), getHist("diphotonMinvEBEB_k1000_pileupDown",3), getHist("diphotonMinvEBEB_k1000_pileupDown",4), getHist("diphotonMinvEBEB_k1000_pileupDown",0), 4000, 6000);
//   TH1* h2000_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k2000_pileupDown",1),getHist("diphotonMinvEBEB_k2000_pileupDown",2), getHist("diphotonMinvEBEB_k2000_pileupDown",3), getHist("diphotonMinvEBEB_k2000_pileupDown",4), getHist("diphotonMinvEBEB_k2000_pileupDown",0), 4000, 6000);
//   TH1* h3000_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k3000_pileupDown",1),getHist("diphotonMinvEBEB_k3000_pileupDown",2), getHist("diphotonMinvEBEB_k3000_pileupDown",3), getHist("diphotonMinvEBEB_k3000_pileupDown",4), getHist("diphotonMinvEBEB_k3000_pileupDown",0), 4000, 6000);
//   TH1* h4000_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k4000_pileupDown",1),getHist("diphotonMinvEBEB_k4000_pileupDown",2), getHist("diphotonMinvEBEB_k4000_pileupDown",3), getHist("diphotonMinvEBEB_k4000_pileupDown",4), getHist("diphotonMinvEBEB_k4000_pileupDown",0), 4000, 6000);
//   TH1* h5000_EBEB_pileupDown=combine(getHist("diphotonMinvEBEB_k5000_pileupDown",1),getHist("diphotonMinvEBEB_k5000_pileupDown",2), getHist("diphotonMinvEBEB_k5000_pileupDown",3), getHist("diphotonMinvEBEB_k5000_pileupDown",4), getHist("diphotonMinvEBEB_k5000_pileupDown",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k0p1_pileupDown",1),getHist("diphotonMinvEBEE_k0p1_pileupDown",2), getHist("diphotonMinvEBEE_k0p1_pileupDown",3), getHist("diphotonMinvEBEE_k0p1_pileupDown",4), getHist("diphotonMinvEBEE_k0p1_pileupDown",0), 4000, 6000);
//   TH1* h1_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k1_pileupDown",1),getHist("diphotonMinvEBEE_k1_pileupDown",2), getHist("diphotonMinvEBEE_k1_pileupDown",3), getHist("diphotonMinvEBEE_k1_pileupDown",4), getHist("diphotonMinvEBEE_k1_pileupDown",0), 4000, 6000);
//   TH1* h10_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k10_pileupDown",1),getHist("diphotonMinvEBEE_k10_pileupDown",2), getHist("diphotonMinvEBEE_k10_pileupDown",3), getHist("diphotonMinvEBEE_k10_pileupDown",4), getHist("diphotonMinvEBEE_k10_pileupDown",0), 4000, 6000);
//   TH1* h100_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k100_pileupDown",1),getHist("diphotonMinvEBEE_k100_pileupDown",2), getHist("diphotonMinvEBEE_k100_pileupDown",3), getHist("diphotonMinvEBEE_k100_pileupDown",4), getHist("diphotonMinvEBEE_k100_pileupDown",0), 4000, 6000);
//   TH1* h500_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k500_pileupDown",1),getHist("diphotonMinvEBEE_k500_pileupDown",2), getHist("diphotonMinvEBEE_k500_pileupDown",3), getHist("diphotonMinvEBEE_k500_pileupDown",4), getHist("diphotonMinvEBEE_k500_pileupDown",0), 4000, 6000);
//   TH1* h1000_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k1000_pileupDown",1),getHist("diphotonMinvEBEE_k1000_pileupDown",2), getHist("diphotonMinvEBEE_k1000_pileupDown",3), getHist("diphotonMinvEBEE_k1000_pileupDown",4), getHist("diphotonMinvEBEE_k1000_pileupDown",0), 4000, 6000);
//   TH1* h2000_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k2000_pileupDown",1),getHist("diphotonMinvEBEE_k2000_pileupDown",2), getHist("diphotonMinvEBEE_k2000_pileupDown",3), getHist("diphotonMinvEBEE_k2000_pileupDown",4), getHist("diphotonMinvEBEE_k2000_pileupDown",0), 4000, 6000);
//   TH1* h3000_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k3000_pileupDown",1),getHist("diphotonMinvEBEE_k3000_pileupDown",2), getHist("diphotonMinvEBEE_k3000_pileupDown",3), getHist("diphotonMinvEBEE_k3000_pileupDown",4), getHist("diphotonMinvEBEE_k3000_pileupDown",0), 4000, 6000);
//   TH1* h4000_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k4000_pileupDown",1),getHist("diphotonMinvEBEE_k4000_pileupDown",2), getHist("diphotonMinvEBEE_k4000_pileupDown",3), getHist("diphotonMinvEBEE_k4000_pileupDown",4), getHist("diphotonMinvEBEE_k4000_pileupDown",0), 4000, 6000);
//   TH1* h5000_EBEE_pileupDown=combine(getHist("diphotonMinvEBEE_k5000_pileupDown",1),getHist("diphotonMinvEBEE_k5000_pileupDown",2), getHist("diphotonMinvEBEE_k5000_pileupDown",3), getHist("diphotonMinvEBEE_k5000_pileupDown",4), getHist("diphotonMinvEBEE_k5000_pileupDown",0), 4000, 6000);

//   // pileUpNom
//   TH1* h0p1_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k0p1_pileupNom",1),getHist("diphotonMinvEBEB_k0p1_pileupNom",2), getHist("diphotonMinvEBEB_k0p1_pileupNom",3), getHist("diphotonMinvEBEB_k0p1_pileupNom",4), getHist("diphotonMinvEBEB_k0p1_pileupNom",0), 4000, 6000);
//   TH1* h1_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k1_pileupNom",1),getHist("diphotonMinvEBEB_k1_pileupNom",2), getHist("diphotonMinvEBEB_k1_pileupNom",3), getHist("diphotonMinvEBEB_k1_pileupNom",4), getHist("diphotonMinvEBEB_k1_pileupNom",0), 4000, 6000);
//   TH1* h10_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k10_pileupNom",1),getHist("diphotonMinvEBEB_k10_pileupNom",2), getHist("diphotonMinvEBEB_k10_pileupNom",3), getHist("diphotonMinvEBEB_k10_pileupNom",4), getHist("diphotonMinvEBEB_k100_pileupNom",0), 4000, 6000);
//   TH1* h100_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k100_pileupNom",1),getHist("diphotonMinvEBEB_k100_pileupNom",2), getHist("diphotonMinvEBEB_k100_pileupNom",3), getHist("diphotonMinvEBEB_k100_pileupNom",4), getHist("diphotonMinvEBEB_k100_pileupNom",0), 4000, 6000);
//   TH1* h500_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k500_pileupNom",1),getHist("diphotonMinvEBEB_k500_pileupNom",2), getHist("diphotonMinvEBEB_k500_pileupNom",3), getHist("diphotonMinvEBEB_k500_pileupNom",4), getHist("diphotonMinvEBEB_k500_pileupNom",0), 4000, 6000);
//   TH1* h1000_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k1000_pileupNom",1),getHist("diphotonMinvEBEB_k1000_pileupNom",2), getHist("diphotonMinvEBEB_k1000_pileupNom",3), getHist("diphotonMinvEBEB_k1000_pileupNom",4), getHist("diphotonMinvEBEB_k1000_pileupNom",0), 4000, 6000);
//   TH1* h2000_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k2000_pileupNom",1),getHist("diphotonMinvEBEB_k2000_pileupNom",2), getHist("diphotonMinvEBEB_k2000_pileupNom",3), getHist("diphotonMinvEBEB_k2000_pileupNom",4), getHist("diphotonMinvEBEB_k2000_pileupNom",0), 4000, 6000);
//   TH1* h3000_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k3000_pileupNom",1),getHist("diphotonMinvEBEB_k3000_pileupNom",2), getHist("diphotonMinvEBEB_k3000_pileupNom",3), getHist("diphotonMinvEBEB_k3000_pileupNom",4), getHist("diphotonMinvEBEB_k3000_pileupNom",0), 4000, 6000);
//   TH1* h4000_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k4000_pileupNom",1),getHist("diphotonMinvEBEB_k4000_pileupNom",2), getHist("diphotonMinvEBEB_k4000_pileupNom",3), getHist("diphotonMinvEBEB_k4000_pileupNom",4), getHist("diphotonMinvEBEB_k4000_pileupNom",0), 4000, 6000);
//   TH1* h5000_EBEB_pileupNom=combine(getHist("diphotonMinvEBEB_k5000_pileupNom",1),getHist("diphotonMinvEBEB_k5000_pileupNom",2), getHist("diphotonMinvEBEB_k5000_pileupNom",3), getHist("diphotonMinvEBEB_k5000_pileupNom",4), getHist("diphotonMinvEBEB_k5000_pileupNom",0), 4000, 6000);
// //
//   TH1* h0p1_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k0p1_pileupNom",1),getHist("diphotonMinvEBEE_k0p1_pileupNom",2), getHist("diphotonMinvEBEE_k0p1_pileupNom",3), getHist("diphotonMinvEBEE_k0p1_pileupNom",4), getHist("diphotonMinvEBEE_k0p1_pileupNom",0), 4000, 6000);
//   TH1* h1_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k1_pileupNom",1),getHist("diphotonMinvEBEE_k1_pileupNom",2), getHist("diphotonMinvEBEE_k1_pileupNom",3), getHist("diphotonMinvEBEE_k1_pileupNom",4), getHist("diphotonMinvEBEE_k1_pileupNom",0), 4000, 6000);
//   TH1* h10_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k10_pileupNom",1),getHist("diphotonMinvEBEE_k10_pileupNom",2), getHist("diphotonMinvEBEE_k10_pileupNom",3), getHist("diphotonMinvEBEE_k10_pileupNom",4), getHist("diphotonMinvEBEE_k10_pileupNom",0), 4000, 6000);
//   TH1* h100_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k100_pileupNom",1),getHist("diphotonMinvEBEE_k100_pileupNom",2), getHist("diphotonMinvEBEE_k100_pileupNom",3), getHist("diphotonMinvEBEE_k100_pileupNom",4), getHist("diphotonMinvEBEE_k100_pileupNom",0), 4000, 6000);
//   TH1* h500_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k500_pileupNom",1),getHist("diphotonMinvEBEE_k500_pileupNom",2), getHist("diphotonMinvEBEE_k500_pileupNom",3), getHist("diphotonMinvEBEE_k500_pileupNom",4), getHist("diphotonMinvEBEE_k500_pileupNom",0), 4000, 6000);
//   TH1* h1000_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k1000_pileupNom",1),getHist("diphotonMinvEBEE_k1000_pileupNom",2), getHist("diphotonMinvEBEE_k1000_pileupNom",3), getHist("diphotonMinvEBEE_k1000_pileupNom",4), getHist("diphotonMinvEBEE_k1000_pileupNom",0), 4000, 6000);
//   TH1* h2000_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k2000_pileupNom",1),getHist("diphotonMinvEBEE_k2000_pileupNom",2), getHist("diphotonMinvEBEE_k2000_pileupNom",3), getHist("diphotonMinvEBEE_k2000_pileupNom",4), getHist("diphotonMinvEBEE_k2000_pileupNom",0), 4000, 6000);
//   TH1* h3000_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k3000_pileupNom",1),getHist("diphotonMinvEBEE_k3000_pileupNom",2), getHist("diphotonMinvEBEE_k3000_pileupNom",3), getHist("diphotonMinvEBEE_k3000_pileupNom",4), getHist("diphotonMinvEBEE_k3000_pileupNom",0), 4000, 6000);
//   TH1* h4000_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k4000_pileupNom",1),getHist("diphotonMinvEBEE_k4000_pileupNom",2), getHist("diphotonMinvEBEE_k4000_pileupNom",3), getHist("diphotonMinvEBEE_k4000_pileupNom",4), getHist("diphotonMinvEBEE_k4000_pileupNom",0), 4000, 6000);
//   TH1* h5000_EBEE_pileupNom=combine(getHist("diphotonMinvEBEE_k5000_pileupNom",1),getHist("diphotonMinvEBEE_k5000_pileupNom",2), getHist("diphotonMinvEBEE_k5000_pileupNom",3), getHist("diphotonMinvEBEE_k5000_pileupNom",4), getHist("diphotonMinvEBEE_k5000_pileupNom",0), 4000, 6000);

  //====================== Input to Limits Code =======================================

  // TString outputfilenameBB = "BB"+ year +"_Clockwork.root";
  // TFile* outputFileBB = new TFile(outputfilenameBB, "RECREATE");
  //
  // //ADD_new_name = "%s%s__ADDNegInt%sLT%s" %(region, year[2:], NegInt, LambdaT)
  // h500_EBEB->SetName("BB"+yr+"__CWk500");
  // h1000_EBEB->SetName("BB"+yr+"__CWk1000");
  // h2000_EBEB->SetName("BB"+yr+"__CWk2000");
  // h3000_EBEB->SetName("BB"+yr+"__CWk3000");
  // h5000_EBEB->SetName("BB"+yr+"__CWk5000");
  //
  // h0p1_EBEB->SetName("BB"+yr+"__CWk0p1");
  // h1_EBEB->SetName("BB"+yr+"__CWk1");
  // h10_EBEB->SetName("BB"+yr+"__CWk10");
  // h100_EBEB->SetName("BB"+yr+"__CWk100");
  // h4000_EBEB->SetName("BB"+yr+"__CWk4000");
  //
  // h0p1_EBEB->Scale(luminosity);
  // h1_EBEB->Scale(luminosity);
  // h10_EBEB->Scale(luminosity);
  // h100_EBEB->Scale(luminosity);
  // h4000_EBEB->Scale(luminosity);
  //
  // h0p1_EBEB->Write();
  // h1_EBEB->Write();
  // h10_EBEB->Write();
  // h100_EBEB->Write();
  // h500_EBEB->Write();
  // h1000_EBEB->Write();
  // h2000_EBEB->Write();
  // h3000_EBEB->Write();
  // h4000_EBEB->Write();
  // h5000_EBEB->Write();
  //
  // // Systematics
  //
  // // SetName Systematics
  // h0p1_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk0p1__energyScaleSyst__plus");
  // h1_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk1__energyScaleSyst__plus");
  // h10_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk10__energyScaleSyst__plus");
  // h100_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk100__energyScaleSyst__plus");
  // h500_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk500__energyScaleSyst__plus");
  // h1000_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk1000__energyScaleSyst__plus");
  // h2000_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk2000__energyScaleSyst__plus");
  // h3000_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk3000__energyScaleSyst__plus");
  // h4000_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk4000__energyScaleSyst__plus");
  // h5000_EBEB_energyScaleSystUp->SetName("BB"+yr+"__CWk5000__energyScaleSyst__plus");
  //
  // h0p1_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk0p1__energySigma__plus");
  // h1_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk1__energySigma__plus");
  // h10_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk10__energySigma__plus");
  // h100_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk100__energySigma__plus");
  // h500_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk500__energySigma__plus");
  // h1000_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk1000__energySigma__plus");
  // h2000_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk2000__energySigma__plus");
  // h3000_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk3000__energySigma__plus");
  // h4000_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk4000__energySigma__plus");
  // h5000_EBEB_energySigmaUp->SetName("BB"+yr+"__CWk5000__energySigma__plus");
  //
  // h0p1_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk0p1__energyScaleGain__plus");
  // h1_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk1__energyScaleGain__plus");
  // h10_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk10__energyScaleGain__plus");
  // h100_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk100__energyScaleGain__plus");
  // h500_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk500__energyScaleGain__plus");
  // h1000_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk1000__energyScaleGain__plus");
  // h2000_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk2000__energyScaleGain__plus");
  // h3000_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk3000__energyScaleGain__plus");
  // h4000_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk4000__energyScaleGain__plus");
  // h5000_EBEB_energyScaleGainUp->SetName("BB"+yr+"__CWk5000__energyScaleGain__plus");
  //
  // h0p1_EBEB_effUp->SetName("BB"+yr+"__CWk0p1__eff__plus");
  // h1_EBEB_effUp->SetName("BB"+yr+"__CWk1__eff__plus");
  // h10_EBEB_effUp->SetName("BB"+yr+"__CWk10__eff__plus");
  // h100_EBEB_effUp->SetName("BB"+yr+"__CWk100__eff__plus");
  // h500_EBEB_effUp->SetName("BB"+yr+"__CWk500__eff__plus");
  // h1000_EBEB_effUp->SetName("BB"+yr+"__CWk1000__eff__plus");
  // h2000_EBEB_effUp->SetName("BB"+yr+"__CWk2000__eff__plus");
  // h3000_EBEB_effUp->SetName("BB"+yr+"__CWk3000__eff__plus");
  // h4000_EBEB_effUp->SetName("BB"+yr+"__CWk4000__eff__plus");
  // h5000_EBEB_effUp->SetName("BB"+yr+"__CWk5000__eff__plus");
  //
  // h0p1_EBEB_pileupUp->SetName("BB"+yr+"__CWk0p1__pileup__plus");
  // h1_EBEB_pileupUp->SetName("BB"+yr+"__CWk1__pileup__plus");
  // h10_EBEB_pileupUp->SetName("BB"+yr+"__CWk10__pileup__plus");
  // h100_EBEB_pileupUp->SetName("BB"+yr+"__CWk100__pileup__plus");
  // h500_EBEB_pileupUp->SetName("BB"+yr+"__CWk500__pileup__plus");
  // h1000_EBEB_pileupUp->SetName("BB"+yr+"__CWk1000__pileup__plus");
  // h2000_EBEB_pileupUp->SetName("BB"+yr+"__CWk2000__pileup__plus");
  // h3000_EBEB_pileupUp->SetName("BB"+yr+"__CWk3000__pileup__plus");
  // h4000_EBEB_pileupUp->SetName("BB"+yr+"__CWk4000__pileup__plus");
  // h5000_EBEB_pileupUp->SetName("BB"+yr+"__CWk5000__pileup__plus");
  //
  // // Down
  // h0p1_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk0p1__energyScaleSyst__minus");
  // h1_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk1__energyScaleSyst__minus");
  // h10_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk10__energyScaleSyst__minus");
  // h100_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk100__energyScaleSyst__minus");
  // h500_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk500__energyScaleSyst__minus");
  // h1000_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk1000__energyScaleSyst__minus");
  // h2000_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk2000__energyScaleSyst__minus");
  // h3000_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk3000__energyScaleSyst__minus");
  // h4000_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk4000__energyScaleSyst__minus");
  // h5000_EBEB_energyScaleSystDown->SetName("BB"+yr+"__CWk5000__energyScaleSyst__minus");
  //
  // h0p1_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk0p1__energySigma__minus");
  // h1_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk1__energySigma__minus");
  // h10_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk10__energySigma__minus");
  // h100_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk100__energySigma__minus");
  // h500_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk500__energySigma__minus");
  // h1000_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk1000__energySigma__minus");
  // h2000_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk2000__energySigma__minus");
  // h3000_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk3000__energySigma__minus");
  // h4000_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk4000__energySigma__minus");
  // h5000_EBEB_energySigmaDown->SetName("BB"+yr+"__CWk5000__energySigma__minus");
  //
  // h0p1_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk0p1__energyScaleGain__minus");
  // h1_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk1__energyScaleGain__minus");
  // h10_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk10__energyScaleGain__minus");
  // h100_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk100__energyScaleGain__minus");
  // h500_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk500__energyScaleGain__minus");
  // h1000_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk1000__energyScaleGain__minus");
  // h2000_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk2000__energyScaleGain__minus");
  // h3000_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk3000__energyScaleGain__minus");
  // h4000_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk4000__energyScaleGain__minus");
  // h5000_EBEB_energyScaleGainDown->SetName("BB"+yr+"__CWk5000__energyScaleGain__minus");
  //
  // h0p1_EBEB_effDown->SetName("BB"+yr+"__CWk0p1__eff__minus");
  // h1_EBEB_effDown->SetName("BB"+yr+"__CWk1__eff__minus");
  // h10_EBEB_effDown->SetName("BB"+yr+"__CWk10__eff__minus");
  // h100_EBEB_effDown->SetName("BB"+yr+"__CWk100__eff__minus");
  // h500_EBEB_effDown->SetName("BB"+yr+"__CWk500__eff__minus");
  // h1000_EBEB_effDown->SetName("BB"+yr+"__CWk1000__eff__minus");
  // h2000_EBEB_effDown->SetName("BB"+yr+"__CWk2000__eff__minus");
  // h3000_EBEB_effDown->SetName("BB"+yr+"__CWk3000__eff__minus");
  // h4000_EBEB_effDown->SetName("BB"+yr+"__CWk4000__eff__minus");
  // h5000_EBEB_effDown->SetName("BB"+yr+"__CWk5000__eff__minus");
  //
  // h0p1_EBEB_pileupDown->SetName("BB"+yr+"__CWk0p1__pileup__minus");
  // h1_EBEB_pileupDown->SetName("BB"+yr+"__CWk1__pileup__minus");
  // h10_EBEB_pileupDown->SetName("BB"+yr+"__CWk10__pileup__minus");
  // h100_EBEB_pileupDown->SetName("BB"+yr+"__CWk100__pileup__minus");
  // h500_EBEB_pileupDown->SetName("BB"+yr+"__CWk500__pileup__minus");
  // h1000_EBEB_pileupDown->SetName("BB"+yr+"__CWk1000__pileup__minus");
  // h2000_EBEB_pileupDown->SetName("BB"+yr+"__CWk2000__pileup__minus");
  // h3000_EBEB_pileupDown->SetName("BB"+yr+"__CWk3000__pileup__minus");
  // h4000_EBEB_pileupDown->SetName("BB"+yr+"__CWk4000__pileup__minus");
  // h5000_EBEB_pileupDown->SetName("BB"+yr+"__CWk5000__pileup__minus");
  //
  //
  // //Scale to Lumi
  //
  // h0p1_EBEB_energyScaleSystUp->Scale(luminosity);
  // h1_EBEB_energyScaleSystUp->Scale(luminosity);
  // h10_EBEB_energyScaleSystUp->Scale(luminosity);
  // h100_EBEB_energyScaleSystUp->Scale(luminosity);
  // h500_EBEB_energyScaleSystUp->Scale(luminosity);
  // h1000_EBEB_energyScaleSystUp->Scale(luminosity);
  // h2000_EBEB_energyScaleSystUp->Scale(luminosity);
  // h3000_EBEB_energyScaleSystUp->Scale(luminosity);
  // h4000_EBEB_energyScaleSystUp->Scale(luminosity);
  // h5000_EBEB_energyScaleSystUp->Scale(luminosity);
  //
  // h0p1_EBEB_energyScaleSystDown->Scale(luminosity);
  // h1_EBEB_energyScaleSystDown->Scale(luminosity);
  // h10_EBEB_energyScaleSystDown->Scale(luminosity);
  // h100_EBEB_energyScaleSystDown->Scale(luminosity);
  // h500_EBEB_energyScaleSystDown->Scale(luminosity);
  // h1000_EBEB_energyScaleSystDown->Scale(luminosity);
  // h2000_EBEB_energyScaleSystDown->Scale(luminosity);
  // h3000_EBEB_energyScaleSystDown->Scale(luminosity);
  // h4000_EBEB_energyScaleSystDown->Scale(luminosity);
  // h5000_EBEB_energyScaleSystDown->Scale(luminosity);
  //
  // // energySigma
  // h0p1_EBEB_energySigmaUp->Scale(luminosity);
  // h1_EBEB_energySigmaUp->Scale(luminosity);
  // h10_EBEB_energySigmaUp->Scale(luminosity);
  // h100_EBEB_energySigmaUp->Scale(luminosity);
  // h500_EBEB_energySigmaUp->Scale(luminosity);
  // h1000_EBEB_energySigmaUp->Scale(luminosity);
  // h2000_EBEB_energySigmaUp->Scale(luminosity);
  // h3000_EBEB_energySigmaUp->Scale(luminosity);
  // h4000_EBEB_energySigmaUp->Scale(luminosity);
  // h5000_EBEB_energySigmaUp->Scale(luminosity);
  //
  // h0p1_EBEB_energySigmaDown->Scale(luminosity);
  // h1_EBEB_energySigmaDown->Scale(luminosity);
  // h10_EBEB_energySigmaDown->Scale(luminosity);
  // h100_EBEB_energySigmaDown->Scale(luminosity);
  // h500_EBEB_energySigmaDown->Scale(luminosity);
  // h1000_EBEB_energySigmaDown->Scale(luminosity);
  // h2000_EBEB_energySigmaDown->Scale(luminosity);
  // h3000_EBEB_energySigmaDown->Scale(luminosity);
  // h4000_EBEB_energySigmaDown->Scale(luminosity);
  // h5000_EBEB_energySigmaDown->Scale(luminosity);
  //
  // // ==== energyScaleGain
  //
  // h0p1_EBEB_energyScaleGainUp->Scale(luminosity);
  // h1_EBEB_energyScaleGainUp->Scale(luminosity);
  // h10_EBEB_energyScaleGainUp->Scale(luminosity);
  // h100_EBEB_energyScaleGainUp->Scale(luminosity);
  // h500_EBEB_energyScaleGainUp->Scale(luminosity);
  // h1000_EBEB_energyScaleGainUp->Scale(luminosity);
  // h2000_EBEB_energyScaleGainUp->Scale(luminosity);
  // h3000_EBEB_energyScaleGainUp->Scale(luminosity);
  // h4000_EBEB_energyScaleGainUp->Scale(luminosity);
  // h5000_EBEB_energyScaleGainUp->Scale(luminosity);
  //
  // h0p1_EBEB_energyScaleGainDown->Scale(luminosity);
  // h1_EBEB_energyScaleGainDown->Scale(luminosity);
  // h10_EBEB_energyScaleGainDown->Scale(luminosity);
  // h100_EBEB_energyScaleGainDown->Scale(luminosity);
  // h500_EBEB_energyScaleGainDown->Scale(luminosity);
  // h1000_EBEB_energyScaleGainDown->Scale(luminosity);
  // h2000_EBEB_energyScaleGainDown->Scale(luminosity);
  // h3000_EBEB_energyScaleGainDown->Scale(luminosity);
  // h4000_EBEB_energyScaleGainDown->Scale(luminosity);
  // h5000_EBEB_energyScaleGainDown->Scale(luminosity);
  //
  // // eff
  // h0p1_EBEB_effUp->Scale(luminosity);
  // h1_EBEB_effUp->Scale(luminosity);
  // h10_EBEB_effUp->Scale(luminosity);
  // h100_EBEB_effUp->Scale(luminosity);
  // h500_EBEB_effUp->Scale(luminosity);
  // h1000_EBEB_effUp->Scale(luminosity);
  // h2000_EBEB_effUp->Scale(luminosity);
  // h3000_EBEB_effUp->Scale(luminosity);
  // h4000_EBEB_effUp->Scale(luminosity);
  // h5000_EBEB_effUp->Scale(luminosity);
  //
  // h0p1_EBEB_effDown->Scale(luminosity);
  // h1_EBEB_effDown->Scale(luminosity);
  // h10_EBEB_effDown->Scale(luminosity);
  // h100_EBEB_effDown->Scale(luminosity);
  // h500_EBEB_effDown->Scale(luminosity);
  // h1000_EBEB_effDown->Scale(luminosity);
  // h2000_EBEB_effDown->Scale(luminosity);
  // h3000_EBEB_effDown->Scale(luminosity);
  // h4000_EBEB_effDown->Scale(luminosity);
  // h5000_EBEB_effDown->Scale(luminosity);
  //
  // h0p1_EBEB_pileupUp->Scale(luminosity);
  // h1_EBEB_pileupUp->Scale(luminosity);
  // h10_EBEB_pileupUp->Scale(luminosity);
  // h100_EBEB_pileupUp->Scale(luminosity);
  // h500_EBEB_pileupUp->Scale(luminosity);
  // h1000_EBEB_pileupUp->Scale(luminosity);
  // h2000_EBEB_pileupUp->Scale(luminosity);
  // h3000_EBEB_pileupUp->Scale(luminosity);
  // h4000_EBEB_pileupUp->Scale(luminosity);
  // h5000_EBEB_pileupUp->Scale(luminosity);
  //
  // h0p1_EBEB_pileupDown->Scale(luminosity);
  // h1_EBEB_pileupDown->Scale(luminosity);
  // h10_EBEB_pileupDown->Scale(luminosity);
  // h100_EBEB_pileupDown->Scale(luminosity);
  // h500_EBEB_pileupDown->Scale(luminosity);
  // h1000_EBEB_pileupDown->Scale(luminosity);
  // h2000_EBEB_pileupDown->Scale(luminosity);
  // h3000_EBEB_pileupDown->Scale(luminosity);
  // h4000_EBEB_pileupDown->Scale(luminosity);
  // h5000_EBEB_pileupDown->Scale(luminosity);
  //
  // // Write Systematics
  //
  // h0p1_EBEB_energyScaleSystUp->Write();
  // h1_EBEB_energyScaleSystUp->Write();
  // h10_EBEB_energyScaleSystUp->Write();
  // h100_EBEB_energyScaleSystUp->Write();
  // h500_EBEB_energyScaleSystUp->Write();
  // h1000_EBEB_energyScaleSystUp->Write();
  // h2000_EBEB_energyScaleSystUp->Write();
  // h3000_EBEB_energyScaleSystUp->Write();
  // h4000_EBEB_energyScaleSystUp->Write();
  // h5000_EBEB_energyScaleSystUp->Write();
  //
  // h0p1_EBEB_energyScaleSystDown->Write();
  // h1_EBEB_energyScaleSystDown->Write();
  // h10_EBEB_energyScaleSystDown->Write();
  // h100_EBEB_energyScaleSystDown->Write();
  // h500_EBEB_energyScaleSystDown->Write();
  // h1000_EBEB_energyScaleSystDown->Write();
  // h2000_EBEB_energyScaleSystDown->Write();
  // h3000_EBEB_energyScaleSystDown->Write();
  // h4000_EBEB_energyScaleSystDown->Write();
  // h5000_EBEB_energyScaleSystDown->Write();
  //
  // // energySigma
  // h0p1_EBEB_energySigmaUp->Write();
  // h1_EBEB_energySigmaUp->Write();
  // h10_EBEB_energySigmaUp->Write();
  // h100_EBEB_energySigmaUp->Write();
  // h500_EBEB_energySigmaUp->Write();
  // h1000_EBEB_energySigmaUp->Write();
  // h2000_EBEB_energySigmaUp->Write();
  // h3000_EBEB_energySigmaUp->Write();
  // h4000_EBEB_energySigmaUp->Write();
  // h5000_EBEB_energySigmaUp->Write();
  //
  // h0p1_EBEB_energySigmaDown->Write();
  // h1_EBEB_energySigmaDown->Write();
  // h10_EBEB_energySigmaDown->Write();
  // h100_EBEB_energySigmaDown->Write();
  // h500_EBEB_energySigmaDown->Write();
  // h1000_EBEB_energySigmaDown->Write();
  // h2000_EBEB_energySigmaDown->Write();
  // h3000_EBEB_energySigmaDown->Write();
  // h4000_EBEB_energySigmaDown->Write();
  // h5000_EBEB_energySigmaDown->Write();
  //
  // // ==== energyScaleGain
  //
  // h0p1_EBEB_energyScaleGainUp->Write();
  // h1_EBEB_energyScaleGainUp->Write();
  // h10_EBEB_energyScaleGainUp->Write();
  // h100_EBEB_energyScaleGainUp->Write();
  // h500_EBEB_energyScaleGainUp->Write();
  // h1000_EBEB_energyScaleGainUp->Write();
  // h2000_EBEB_energyScaleGainUp->Write();
  // h3000_EBEB_energyScaleGainUp->Write();
  // h4000_EBEB_energyScaleGainUp->Write();
  // h5000_EBEB_energyScaleGainUp->Write();
  //
  // h0p1_EBEB_energyScaleGainDown->Write();
  // h1_EBEB_energyScaleGainDown->Write();
  // h10_EBEB_energyScaleGainDown->Write();
  // h100_EBEB_energyScaleGainDown->Write();
  // h500_EBEB_energyScaleGainDown->Write();
  // h1000_EBEB_energyScaleGainDown->Write();
  // h2000_EBEB_energyScaleGainDown->Write();
  // h3000_EBEB_energyScaleGainDown->Write();
  // h4000_EBEB_energyScaleGainDown->Write();
  // h5000_EBEB_energyScaleGainDown->Write();
  //
  // // eff
  // h0p1_EBEB_effUp->Write();
  // h1_EBEB_effUp->Write();
  // h10_EBEB_effUp->Write();
  // h100_EBEB_effUp->Write();
  // h500_EBEB_effUp->Write();
  // h1000_EBEB_effUp->Write();
  // h2000_EBEB_effUp->Write();
  // h3000_EBEB_effUp->Write();
  // h4000_EBEB_effUp->Write();
  // h5000_EBEB_effUp->Write();
  //
  // h0p1_EBEB_effDown->Write();
  // h1_EBEB_effDown->Write();
  // h10_EBEB_effDown->Write();
  // h100_EBEB_effDown->Write();
  // h500_EBEB_effDown->Write();
  // h1000_EBEB_effDown->Write();
  // h2000_EBEB_effDown->Write();
  // h3000_EBEB_effDown->Write();
  // h4000_EBEB_effDown->Write();
  // h5000_EBEB_effDown->Write();
  //
  // h0p1_EBEB_pileupUp->Write();
  // h1_EBEB_pileupUp->Write();
  // h10_EBEB_pileupUp->Write();
  // h100_EBEB_pileupUp->Write();
  // h500_EBEB_pileupUp->Write();
  // h1000_EBEB_pileupUp->Write();
  // h2000_EBEB_pileupUp->Write();
  // h3000_EBEB_pileupUp->Write();
  // h4000_EBEB_pileupUp->Write();
  // h5000_EBEB_pileupUp->Write();
  //
  // h0p1_EBEB_pileupDown->Write();
  // h1_EBEB_pileupDown->Write();
  // h10_EBEB_pileupDown->Write();
  // h100_EBEB_pileupDown->Write();
  // h500_EBEB_pileupDown->Write();
  // h1000_EBEB_pileupDown->Write();
  // h2000_EBEB_pileupDown->Write();
  // h3000_EBEB_pileupDown->Write();
  // h4000_EBEB_pileupDown->Write();
  // h5000_EBEB_pileupDown->Write();
  //
  // // h0p1_EBEB_pileupNom->Write();
  // // h1_EBEB_pileupNom->Write();
  // // h10_EBEB_pileupNom->Write();
  // // h100_EBEB_pileupNom->Write();
  // // h500_EBEB_pileupNom->Write();
  // // h1000_EBEB_pileupNom->Write();
  // // h2000_EBEB_pileupNom->Write();
  // // h3000_EBEB_pileupNom->Write();
  // // h4000_EBEB_pileupNom->Write();
  // // h5000_EBEB_pileupNom->Write();
  //
  // outputFileBB->Close();
  //
  // //======== BE
  //
  // TString outputfilenameBE = "BE"+ year +"_Clockwork.root";
  // TFile* outputFileBE = new TFile(outputfilenameBE, "RECREATE");
  //
  // h500_EBEE->SetName("BE"+yr+"__CWk500");
  // h1000_EBEE->SetName("BE"+yr+"__CWk1000");
  // h2000_EBEE->SetName("BE"+yr+"__CWk2000");
  // h3000_EBEE->SetName("BE"+yr+"__CWk3000");
  // h5000_EBEE->SetName("BE"+yr+"__CWk5000");
  //
  // h0p1_EBEE->SetName("BE"+yr+"__CWk0p1");
  // h1_EBEE->SetName("BE"+yr+"__CWk1");
  // h10_EBEE->SetName("BE"+yr+"__CWk10");
  // h100_EBEE->SetName("BE"+yr+"__CWk100");
  // h4000_EBEE->SetName("BE"+yr+"__CWk4000");
  //
  // h0p1_EBEE->Scale(luminosity);
  // h1_EBEE->Scale(luminosity);
  // h10_EBEE->Scale(luminosity);
  // h100_EBEE->Scale(luminosity);
  // h4000_EBEE->Scale(luminosity);
  //
  // h0p1_EBEE->Write();
  // h1_EBEE->Write();
  // h10_EBEE->Write();
  // h100_EBEE->Write();
  // h500_EBEE->Write();
  // h1000_EBEE->Write();
  // h2000_EBEE->Write();
  // h3000_EBEE->Write();
  // h4000_EBEE->Write();
  // h5000_EBEE->Write();
  //
  // //Systematics
  //
  // // SetName Systematics
  // h0p1_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk0p1__energyScaleSyst__plus");
  // h1_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk1__energyScaleSyst__plus");
  // h10_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk10__energyScaleSyst__plus");
  // h100_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk100__energyScaleSyst__plus");
  // h500_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk500__energyScaleSyst__plus");
  // h1000_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk1000__energyScaleSyst__plus");
  // h2000_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk2000__energyScaleSyst__plus");
  // h3000_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk3000__energyScaleSyst__plus");
  // h4000_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk4000__energyScaleSyst__plus");
  // h5000_EBEE_energyScaleSystUp->SetName("BE"+yr+"__CWk5000__energyScaleSyst__plus");
  //
  // h0p1_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk0p1__energySigma__plus");
  // h1_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk1__energySigma__plus");
  // h10_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk10__energySigma__plus");
  // h100_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk100__energySigma__plus");
  // h500_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk500__energySigma__plus");
  // h1000_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk1000__energySigma__plus");
  // h2000_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk2000__energySigma__plus");
  // h3000_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk3000__energySigma__plus");
  // h4000_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk4000__energySigma__plus");
  // h5000_EBEE_energySigmaUp->SetName("BE"+yr+"__CWk5000__energySigma__plus");
  //
  // h0p1_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk0p1__energyScaleGain__plus");
  // h1_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk1__energyScaleGain__plus");
  // h10_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk10__energyScaleGain__plus");
  // h100_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk100__energyScaleGain__plus");
  // h500_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk500__energyScaleGain__plus");
  // h1000_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk1000__energyScaleGain__plus");
  // h2000_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk2000__energyScaleGain__plus");
  // h3000_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk3000__energyScaleGain__plus");
  // h4000_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk4000__energyScaleGain__plus");
  // h5000_EBEE_energyScaleGainUp->SetName("BE"+yr+"__CWk5000__energyScaleGain__plus");
  //
  // h0p1_EBEE_effUp->SetName("BE"+yr+"__CWk0p1__eff__plus");
  // h1_EBEE_effUp->SetName("BE"+yr+"__CWk1__eff__plus");
  // h10_EBEE_effUp->SetName("BE"+yr+"__CWk10__eff__plus");
  // h100_EBEE_effUp->SetName("BE"+yr+"__CWk100__eff__plus");
  // h500_EBEE_effUp->SetName("BE"+yr+"__CWk500__eff__plus");
  // h1000_EBEE_effUp->SetName("BE"+yr+"__CWk1000__eff__plus");
  // h2000_EBEE_effUp->SetName("BE"+yr+"__CWk2000__eff__plus");
  // h3000_EBEE_effUp->SetName("BE"+yr+"__CWk3000__eff__plus");
  // h4000_EBEE_effUp->SetName("BE"+yr+"__CWk4000__eff__plus");
  // h5000_EBEE_effUp->SetName("BE"+yr+"__CWk5000__eff__plus");
  //
  // h0p1_EBEE_pileupUp->SetName("BE"+yr+"__CWk0p1__pileup__plus");
  // h1_EBEE_pileupUp->SetName("BE"+yr+"__CWk1__pileup__plus");
  // h10_EBEE_pileupUp->SetName("BE"+yr+"__CWk10__pileup__plus");
  // h100_EBEE_pileupUp->SetName("BE"+yr+"__CWk100__pileup__plus");
  // h500_EBEE_pileupUp->SetName("BE"+yr+"__CWk500__pileup__plus");
  // h1000_EBEE_pileupUp->SetName("BE"+yr+"__CWk1000__pileup__plus");
  // h2000_EBEE_pileupUp->SetName("BE"+yr+"__CWk2000__pileup__plus");
  // h3000_EBEE_pileupUp->SetName("BE"+yr+"__CWk3000__pileup__plus");
  // h4000_EBEE_pileupUp->SetName("BE"+yr+"__CWk4000__pileup__plus");
  // h5000_EBEE_pileupUp->SetName("BE"+yr+"__CWk5000__pileup__plus");
  //
  // // Down
  // h0p1_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk0p1__energyScaleSyst__minus");
  // h1_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk1__energyScaleSyst__minus");
  // h10_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk10__energyScaleSyst__minus");
  // h100_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk100__energyScaleSyst__minus");
  // h500_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk500__energyScaleSyst__minus");
  // h1000_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk1000__energyScaleSyst__minus");
  // h2000_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk2000__energyScaleSyst__minus");
  // h3000_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk3000__energyScaleSyst__minus");
  // h4000_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk4000__energyScaleSyst__minus");
  // h5000_EBEE_energyScaleSystDown->SetName("BE"+yr+"__CWk5000__energyScaleSyst__minus");
  //
  // h0p1_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk0p1__energySigma__minus");
  // h1_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk1__energySigma__minus");
  // h10_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk10__energySigma__minus");
  // h100_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk100__energySigma__minus");
  // h500_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk500__energySigma__minus");
  // h1000_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk1000__energySigma__minus");
  // h2000_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk2000__energySigma__minus");
  // h3000_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk3000__energySigma__minus");
  // h4000_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk4000__energySigma__minus");
  // h5000_EBEE_energySigmaDown->SetName("BE"+yr+"__CWk5000__energySigma__minus");
  //
  // h0p1_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk0p1__energyScaleGain__minus");
  // h1_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk1__energyScaleGain__minus");
  // h10_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk10__energyScaleGain__minus");
  // h100_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk100__energyScaleGain__minus");
  // h500_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk500__energyScaleGain__minus");
  // h1000_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk1000__energyScaleGain__minus");
  // h2000_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk2000__energyScaleGain__minus");
  // h3000_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk3000__energyScaleGain__minus");
  // h4000_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk4000__energyScaleGain__minus");
  // h5000_EBEE_energyScaleGainDown->SetName("BE"+yr+"__CWk5000__energyScaleGain__minus");
  //
  // h0p1_EBEE_effDown->SetName("BE"+yr+"__CWk0p1__eff__minus");
  // h1_EBEE_effDown->SetName("BE"+yr+"__CWk1__eff__minus");
  // h10_EBEE_effDown->SetName("BE"+yr+"__CWk10__eff__minus");
  // h100_EBEE_effDown->SetName("BE"+yr+"__CWk100__eff__minus");
  // h500_EBEE_effDown->SetName("BE"+yr+"__CWk500__eff__minus");
  // h1000_EBEE_effDown->SetName("BE"+yr+"__CWk1000__eff__minus");
  // h2000_EBEE_effDown->SetName("BE"+yr+"__CWk2000__eff__minus");
  // h3000_EBEE_effDown->SetName("BE"+yr+"__CWk3000__eff__minus");
  // h4000_EBEE_effDown->SetName("BE"+yr+"__CWk4000__eff__minus");
  // h5000_EBEE_effDown->SetName("BE"+yr+"__CWk5000__eff__minus");
  //
  // h0p1_EBEE_pileupDown->SetName("BE"+yr+"__CWk0p1__pileup__minus");
  // h1_EBEE_pileupDown->SetName("BE"+yr+"__CWk1__pileup__minus");
  // h10_EBEE_pileupDown->SetName("BE"+yr+"__CWk10__pileup__minus");
  // h100_EBEE_pileupDown->SetName("BE"+yr+"__CWk100__pileup__minus");
  // h500_EBEE_pileupDown->SetName("BE"+yr+"__CWk500__pileup__minus");
  // h1000_EBEE_pileupDown->SetName("BE"+yr+"__CWk1000__pileup__minus");
  // h2000_EBEE_pileupDown->SetName("BE"+yr+"__CWk2000__pileup__minus");
  // h3000_EBEE_pileupDown->SetName("BE"+yr+"__CWk3000__pileup__minus");
  // h4000_EBEE_pileupDown->SetName("BE"+yr+"__CWk4000__pileup__minus");
  // h5000_EBEE_pileupDown->SetName("BE"+yr+"__CWk5000__pileup__minus");
  //
  // //Scale to Lumi
  //
  // h0p1_EBEE_energyScaleSystUp->Scale(luminosity);
  // h1_EBEE_energyScaleSystUp->Scale(luminosity);
  // h10_EBEE_energyScaleSystUp->Scale(luminosity);
  // h100_EBEE_energyScaleSystUp->Scale(luminosity);
  // h500_EBEE_energyScaleSystUp->Scale(luminosity);
  // h1000_EBEE_energyScaleSystUp->Scale(luminosity);
  // h2000_EBEE_energyScaleSystUp->Scale(luminosity);
  // h3000_EBEE_energyScaleSystUp->Scale(luminosity);
  // h4000_EBEE_energyScaleSystUp->Scale(luminosity);
  // h5000_EBEE_energyScaleSystUp->Scale(luminosity);
  //
  // h0p1_EBEE_energyScaleSystDown->Scale(luminosity);
  // h1_EBEE_energyScaleSystDown->Scale(luminosity);
  // h10_EBEE_energyScaleSystDown->Scale(luminosity);
  // h100_EBEE_energyScaleSystDown->Scale(luminosity);
  // h500_EBEE_energyScaleSystDown->Scale(luminosity);
  // h1000_EBEE_energyScaleSystDown->Scale(luminosity);
  // h2000_EBEE_energyScaleSystDown->Scale(luminosity);
  // h3000_EBEE_energyScaleSystDown->Scale(luminosity);
  // h4000_EBEE_energyScaleSystDown->Scale(luminosity);
  // h5000_EBEE_energyScaleSystDown->Scale(luminosity);
  //
  // // energySigma
  // h0p1_EBEE_energySigmaUp->Scale(luminosity);
  // h1_EBEE_energySigmaUp->Scale(luminosity);
  // h10_EBEE_energySigmaUp->Scale(luminosity);
  // h100_EBEE_energySigmaUp->Scale(luminosity);
  // h500_EBEE_energySigmaUp->Scale(luminosity);
  // h1000_EBEE_energySigmaUp->Scale(luminosity);
  // h2000_EBEE_energySigmaUp->Scale(luminosity);
  // h3000_EBEE_energySigmaUp->Scale(luminosity);
  // h4000_EBEE_energySigmaUp->Scale(luminosity);
  // h5000_EBEE_energySigmaUp->Scale(luminosity);
  //
  // h0p1_EBEE_energySigmaDown->Scale(luminosity);
  // h1_EBEE_energySigmaDown->Scale(luminosity);
  // h10_EBEE_energySigmaDown->Scale(luminosity);
  // h100_EBEE_energySigmaDown->Scale(luminosity);
  // h500_EBEE_energySigmaDown->Scale(luminosity);
  // h1000_EBEE_energySigmaDown->Scale(luminosity);
  // h2000_EBEE_energySigmaDown->Scale(luminosity);
  // h3000_EBEE_energySigmaDown->Scale(luminosity);
  // h4000_EBEE_energySigmaDown->Scale(luminosity);
  // h5000_EBEE_energySigmaDown->Scale(luminosity);
  //
  // // ==== energyScaleGain
  //
  // h0p1_EBEE_energyScaleGainUp->Scale(luminosity);
  // h1_EBEE_energyScaleGainUp->Scale(luminosity);
  // h10_EBEE_energyScaleGainUp->Scale(luminosity);
  // h100_EBEE_energyScaleGainUp->Scale(luminosity);
  // h500_EBEE_energyScaleGainUp->Scale(luminosity);
  // h1000_EBEE_energyScaleGainUp->Scale(luminosity);
  // h2000_EBEE_energyScaleGainUp->Scale(luminosity);
  // h3000_EBEE_energyScaleGainUp->Scale(luminosity);
  // h4000_EBEE_energyScaleGainUp->Scale(luminosity);
  // h5000_EBEE_energyScaleGainUp->Scale(luminosity);
  //
  // h0p1_EBEE_energyScaleGainDown->Scale(luminosity);
  // h1_EBEE_energyScaleGainDown->Scale(luminosity);
  // h10_EBEE_energyScaleGainDown->Scale(luminosity);
  // h100_EBEE_energyScaleGainDown->Scale(luminosity);
  // h500_EBEE_energyScaleGainDown->Scale(luminosity);
  // h1000_EBEE_energyScaleGainDown->Scale(luminosity);
  // h2000_EBEE_energyScaleGainDown->Scale(luminosity);
  // h3000_EBEE_energyScaleGainDown->Scale(luminosity);
  // h4000_EBEE_energyScaleGainDown->Scale(luminosity);
  // h5000_EBEE_energyScaleGainDown->Scale(luminosity);
  //
  // // eff
  // h0p1_EBEE_effUp->Scale(luminosity);
  // h1_EBEE_effUp->Scale(luminosity);
  // h10_EBEE_effUp->Scale(luminosity);
  // h100_EBEE_effUp->Scale(luminosity);
  // h500_EBEE_effUp->Scale(luminosity);
  // h1000_EBEE_effUp->Scale(luminosity);
  // h2000_EBEE_effUp->Scale(luminosity);
  // h3000_EBEE_effUp->Scale(luminosity);
  // h4000_EBEE_effUp->Scale(luminosity);
  // h5000_EBEE_effUp->Scale(luminosity);
  //
  // h0p1_EBEE_effDown->Scale(luminosity);
  // h1_EBEE_effDown->Scale(luminosity);
  // h10_EBEE_effDown->Scale(luminosity);
  // h100_EBEE_effDown->Scale(luminosity);
  // h500_EBEE_effDown->Scale(luminosity);
  // h1000_EBEE_effDown->Scale(luminosity);
  // h2000_EBEE_effDown->Scale(luminosity);
  // h3000_EBEE_effDown->Scale(luminosity);
  // h4000_EBEE_effDown->Scale(luminosity);
  // h5000_EBEE_effDown->Scale(luminosity);
  //
  // h0p1_EBEE_pileupUp->Scale(luminosity);
  // h1_EBEE_pileupUp->Scale(luminosity);
  // h10_EBEE_pileupUp->Scale(luminosity);
  // h100_EBEE_pileupUp->Scale(luminosity);
  // h500_EBEE_pileupUp->Scale(luminosity);
  // h1000_EBEE_pileupUp->Scale(luminosity);
  // h2000_EBEE_pileupUp->Scale(luminosity);
  // h3000_EBEE_pileupUp->Scale(luminosity);
  // h4000_EBEE_pileupUp->Scale(luminosity);
  // h5000_EBEE_pileupUp->Scale(luminosity);
  //
  // h0p1_EBEE_pileupDown->Scale(luminosity);
  // h1_EBEE_pileupDown->Scale(luminosity);
  // h10_EBEE_pileupDown->Scale(luminosity);
  // h100_EBEE_pileupDown->Scale(luminosity);
  // h500_EBEE_pileupDown->Scale(luminosity);
  // h1000_EBEE_pileupDown->Scale(luminosity);
  // h2000_EBEE_pileupDown->Scale(luminosity);
  // h3000_EBEE_pileupDown->Scale(luminosity);
  // h4000_EBEE_pileupDown->Scale(luminosity);
  // h5000_EBEE_pileupDown->Scale(luminosity);
  //
  // h0p1_EBEE_energyScaleSystUp->Write();
  // h1_EBEE_energyScaleSystUp->Write();
  // h10_EBEE_energyScaleSystUp->Write();
  // h100_EBEE_energyScaleSystUp->Write();
  // h500_EBEE_energyScaleSystUp->Write();
  // h1000_EBEE_energyScaleSystUp->Write();
  // h2000_EBEE_energyScaleSystUp->Write();
  // h3000_EBEE_energyScaleSystUp->Write();
  // h4000_EBEE_energyScaleSystUp->Write();
  // h5000_EBEE_energyScaleSystUp->Write();
  //
  // h0p1_EBEE_energyScaleSystDown->Write();
  // h1_EBEE_energyScaleSystDown->Write();
  // h10_EBEE_energyScaleSystDown->Write();
  // h100_EBEE_energyScaleSystDown->Write();
  // h500_EBEE_energyScaleSystDown->Write();
  // h1000_EBEE_energyScaleSystDown->Write();
  // h2000_EBEE_energyScaleSystDown->Write();
  // h3000_EBEE_energyScaleSystDown->Write();
  // h4000_EBEE_energyScaleSystDown->Write();
  // h5000_EBEE_energyScaleSystDown->Write();
  //
  // h0p1_EBEE_energySigmaUp->Write();
  // h1_EBEE_energySigmaUp->Write();
  // h10_EBEE_energySigmaUp->Write();
  // h100_EBEE_energySigmaUp->Write();
  // h500_EBEE_energySigmaUp->Write();
  // h1000_EBEE_energySigmaUp->Write();
  // h2000_EBEE_energySigmaUp->Write();
  // h3000_EBEE_energySigmaUp->Write();
  // h4000_EBEE_energySigmaUp->Write();
  // h5000_EBEE_energySigmaUp->Write();
  //
  // h0p1_EBEE_energySigmaDown->Write();
  // h1_EBEE_energySigmaDown->Write();
  // h10_EBEE_energySigmaDown->Write();
  // h100_EBEE_energySigmaDown->Write();
  // h500_EBEE_energySigmaDown->Write();
  // h1000_EBEE_energySigmaDown->Write();
  // h2000_EBEE_energySigmaDown->Write();
  // h3000_EBEE_energySigmaDown->Write();
  // h4000_EBEE_energySigmaDown->Write();
  // h5000_EBEE_energySigmaDown->Write();
  //
  // h0p1_EBEE_energyScaleGainUp->Write();
  // h1_EBEE_energyScaleGainUp->Write();
  // h10_EBEE_energyScaleGainUp->Write();
  // h100_EBEE_energyScaleGainUp->Write();
  // h500_EBEE_energyScaleGainUp->Write();
  // h1000_EBEE_energyScaleGainUp->Write();
  // h2000_EBEE_energyScaleGainUp->Write();
  // h3000_EBEE_energyScaleGainUp->Write();
  // h4000_EBEE_energyScaleGainUp->Write();
  // h5000_EBEE_energyScaleGainUp->Write();
  //
  // h0p1_EBEE_energyScaleGainDown->Write();
  // h1_EBEE_energyScaleGainDown->Write();
  // h10_EBEE_energyScaleGainDown->Write();
  // h100_EBEE_energyScaleGainDown->Write();
  // h500_EBEE_energyScaleGainDown->Write();
  // h1000_EBEE_energyScaleGainDown->Write();
  // h2000_EBEE_energyScaleGainDown->Write();
  // h3000_EBEE_energyScaleGainDown->Write();
  // h4000_EBEE_energyScaleGainDown->Write();
  // h5000_EBEE_energyScaleGainDown->Write();
  //
  // h0p1_EBEE_effUp->Write();
  // h1_EBEE_effUp->Write();
  // h10_EBEE_effUp->Write();
  // h100_EBEE_effUp->Write();
  // h500_EBEE_effUp->Write();
  // h1000_EBEE_effUp->Write();
  // h2000_EBEE_effUp->Write();
  // h3000_EBEE_effUp->Write();
  // h4000_EBEE_effUp->Write();
  // h5000_EBEE_effUp->Write();
  //
  // h0p1_EBEE_effDown->Write();
  // h1_EBEE_effDown->Write();
  // h10_EBEE_effDown->Write();
  // h100_EBEE_effDown->Write();
  // h500_EBEE_effDown->Write();
  // h1000_EBEE_effDown->Write();
  // h2000_EBEE_effDown->Write();
  // h3000_EBEE_effDown->Write();
  // h4000_EBEE_effDown->Write();
  // h5000_EBEE_effDown->Write();
  //
  // h0p1_EBEE_pileupUp->Write();
  // h1_EBEE_pileupUp->Write();
  // h10_EBEE_pileupUp->Write();
  // h100_EBEE_pileupUp->Write();
  // h500_EBEE_pileupUp->Write();
  // h1000_EBEE_pileupUp->Write();
  // h2000_EBEE_pileupUp->Write();
  // h3000_EBEE_pileupUp->Write();
  // h4000_EBEE_pileupUp->Write();
  // h5000_EBEE_pileupUp->Write();
  //
  // h0p1_EBEE_pileupDown->Write();
  // h1_EBEE_pileupDown->Write();
  // h10_EBEE_pileupDown->Write();
  // h100_EBEE_pileupDown->Write();
  // h500_EBEE_pileupDown->Write();
  // h1000_EBEE_pileupDown->Write();
  // h2000_EBEE_pileupDown->Write();
  // h3000_EBEE_pileupDown->Write();
  // h4000_EBEE_pileupDown->Write();
  // h5000_EBEE_pileupDown->Write();
  //
  // // h0p1_EBEE_pileupNom->Write();
  // // h1_EBEE_pileupNom->Write();
  // // h10_EBEE_pileupNom->Write();
  // // h100_EBEE_pileupNom->Write();
  // // h500_EBEE_pileupNom->Write();
  // // h1000_EBEE_pileupNom->Write();
  // // h2000_EBEE_pileupNom->Write();
  // // h3000_EBEE_pileupNom->Write();
  // // h4000_EBEE_pileupNom->Write();
  // // h5000_EBEE_pileupNom->Write();
  //
  //
  // outputFileBE->Close();
}



// TH1* draw1DComps(TCanvas* c, const char* name)
// {
//   c->cd();
//   TH1* hSig=getHist(name, 1);
//   TH1* hData=getHist(name, 2);
//   TH1* hBkg=getHist(name, 3);
//
//   hSig->SetFillColor(kRed+2);
//   hSig->SetFillStyle(3004);
//   hBkg->SetFillColor(kBlue+2);
//   hBkg->SetFillStyle(3005);
//
//   TH1 *h=hData->DrawNormalized("E0");
//   hSig->DrawNormalized("same");
//   hBkg->DrawNormalized("same");
//
//   h->SetTitle("");
//   h->SetStats(0);
//
//   TLegend* leg=new TLegend(.589,.703,.89,.913);
//   leg->AddEntry(hData, "Data", "pl");
//   leg->AddEntry(hSig, "#phi(750) to #eta#eta", "f");
//   leg->AddEntry(hBkg, "Sherpa Diphotons", "f");
//   leg->SetLineWidth(0);
//   leg->Draw();
//
//   return h;
// }


// void drawCompPlots(void)
// {
//
//   TCanvas *c=new TCanvas();
//   TH1* h=draw1DComps(c, "hConvN");
//   gPad->SetLogy(0);
//   h->GetXaxis()->SetTitle("Number of Conversions");
//   h->GetYaxis()->SetTitle("Arbitrary Units");
//   h->GetXaxis()->SetNdivisions(10);
//   h->GetXaxis()->SetRange(1,6);
//   CMSlumi(c, 0, 32, true);
//
//   c=new TCanvas();
//   h=draw1DComps(c, "hConvR");
//   gPad->SetLogy(0);
//   h->GetXaxis()->SetTitle("Conversion Radius [cm]");
//   h->GetYaxis()->SetTitle("Arbitrary Units");
//   h->SetMaximum(0.07);
//   CMSlumi(c, 0, 32, true);
//
//
//   c=new TCanvas();
//   h=draw1DComps(c, "hConvDphi");
//   gPad->SetLogy(1);
//   h->GetXaxis()->SetTitle("#Delta#phi between Photon and Conversion");
//   h->GetYaxis()->SetTitle("Arbitrary Units");
//   h->SetMaximum(0.5);
//   h->GetXaxis()->SetNdivisions(505);
//   CMSlumi(c, 0, 32, true);
//
//   c=new TCanvas();
//   h=draw1DComps(c, "hConvPtOverE");
//   gPad->SetLogy(1);
//   h->GetXaxis()->SetTitle("Conversion p_{T}/Photon p_{T}");
//   h->GetYaxis()->SetTitle("Arbitrary Units");
//   h->SetMaximum(0.3);
//   CMSlumi(c, 0, 32, true);
//
//   c=new TCanvas();
//   h=draw1DComps(c, "hConv1stR");
//   gPad->SetLogy(0);
//   h->GetXaxis()->SetTitle("Earliest Conversion Radius [cm]");
//   h->GetYaxis()->SetTitle("Arbitrary Units");
//   h->SetMaximum(0.1);
//   CMSlumi(c, 0, 32, true);
//
//
//   return;
// }

// void drawMassPlots(int nconv, int BB)
// {
//   TH1* h=0;
//   if(nconv==0 && BB==1) h=getHist("hInvMass0ObsBB", 2);
//   if(nconv==1 && BB==1) h=getHist("hInvMass1ObsBB", 2);
//   if(nconv==2 && BB==1) h=getHist("hInvMass2ObsBB", 2);
//   if(nconv==0 && BB!=1) h=getHist("hInvMass0ObsBE", 2);
//   if(nconv==1 && BB!=1) h=getHist("hInvMass1ObsBE", 2);
//   if(nconv==2 && BB!=1) h=getHist("hInvMass2ObsBE", 2);
//
//   assert(h);
//
//   TCanvas *c=new TCanvas();
//
//   h->Draw("E0");
//   h->SetStats(0);
//   h->SetTitle("");
//   gPad->SetLogy(1);
//   h->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV]");
//   h->GetYaxis()->SetTitle("Events/20 GeV");
//   h->SetMinimum(.01);
//
//   TText *tt=0;
//   if(nconv==0 && BB==1) tt=new TText(300, 1000, "EB-EB =0 conversions");
//   if(nconv==1 && BB==1) tt=new TText(300, 1000, "EB-EB =1 conversions");
//   if(nconv==2 && BB==1) tt=new TText(300, 1000, "EB-EB >=2 conversions");
//   if(nconv==0 && BB!=1) tt=new TText(300, 1000, "EB-EE =0 conversions");
//   if(nconv==1 && BB!=1) tt=new TText(300, 1000, "EB-EE =1 conversions");
//   if(nconv==2 && BB!=1) tt=new TText(300, 1000, "EB-EE >=2 conversions");
//   tt->SetNDC();
//   tt->SetX(.3);
//   tt->SetY(.85);
//   tt->SetTextSize(0.04);
//   tt->SetTextFont(62);
//   tt->Draw();
//
//   TF1  *f1 = new TF1("f1","pow(x,[a]+[b]*log(x))",160,1400);
//   h->Fit(f1);
//
//   // CMSlumi(c, 0, 33, true);
//
// }


// void drawplots(void)
// {
//   drawCompPlots();
//   drawMassPlots(0, 1);
//   drawMassPlots(1, 1);
//   drawMassPlots(2, 1);
// }
