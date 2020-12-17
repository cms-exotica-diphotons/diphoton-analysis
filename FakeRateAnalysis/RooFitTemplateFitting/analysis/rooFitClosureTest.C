#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include "TROOT.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TF1.h"
#include "RooHistPdf.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooNDKeysPdf.h"
#include "TFile.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMath.h"
#include "TText.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "RooChi2Var.h"

#include <vector>
#include <algorithm>

/**
 * Return background and uncertainty instead of fakerate
 *
 * This function is called from /scripts/fakeRateCalculation.C
 * From /analysis, run
 * root -l -b -q ../scripts/fakeRateCalculation.C'("mc","sieie")'
 */
std::pair<double,double> rooFitClosureTest(TString sample, TString templateVariable, TString ptBin, TString etaBin, std::pair<double,double> sideband, int denomBin, TString era, int pvCutLow, int pvCutHigh)
{
  //bool no_template_pv_binning = true;

  std::map<TString, TString> cmssw_version;
  cmssw_version["2016"] = "76X";
  cmssw_version["2017"] = "94X";
  cmssw_version["Run2017B"] = "94X";
  cmssw_version["Run2017C"] = "94X";
  cmssw_version["Run2017D"] = "94X";
  cmssw_version["Run2017E"] = "94X";
  cmssw_version["Run2017F"] = "94X";
  cmssw_version["2018"] = "102X";
  cmssw_version["Run2018A"] = "102X";
  cmssw_version["Run2018B"] = "102X";
  cmssw_version["Run2018C"] = "102X";
  cmssw_version["Run2018D"] = "102X";

  gROOT->SetBatch();
  gSystem->Load("libRooFit");
  gSystem->AddIncludePath("-I$ROOFITSYS/include");

  using namespace RooFit;
  using namespace std;

  cout << endl;
  cout << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;

  setTDRStyle();
  gROOT->ForceStyle();

  cout << "Starting rooFitClosureTest" << endl;
  cout << "Using " << sample << ", " << templateVariable << ", " << etaBin << ", pt " << ptBin << ", " << sideband.first << " < sideband < " << sideband.second << endl;

  // for real templates (same for data and mc)
  TString extra("");

  // for numerator, fake templates, and denominator (choose data or mc)
  //TString basefilename("root://cmseos.fnal.gov//store/user/cawest/fake_rate/");
  TString basefilename("/uscms/home/cuperez/nobackup/tribosons/FakeRate/FakeRate/CMSSW_10_2_18/src/");
  TString data_filename = "";
  TString pvCut = "";
  TString input_filename = "";

  // MC as fakes (fake-enriched samples) or Truth
  if (sample == "QCD")    data_filename = "diphoton_fake_rate_closure_test_QCD_Pt_all_TuneCUETP8M1_13TeV_pythia8_" + cmssw_version[era] + "_MiniAOD_histograms.root";
  if (sample == "GJets")  data_filename = "diphoton_fake_rate_closure_test_GJets_HT-all_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_" + cmssw_version[era] + "_MiniAOD_histograms.root";
  if (sample == "GGJets") data_filename = "diphoton_fake_rate_closure_test_GGJets_M-all_Pt-50_13TeV-sherpa_" + cmssw_version[era] + "_MiniAOD_histograms.root";
  if (sample == "all")    data_filename = "diphoton_fake_rate_closure_test_all_samples_" + cmssw_version[era] + "_MiniAOD_histograms.root";
  if (sample == "alltruth"){
    data_filename = "diphoton_fake_rate_closure_test_matching_all_samples_"+ cmssw_version[era] +"_MiniAOD_histograms.root";
    input_filename = "diphoton_fake_rate_closure_test_all_samples_" + cmssw_version[era] + "_MiniAOD_histograms.root";
    std::cout << "Using numerator file: " << input_filename << std::endl;
  }

  TFile *histojetfile = TFile::Open(data_filename);
  TFile *histojetfile_templates;
  histojetfile_templates = TFile::Open(data_filename);



  // Real Templates
  TString mc_filename(basefilename + "diphoton_fake_rate_real_templates_all_GGJets_GJets_" + cmssw_version[era] + "_nPV0-200_MiniAOD_histograms.root");
  TFile *historealmcfile;
  historealmcfile = TFile::Open(mc_filename);

  double sidebandLow = sideband.first;
  double sidebandHigh = sideband.second;
  TString postFix = "";
  if (templateVariable == "sieie")
    postFix = TString::Format("_chIso%dTo%d",(int)sidebandLow,(int)sidebandHigh);
  else if (templateVariable == "chIso")
    postFix = TString::Format("_sieie%.4fTo%.4f",sidebandLow,sidebandHigh);

  // ---get histograms
  // Fake Templates
  TString temp;
  TString histName;

  if (sample == "alltruth"){
     temp = "_numerator_fakes_pt";
     histName = templateVariable + etaBin + temp + ptBin ;
  }
  else{
    temp = "_faketemplate_pt";
    histName = templateVariable + etaBin + temp + ptBin + postFix ;
  }


  std::cout << "Getting " << histName << std::endl;
  histojetfile->Print();
  TH1D *hfakeTemplate = (TH1D*) histojetfile_templates->Get(histName);
  hfakeTemplate->Print();

  // Real Templates
  TH1D *hrealTemplate = (TH1D*) historealmcfile->Get( templateVariable + etaBin + TString("_realtemplate_pt") + ptBin );
  hrealTemplate->Print();

  // Numerator
  TH1D *hData;
  TH1D *hdenom;
  if (sample == "alltruth") {
    TFile *inputFile = TFile::Open(input_filename);
    hData = (TH1D*) inputFile->Get( templateVariable + etaBin + TString("_numerator_pt") + ptBin);
    hdenom   = (TH1D*) inputFile->Get( TString("phoPt") + etaBin + TString("_denominator_varbin") );
  }
  else{
    hData = (TH1D*) histojetfile->Get( templateVariable + etaBin + TString("_numerator_pt") + ptBin);
    hdenom   = (TH1D*) histojetfile->Get( TString("phoPt") + etaBin + TString("_denominator_varbin") );
  }
  hData->Print();
  hdenom->Print();
  // Denominator



  // avoiding 0 entries in the histograms
  // fake and real mc histos are the most critical
  for (int bincount = 1; bincount <= hfakeTemplate->GetNbinsX(); bincount++) {
    if (hfakeTemplate->GetBinContent(bincount) == 0.)
      hfakeTemplate->SetBinContent(bincount,1.e-6);
  }
  for (int bincount = 1; bincount <= hrealTemplate->GetNbinsX(); bincount++) {
    if (hrealTemplate->GetBinContent(bincount) == 0.)
      hrealTemplate->SetBinContent(bincount,1.e-6);
  }

  int ndataentries = hData->Integral();

  float templateVariableMin, templateVariableMax;
  if (templateVariable == "sieie") {
    templateVariableMin = 0.;
    templateVariableMax = 0.1;
  }
  else { // otherwise, variable is "chIso"
    templateVariableMin = 0.;
    templateVariableMax = 50.;
  }

  TString templateVariableTitle = "";
  if (templateVariable == "sieie")
    templateVariableTitle = "#sigma_{i#etai#eta}";
  else if (templateVariable == "chIso")
    templateVariableTitle = "Iso_{Ch}";

  RooRealVar template_fit_variable("template_fit_variable",templateVariableTitle.Data(),templateVariableMin,templateVariableMax);

  double template_fit_variable_cut;
  if (templateVariable == "sieie") {
    // using cuts for unsaturated photons
    etaBin.Contains("EB") ? template_fit_variable_cut = 0.0105 : template_fit_variable_cut = 0.028;
  }
  else { // otherwise assume "chIso"
    etaBin.Contains("EB") ? template_fit_variable_cut = 5.0 : template_fit_variable_cut = 5.0;
  }
  template_fit_variable.setRange("sigrange",0.0,template_fit_variable_cut);

  RooDataHist faketemplate("faketemplate","fake template",template_fit_variable,hfakeTemplate);
  RooHistPdf fakepdf("fakepdf","test hist fake pdf",template_fit_variable,faketemplate);

  RooDataHist realtemplate("realtemplate","real template",template_fit_variable,hrealTemplate);
  RooHistPdf realpdf("realpdf","test hist real pdf",template_fit_variable,realtemplate);

  RooDataHist data("data","data to be fitted to",template_fit_variable,hData);

  // RooRealVar fsig("fsig","signal fraction",0.1,0,1);

  RooRealVar signum("signum","signum",0,ndataentries);
  RooRealVar fakenum("fakenum","fakenum",0,ndataentries);

  RooExtendPdf extpdfsig("Signal","extpdfsig",realpdf,signum,"sigrange");
  RooExtendPdf extpdffake("Background","extpdffake",fakepdf,fakenum,"sigrange");

  RooAddPdf model("model","sig + background",RooArgList(extpdfsig,extpdffake));

  model.fitTo(data,RooFit::Minos(),SumW2Error(kTRUE),PrintEvalErrors(-1));

  TH1D* fitHist = (TH1D*) model.createHistogram("template_fit_variable",hData->GetNbinsX());

  double fitres = hData->Chi2Test(fitHist,"CHI2/NDF");
  cout << "CHI2 FIT RES = " << fitres << endl;

  TCanvas *canvas = new TCanvas("canvas","Fit Result",1600,600);
  canvas->Divide(2,1);

  RooPlot *xframe = template_fit_variable.frame();
  xframe->SetTitle("");

  data.plotOn(xframe);
  model.plotOn(xframe);
  model.plotOn(xframe,Components(extpdfsig),LineColor(2),LineStyle(2));
  model.plotOn(xframe,Components(extpdffake),LineColor(8),LineStyle(2));
  data.plotOn(xframe);

  canvas->cd(1);

  if (templateVariable == "sieie") {
    etaBin.Contains("EB") ? xframe->GetXaxis()->SetRangeUser(0.,0.03) : xframe->GetXaxis()->SetRangeUser(0.,0.08);
  }
  else { // otherwise assume "chIso"
    etaBin.Contains("EB") ? xframe->GetXaxis()->SetRangeUser(0.,10.) : xframe->GetXaxis()->SetRangeUser(0.,10.);
  }
  float xframemax = xframe->GetMaximum();
  xframe->GetYaxis()->SetRangeUser(1.e-1,1.1*xframemax);
  //xframe->GetYaxis()->SetTitle("#gamma Candidates / ( 0.0005 )");
  etaBin.Contains("EB") ? xframe->GetYaxis()->SetTitle("#gamma Candidates / ( 0.002 )") : xframe->GetYaxis()->SetTitle("#gamma Candidates / ( 0.004 )");
  //  xframe->GetYaxis()->SetTitleOffset(1.6);
  xframe->Draw();

  TString label_pt_bin = ptBin;
  label_pt_bin.ReplaceAll("To"," < p_{T} < ");

  TString sideband_string;
  if (templateVariable == "sieie")
    sideband_string = TString::Format("%d < Iso_{Ch} < %d GeV",(int)sidebandLow,(int)sidebandHigh);
  else if (templateVariable == "chIso")
    sideband_string = TString::Format("%.4f < #sigma_{i#etai#eta} < %.3f",sidebandLow,sidebandHigh);

  TLatex *t_label = new TLatex();
  t_label->SetTextAlign(12);
  if (etaBin == "EB") t_label->DrawLatexNDC(0.55,0.60,"ECAL barrel");
  else t_label->DrawLatexNDC(0.55,0.60,"ECAL endcap");
  t_label->     DrawLatexNDC(0.55,0.55,label_pt_bin + " GeV");
  t_label->     DrawLatexNDC(0.55,0.50,sideband_string);
  t_label->DrawLatexNDC(0.17, 0.975, "#font[62]{CMS} #scale[0.8]{#font[52]{Preliminary}}");
  t_label->SetTextFont(42);
  t_label->DrawLatexNDC(0.70, 0.975, Form("%1.1f fb^{-1} (13 TeV)", luminosity[era.Data()]));
  //  t_label->     DrawLatexNDC(0.55,0.45,TString::Format("#chi^{2}/ndf = %6.1f",fitres));

  TObject *objdata = nullptr;
  TObject *objmodel = nullptr;
  TObject *objsignal = nullptr;
  TObject *objfake = nullptr;

  for (int i = 0; i < xframe->numItems(); i++) {
    cout << xframe->nameOf(i) << endl;
    TString objname = xframe->nameOf(i);
    if (objname.Contains("data"))                                    objdata = (TObject*) xframe->findObject(objname.Data());
    if (objname.Contains("model") && !objname.Contains("Comp"))      objmodel = (TObject*) xframe->findObject(objname.Data());
    if (objname.Contains("model") && objname.Contains("Signal"))     objsignal = (TObject*) xframe->findObject(objname.Data());
    if (objname.Contains("model") && objname.Contains("Background")) objfake = (TObject*) xframe->findObject(objname.Data());
  }

  TLegend *legend = new TLegend(0.55,0.65,0.85,0.85);
  legend->SetTextSize(0.03);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->SetFillStyle(0);
  legend->AddEntry(objdata," Numerator candidates","ep");
  legend->AddEntry(objsignal," Real template","l");
  legend->AddEntry(objfake," Fake template","l");
  legend->AddEntry(objmodel," Combined fit","l");
  legend->Draw("same");

  canvas->cd(2);

  RooPlot *xframeClone = (RooPlot*)xframe->emptyClone("xframeClone");
  xframeClone->SetTitle("");

  xframeClone->Draw();
  xframe->Draw("same");

  //  t_label->DrawLatexNDC(0.17,0.975,txt);

  if (templateVariable == "sieie") {
    etaBin.Contains("EB") ? xframeClone->GetXaxis()->SetRangeUser(0.,0.03) : xframeClone->GetXaxis()->SetRangeUser(0.,0.08);
  }
  else { // otherwise "chIso"
    etaBin.Contains("EB") ? xframeClone->GetXaxis()->SetRangeUser(0.,50.) : xframeClone->GetXaxis()->SetRangeUser(0.,50.);
  }
  xframeClone->GetYaxis()->SetRangeUser(1.e-1,10.0*xframemax);
  // xframeClone->GetYaxis()->SetTitle("#gamma Candidates / ( 0.0005 )");
  etaBin.Contains("EB") ? xframe->GetYaxis()->SetTitle("#gamma Candidates / ( 0.002 )") : xframe->GetYaxis()->SetTitle("#gamma Candidates / ( 0.004 )");
  //  xframeClone->GetYaxis()->SetTitle(xframe->GetYaxis()->GetTitle());
  xframeClone->GetYaxis()->SetTitleOffset(1.2);

  gPad->SetLogy();
  canvas->Print( TString("plots/fakeRatePlot_") + sample + "_" + era + "_" +  etaBin + TString("_pT") + ptBin + postFix + TString(".pdf") );

  // change to TH1D just so we can change the name
  TH1D *hobjdata = nullptr;
  TH1D *hobjmodel = nullptr;
  TH1D *hobjsignal = nullptr;
  TH1D *hobjfake = nullptr;
  for (int i = 0; i < xframe->numItems(); i++) {
    cout << xframe->nameOf(i) << endl;
    TString objname = xframe->nameOf(i);
    if (objname.Contains("data"))                                    hobjdata   = (TH1D*) xframe->findObject(objname.Data());
    if (objname.Contains("model") && !objname.Contains("Comp"))      hobjmodel  = (TH1D*) xframe->findObject(objname.Data());
    if (objname.Contains("model") && objname.Contains("Signal"))     hobjsignal = (TH1D*) xframe->findObject(objname.Data());
    if (objname.Contains("model") && objname.Contains("Background")) hobjfake   = (TH1D*) xframe->findObject(objname.Data());
  }

  hobjdata->  SetName( TString("data")          + etaBin + TString("_pt") + ptBin + postFix );
  hobjmodel-> SetName( TString("sigplusbkgfit") + etaBin + TString("_pt") + ptBin + postFix );
  hobjsignal->SetName( TString("signalfit")     + etaBin + TString("_pt") + ptBin + postFix );
  hobjfake->  SetName( TString("bkgfit")        + etaBin + TString("_pt") + ptBin + postFix );

  TFile outfile("fakeRatePlots_" + sample + "_" + era + pvCut + ".root","update");
  outfile.cd();
  hobjdata->Write();
  hobjmodel->Write();
  hobjsignal->Write();
  hobjfake->Write();

  float fakevalue = fakenum.getValV();
  float fakeerrorhi = fakenum.getErrorHi();
  float fakeerrorlo = fakenum.getErrorLo();
  float fakeerrormax = max(fabs(fakeerrorhi),fabs(fakeerrorlo));
  TString fakeresults = TString::Format("Fake results %f +%f %f",fakevalue,fakeerrorhi,fakeerrorlo);

  float sigvalue = signum.getValV();
  float sigerrorhi = signum.getErrorHi();
  float sigerrorlo = signum.getErrorLo();
  float sigerrormax = max(fabs(sigerrorhi),fabs(sigerrorlo));
  TString sigresults = TString::Format("Signal results %f +%f %f",sigvalue,sigerrorhi,sigerrorlo);

  cout << "sigvalue " << sigvalue << " sigerrormax " << sigerrormax << " sigerrormax/sigvalue " << sigerrormax/sigvalue << endl;
  cout << "fakevalue " << fakevalue << " fakeerrormax " << fakeerrormax << " fakeerrormax/fakevalue " << fakeerrormax/fakevalue << endl;

  cout << fakeresults.Data() << endl;
  cout << sigresults.Data() << endl;

  float Ratio = (fakevalue/(fakevalue+sigvalue));
  float RatioError = Ratio*sqrt( ((fakeerrormax/fakevalue)*(fakeerrormax/fakevalue) + (sigerrormax/sigvalue)*(sigerrormax/sigvalue)) );
  cout << "Ratio " << Ratio << " +- " << RatioError << endl;

  float numerator = hData->Integral(0,hData->FindBin(template_fit_variable_cut)-1); // integrate to bin with upper edge at sieie cute
  float denominator = hdenom->GetBinContent( denomBin ); // pT bin in denominator pT distribution
  float contamination = sigvalue;

  cout << numerator << " " << denominator << " " << contamination << endl;

  float fakerate = fakevalue/denominator;
  float fakerateerror = TMath::Sqrt((fakeerrormax*fakeerrormax/denominator/denominator) + (fakerate*fakerate/denominator));

  cout << "Here: " << fakerate << " " << fakerateerror << endl;
  cout << "Ending rooFitClosureTest" << endl;
  cout << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;

  return std::make_pair(fakevalue,fakeerrormax);

  histojetfile->cd();
  histojetfile->Close();

  historealmcfile->cd();
  historealmcfile->Close();

} // end of rooFitClosureTest()
