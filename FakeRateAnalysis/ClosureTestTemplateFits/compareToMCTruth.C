TString graphNamer(std::string region, std::string iso){
  const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
  return graphName;
}

// double fakeRateRatioUncertainty(double erra, double errb, double a, double b) {
//   double uncert = TMath::Sqrt((erra*erra/(a*a)) + (errb*errb/(b*b)));
//   return uncert;
// }

float fakeRateRatioUncertainty(float sigA, float sigB, float muA, float muB, bool isProd){
    float mu;
    if (isProd) mu = muA*muB;
    else mu = muB/muA;

    float fracErr = TMath::Sqrt((sigA*sigA/ muA*muA) + (sigB*sigB / muB*muB));
    float sigma = fracErr * mu;

    return sigma;
}


void add_grPlus(int year, std::string region="EE"){
  auto c1 = new TCanvas("c1","c1",200,10,700,500);
  auto mg = new TMultiGraph();

  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==NULL) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    exit(-1);
  }

  TFile *fFake = TFile::Open(Form("%s/src/fakeRatePlots_all_%d_nPV0-200.root", cmssw_base, year));
  TFile *fTruth = TFile::Open(Form("%s/src/fakeRatePlots_alltruth_%d_nPV0-200.root", cmssw_base, year));

  const std::string iso("chIso5To10");
  // const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));

  auto grTruth = dynamic_cast<TGraphAsymmErrors*>(fTruth->Get(graphNamer(region, iso)));
  auto grFake = dynamic_cast<TGraphAsymmErrors*>(fFake->Get(graphNamer(region, iso)));

  grTruth->SetLineColor(kOrange);
  grFake->SetLineColor(kRed);
  mg->Add(grTruth); grTruth->SetTitle("MC as Truth"); //grTruth->SetLineWidth(3);
  mg->Add(grFake); grFake->SetTitle("chIso5To10")  ; //grFake->SetLineWidth(3);


  auto grFake1 = dynamic_cast<TGraphAsymmErrors*>(fFake->Get(graphNamer(region, "chIso10To15")));
  auto grFake2 = dynamic_cast<TGraphAsymmErrors*>(fFake->Get(graphNamer(region, "chIso15To20")));
  grFake1->SetLineColor(kBlue);
  grFake2->SetLineColor(kBlack);
  mg->Add(grFake1); grFake1->SetTitle("chIso10To15");
  mg->Add(grFake2); grFake2->SetTitle("chIso15To20");

  mg->SetTitle(Form("Closure Test %s %s", std::to_string(year).c_str(), region.c_str()));
  mg->Draw("apl");
  //c1->BuildLegend();
  c1->BuildLegend(0.6,0.68,0.8,0.88);
  c1->SaveAs(Form("closureTest_MCTruth_comparisons%s_%sPlus.pdf", region.c_str(), std::to_string(year).c_str()));
  return 0;
}

