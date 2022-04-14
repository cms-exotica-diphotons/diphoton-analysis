#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include "THStack.h"

void gg_bkg_sub()
{
  init(false, true);

  // TChain *chGG = new TChain("diphoton/fTree");
  // chGG->Add("/eos/uscms/store/user/cawest/diphoton/cba3996/GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213601/0000/*.root");
  // chGG->Add("/eos/uscms/store/user/cawest/diphoton/cba3996/GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213628/0000/*.root");
  // chGG->Add("/eos/uscms/store/user/cawest/diphoton/cba3996/GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213653/0000/*.root");
  // chGG->Add("/eos/uscms/store/user/cawest/diphoton/cba3996/GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213719/0000/*.root");

  // TChain *chADD = new TChain("diphoton/fTree");
  // chADD->Add("/eos/uscms/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192641/0000/*.root");
  // chADD->Add("/eos/uscms/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192428/0000/*.root");
  // chADD->Add("/eos/uscms/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192458/0000/*.root");
  // chADD->Add("/eos/uscms/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192558/0000/*.root");

  TChain* chADD = chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"];
  TChain* chGG70 = chains["gg70_2018"];

  TCanvas *c = new TCanvas;

  TH1D* hGG_gluon_gluon = new TH1D("hGG_gluon_gluon", "hGG_gluon_gluon", 10, 500, 1000);
  chGG70->Draw("Diphoton.Minv>>hGG_gluon_gluon", "weightAll*(isGood && pdf_id1==21 && pdf_id2==21)", "hist");
  hGG_gluon_gluon->SetFillColor(kAzure-2);
  hGG_gluon_gluon->SetLineColor(kAzure-2);
  hGG_gluon_gluon->SetFillStyle(1001);
  TH1D* hGG_quark_quark = new TH1D("hGG_quark_quark", "hGG_quark_quark", 10, 500, 1000);
  chGG70->Draw("Diphoton.Minv>>hGG_quark_quark", "weightAll*(isGood && !(pdf_id1==21 && pdf_id2==21))", "hist");
  hGG_quark_quark->SetFillColor(kAzure-4);
  hGG_quark_quark->SetLineColor(kAzure-4);
  hGG_quark_quark->SetFillStyle(1001);

  TH1D* hADD = new TH1D("ADD", "ADD", 10, 500, 1000);
  chADD->Draw("Diphoton.Minv>>ADD", "weightAll*isGood");
  hADD->SetMarkerColor(kBlack);
  hADD->SetLineColor(kBlack);
  hADD->SetMarkerSize(1.25);
  hADD->GetYaxis()->SetRangeUser(0, 1.5*hADD->GetMaximum());
  hADD->SetTitle(";m_{#gamma#gamma} (GeV);Events / 1 fb^{-1}");

  hADD->Draw();

  THStack *hs = new THStack("hs", "hs");
  hs->Add(hGG_quark_quark);
  hs->Add(hGG_gluon_gluon);
  hs->Draw("hist same");

  hADD->Draw("same");

  c->RedrawAxis();

  TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(hADD, "ADD, #Lambda_{T} = 11 TeV", "ELP");
  leg->AddEntry(hGG_quark_quark, "quark-antiquark", "F");
  leg->AddEntry(hGG_gluon_gluon, "gluon-gluon", "F");
  leg->Draw();

  c->Print("plots/GG_bkg_sub.pdf");
}
