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
TString year = "2017";
std::string stryear = "2017";
TString yr = "17";

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

  TH1* h0p1_EBEB=combine(getHist("diphotonMinvEBEB_k500",1),getHist("diphotonMinvEBEB_k500",2), getHist("diphotonMinvEBEB_k500",3), getHist("diphotonMinvEBEB_k500",4), getHist("diphotonMinvEBEB_k500",0), 4000, 6000);
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

  TString outputfilename = "Test"+ year +"_Clockwork.root";
  TFile* outputFile = new TFile(outputfilename, "RECREATE");

  //ADD_new_name = "%s%s__ADDNegInt%sLT%s" %(region, year[2:], NegInt, LambdaT)
  h500_EBEB->SetName("BB"+year+"__CWk500");
  h1000_EBEB->SetName("BB"+year+"__CWk1000");
  h2000_EBEB->SetName("BB"+year+"__CWk2000");
  h3000_EBEB->SetName("BB"+year+"__CWk3000");
  h5000_EBEB->SetName("BB"+year+"__CWk5000");

  h500_EBEE->SetName("BE"+year+"__CWk500");
  h1000_EBEE->SetName("BE"+year+"__CWk1000");
  h2000_EBEE->SetName("BE"+year+"__CWk2000");
  h3000_EBEE->SetName("BE"+year+"__CWk3000");
  h5000_EBEE->SetName("BE"+year+"__CWk5000");

  h500_EBEB->Write();
  h1000_EBEB->Write();
  h2000_EBEB->Write();
  h3000_EBEB->Write();
  h5000_EBEB->Write();

  h500_EBEE->Write();
  h1000_EBEE->Write();
  h2000_EBEE->Write();
  h3000_EBEE->Write();
  h5000_EBEE->Write();

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