void add_gr(int year, std::string region="EE", bool adjustrange=false){

  auto c1 = new TCanvas("c1","c1",200,10,700,500);
  auto mg = new TMultiGraph();

  auto *padRatio = new TPad("padRatio","padRatio",0.,0.,1.,0.3); padRatio->Draw();
  padRatio->SetTopMargin(0.001);
  padRatio->SetBottomMargin(0.3);
  // padRatio->SetLogx ();
  padRatio->SetGrid();

  auto *p1 = new TPad("p1","p1",0.,0.3,1.,1.);  p1->Draw();
  p1->SetBottomMargin(0.08);
  p1->cd();
  p1->SetGrid();
  //p1->SetLogx();
  //p1->SetLogy();

  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==NULL) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    exit(-1);
  }

  TFile *fFake = TFile::Open(Form("%s/src/fakeRatePlots_all_%d_nPV0-200.root", cmssw_base, year));
  TFile *fTruth = TFile::Open(Form("%s/src/fakeRatePlots_alltruth_%d_nPV0-200.root", cmssw_base, year));

  const std::string iso("chIso5To10");
  // const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));

  auto grTruth = dynamic_cast<TGraphAsymmErrors*>(fTruth->Get(graphNamer(region, iso)));
  auto grFake = dynamic_cast<TGraphAsymmErrors*>(fFake->Get(graphNamer(region, iso)));

  grTruth->SetLineColor(kOrange);
  grFake->SetLineColor(kRed);
  mg->Add(grTruth); grTruth->SetTitle("MC as Truth"); //grTruth->SetLineWidth(3);
  mg->Add(grFake); grFake->SetTitle("chIso5To10"); //grFake->SetLineWidth(3);

  mg->SetTitle(Form("Closure Test %s %s", std::to_string(year).c_str(), region.c_str()));

  mg->Draw("apl");
  //c1->BuildLegend();
  p1->BuildLegend(0.6,0.68,0.8,0.88);
  mg->GetHistogram()->GetXaxis()->SetRangeUser(0.,2.5);
  mg->GetHistogram()->GetXaxis()->SetRangeUser(0.,2.5);
  mg->GetXaxis()->SetLimits(0., 630.);
  if  (region=="EB" && adjustrange) mg->GetHistogram()->GetYaxis()->SetRangeUser(0.,0.3);
  if  (region=="EE" && adjustrange) mg->GetHistogram()->GetYaxis()->SetRangeUser(0.,0.7);

  gPad->Modified();
  gPad->Update();

  // Ratio Plot
  padRatio->cd();
  std::vector<int> ptBinArray({ 50, 70, 90, 110, 130, 150, 200, 250, 300, 600});
  std::vector<double> ptBinArray_double;
  for (auto iBin : ptBinArray) {
    ptBinArray_double.push_back(static_cast<double>(iBin));
  }

  const int nBins = ptBinArray.size();
  TGraphAsymmErrors* r = new TGraphAsymmErrors();

  for (int i = 0; i < nBins-1; i++){
    double ptLow = ptBinArray_double[i];
    double ptHigh = ptBinArray_double[i+1];
    double ptBinSize = ptHigh - ptLow;
    TString binName = TString::Format("%iTo%i",ptBinArray[i],ptBinArray[i+1]);

    // double pt = (ptLow+ptHigh)/2;
    double pt = grFake->GetX()[i];
    double y = grFake->Eval(pt)/grTruth->Eval(pt);
    std::cout << "pt: " << pt  << "; FakeRate: " << y;
    // error
    // double errFakeY = grFake->GetErrorY(y);
    // double errTruthY = grTruth->GetErrorY(y);
    // double errY = fakeRateRatioUncertainty(errTruthY, errFakeY, grTruth->Eval(pt), grFake->Eval(pt), false);
    //
    // double errFakeX = grFake->GetErrorX(pt);
    // double errTruthX = grTruth->GetErrorX(pt);
    // // double errX = fakeRateRatioUncertainty(errFakeX, errTruthX, pt, pt);
    // double errX = errFakeX;

    // error
    double errFakeY = grFake->GetErrorYhigh(i) - grFake->GetErrorYlow(i);
    double errTruthY = grTruth->GetErrorYhigh(i) - grTruth->GetErrorYlow(y);
    double errY = fakeRateRatioUncertainty(errTruthY, errFakeY, grTruth->Eval(pt), grFake->Eval(pt), false);

    double errFakeX = grFake->GetErrorXhigh(i) - grFake->GetErrorXlow(i);
    double errTruthX = grTruth->GetErrorXhigh(i) - grTruth->GetErrorXlow(i);
    // double errX = fakeRateRatioUncertainty(errFakeX, errTruthX, pt, pt);
    double errX = errFakeX;

    r->SetPoint(i, pt, y);
    r->SetPointError(i, errX, errX, errY, errY);


    std::cout << binName << ": " << pt << ": "
              << "fakeRate Truth:" << grTruth->Eval(pt) << ": "
              << "fakeRate Fake:" << grFake->Eval(pt) << ": "
              << "fakeRate Ratio:" << y << ": "
              << "gRFake errY: " << errFakeY << ": "
              << "gRTruth errY: " << errTruthY << ": "
              << "gRFake errX: " << errFakeX << ": "
              << "gRTruth errX: " << errTruthY
              << std::endl;
  }
  r->GetHistogram()->GetXaxis()->SetTitle("pT (GeV)");
  r->GetHistogram()->GetYaxis()->SetTitle("Fake/Truth  ");

  r->GetXaxis()->SetTitleSize(0.09);
  r->GetYaxis()->SetTitleSize(0.075);
  r->GetXaxis()->SetTitleOffset(0.8);

  //r->GetHistogram->GetXaxis()->SetRangeUser(0.,2.5);
  r->GetXaxis()->SetLimits(0., 630.);

  c1->Update();

  r->GetXaxis()->SetLabelSize(0.075);
  r->GetYaxis()->SetLabelSize(0.075);
  r->GetYaxis()->SetTitleOffset(0.5);
  // r->Draw("AL");
  r->Draw("AP"); // Draw Points only

  if (adjustrange) c1->SaveAs(Form("closureTest_MCTruth_comparisons%s_%s_adjustrange.pdf", region.c_str(), std::to_string(year).c_str()));
  else c1->SaveAs(Form("closureTest_MCTruth_comparisons%s_%s.pdf", region.c_str(), std::to_string(year).c_str()));

  return 0;

}

void compareToMCTruth(int year=2016, bool setBatch=true){

   if (setBatch) gROOT->SetBatch();

   add_gr(year, "EB");
   add_gr(year, "EE");
   add_grPlus(year, "EB");
   add_grPlus(year, "EE");
   add_gr(year, "EB", true);
   add_gr(year, "EE", true);

   return 0;
}
