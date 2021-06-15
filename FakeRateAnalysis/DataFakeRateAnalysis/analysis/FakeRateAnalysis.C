#define FakeRateAnalysis_cxx
#include "FakeRateAnalysis.h"
#include <TLorentzVector.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>

void FakeRateAnalysisBase::Loop() {};

class FakeRateAnalysis : public FakeRateAnalysisBase {

public:
  using FakeRateAnalysisBase::FakeRateAnalysisBase;
  void Loop() {};
  void Loop(int iCut = 0, TString era="UNKNOWN", TString dataset="UNKNOWN", int pvCutLow = 0, int pvCutHigh = 500);
};


void FakeRateAnalysis::Loop(int iCut, TString era, TString dataset, int pvCutLow, int pvCutHigh)
{
//   In a ROOT session, you can do:
//      root> .L FakeRateAnalysis.C
//      root> FakeRateAnalysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  // cout << "Now looping over data using the following chIso sideband definition: " << sidebandLow << "-" << sidebandHigh << " GeV." << endl;
  
  // array of pt bin edges
  std::vector<double> ptBinArray({ 50., 70., 90., 110., 130., 150.});
  // With higher statistics in JetHT sample, additional bins can be used
  if(dataset=="jetht") {
    ptBinArray.push_back(200.);
    ptBinArray.push_back(250.);
    ptBinArray.push_back(300.);
  }
  ptBinArray.push_back(600.);
  const int nBins = ptBinArray.size();


  // make vector of sidebands
  std::vector< std::pair<double,double> > chIsoSidebands;
  typedef std::vector< std::pair<double,double> >::const_iterator chIsoIt;
  chIsoSidebands.push_back( std::make_pair(5.,10.) );
  chIsoSidebands.push_back( std::make_pair(6.,11.) );
  chIsoSidebands.push_back( std::make_pair(7.,12.) );
  chIsoSidebands.push_back( std::make_pair(8.,13.) );
  chIsoSidebands.push_back( std::make_pair(9.,14.) );
  chIsoSidebands.push_back( std::make_pair(10.,15.) );
  chIsoSidebands.push_back( std::make_pair(15.,20.) );
  chIsoSidebands.push_back( std::make_pair(10.,20.) );

  // pt spectrum of all photon objects
  TH1D phoPtEB("phoPtEB","",1000,0.,2500.);
  TH1D phoPtEE("phoPtEE","",1000,0.,2500.);
  TH1D phoPtEE1("phoPtEE1","",1000,0.,2500.);
  TH1D phoPtEE2("phoPtEE2","",1000,0.,2500.);

  // pt spectrum of all numerator objects
  TH1D phoPtEB_numerator("phoPtEB_numerator","",1000,0.,2500.);
  TH1D phoPtEE_numerator("phoPtEE_numerator","",1000,0.,2500.);
  TH1D phoPtEE1_numerator("phoPtEE1_numerator","",1000,0.,2500.);
  TH1D phoPtEE2_numerator("phoPtEE2_numerator","",1000,0.,2500.);
  TH1D phoPtEB_numerator_varbin("phoPtEB_numerator_varbin", "", nBins-1, ptBinArray.data());
  TH1D phoPtEE_numerator_varbin("phoPtEE_numerator_varbin", "", nBins-1, ptBinArray.data());
  TH1D phoPtEE1_numerator_varbin("phoPtEE1_numerator_varbin", "", nBins-1, ptBinArray.data());
  TH1D phoPtEE2_numerator_varbin("phoPtEE2_numerator_varbin", "", nBins-1, ptBinArray.data());

  // pt spectrum of denominator objects
  TH1D phoPtEB_denominator("phoPtEB_denominator","",1000,0.,2500.);
  TH1D phoPtEE_denominator("phoPtEE_denominator","",1000,0.,2500.);
  TH1D phoPtEE1_denominator("phoPtEE1_denominator","",1000,0.,2500.);
  TH1D phoPtEE2_denominator("phoPtEE2_denominator","",1000,0.,2500.);
  TH1D phoPtEB_denominator_varbin("phoPtEB_denominator_varbin", "", nBins-1, ptBinArray.data());
  TH1D phoPtEE_denominator_varbin("phoPtEE_denominator_varbin", "", nBins-1, ptBinArray.data());
  TH1D phoPtEE1_denominator_varbin("phoPtEE1_denominator_varbin", "", nBins-1, ptBinArray.data());
  TH1D phoPtEE2_denominator_varbin("phoPtEE2_denominator_varbin", "", nBins-1, ptBinArray.data());

  // pt spectrum of all objects passing fake template criteria
  // TH1D phoPtEB_faketemplate("phoPtEB_faketemplate","",1000,0.,2500.);
  // TH1D phoPtEE_faketemplate("phoPtEE_faketemplate","",1000,0.,2500.);
  // TH1D phoPtEB_faketemplate_varbin("phoPtEB_faketemplate_varbin","",10,ptBinArray);
  // TH1D phoPtEE_faketemplate_varbin("phoPtEE_faketemplate_varbin","",10,ptBinArray);

  std::vector<TH1D*> phoPtEB_faketemplates; // vector of fake photon pT distributions, one for each sideband definition
  std::vector<TH1D*> phoPtEE_faketemplates;
  std::vector<TH1D*> phoPtEE1_faketemplates;
  std::vector<TH1D*> phoPtEE2_faketemplates;

  for (chIsoIt it = chIsoSidebands.begin(); it != chIsoSidebands.end(); ++it){
    double sidebandLow = it->first;
    double sidebandHigh = it->second;

    TH1D* phoPt_fake_EB = new TH1D(Form( "phoPtEB_faketemplate_chIso%dTo%d",(int)sidebandLow,(int)sidebandHigh ),"",1000,0.,2500.);
    phoPt_fake_EB->Sumw2();
    phoPtEB_faketemplates.push_back(phoPt_fake_EB);

    TH1D* phoPt_fake_EE = new TH1D(Form( "phoPtEE_faketemplate_chIso%dTo%d",(int)sidebandLow,(int)sidebandHigh ),"",1000,0.,2500.);
    phoPt_fake_EE->Sumw2();
    phoPtEE_faketemplates.push_back(phoPt_fake_EE);

    TH1D* phoPt_fake_EE1 = new TH1D(Form( "phoPtEE1_faketemplate_chIso%dTo%d",(int)sidebandLow,(int)sidebandHigh ),"",1000,0.,2500.);
    phoPt_fake_EE1->Sumw2();
    phoPtEE1_faketemplates.push_back(phoPt_fake_EE1);

    TH1D* phoPt_fake_EE2 = new TH1D(Form( "phoPtEE2_faketemplate_chIso%dTo%d",(int)sidebandLow,(int)sidebandHigh ),"",1000,0.,2500.);
    phoPt_fake_EE2->Sumw2();
    phoPtEE2_faketemplates.push_back(phoPt_fake_EE2);
    
  }

  phoPtEB.Sumw2();
  phoPtEE.Sumw2();
  phoPtEE1.Sumw2();
  phoPtEE2.Sumw2();
  phoPtEB_numerator_varbin.Sumw2();
  phoPtEE_numerator_varbin.Sumw2();
  phoPtEE1_numerator_varbin.Sumw2();
  phoPtEE2_numerator_varbin.Sumw2();
  phoPtEB_denominator_varbin.Sumw2();
  phoPtEE_denominator_varbin.Sumw2();
  phoPtEE1_denominator_varbin.Sumw2();
  phoPtEE2_denominator_varbin.Sumw2();
  // phoPtEB_faketemplate_varbin.Sumw2();
  // phoPtEE_faketemplate_varbin.Sumw2();

  // numerator and template histograms
  std::vector< std::vector<TH1D*> > sIeIeFakeTemplatesEB; // for each pT bin, there will be a vector of templates, one for each chIso sideband definition
  std::vector< std::vector<TH1D*> > sIeIeFakeTemplatesEE;
  std::vector< std::vector<TH1D*> > sIeIeFakeTemplatesEE1;
  std::vector< std::vector<TH1D*> > sIeIeFakeTemplatesEE2;
  // create empty vectors to hold all the templates.  One vector for each pT bin
  for (int i=0; i<nBins-1; i++){
    std::vector<TH1D*> ebvec;
    std::vector<TH1D*> eevec;
    sIeIeFakeTemplatesEB.push_back(ebvec);
    sIeIeFakeTemplatesEE.push_back(eevec);
    sIeIeFakeTemplatesEE1.push_back(eevec);
    sIeIeFakeTemplatesEE2.push_back(eevec);
  }

  TH1D* leadingjetPhoDrEB_numerator = new TH1D("leadingjetPhoDrEB_numerator","leadingjetPhoDrEB_numerator",500,0.,5.);
  TH1D* leadingjetPhoDrEE_numerator = new TH1D("leadingjetPhoDrEE_numerator","leadingjetPhoDrEE_numerator",500,0.,5.);
  TH1D* leadingjetPhoDrEE1_numerator = new TH1D("leadingjetPhoDrEE1_numerator","leadingjetPhoDrEE1_numerator",500,0.,5.);
  TH1D* leadingjetPhoDrEE2_numerator = new TH1D("leadingjetPhoDrEE2_numerator","leadingjetPhoDrEE2_numerator",500,0.,5.);

  TH1D* leadingjetPhoDrEB_faketemplate = new TH1D("leadingjetPhoDrEB_faketemplate","leadingjetPhoDrEB_faketemplate",500,0.,5.);
  TH1D* leadingjetPhoDrEE_faketemplate = new TH1D("leadingjetPhoDrEE_faketemplate","leadingjetPhoDrEE_faketemplate",500,0.,5.);
  TH1D* leadingjetPhoDrEE1_faketemplate = new TH1D("leadingjetPhoDrEE1_faketemplate","leadingjetPhoDrEE1_faketemplate",500,0.,5.);
  TH1D* leadingjetPhoDrEE2_faketemplate = new TH1D("leadingjetPhoDrEE2_faketemplate","leadingjetPhoDrEE2_faketemplate",500,0.,5.);

  TH1D* leadingjetPhoDrEB_denominator = new TH1D("leadingjetPhoDrEB_denominator","leadingjetPhoDrEB_denominator",500,0.,5.);
  TH1D* leadingjetPhoDrEE_denominator = new TH1D("leadingjetPhoDrEE_denominator","leadingjetPhoDrEE_denominator",500,0.,5.);
  TH1D* leadingjetPhoDrEE1_denominator = new TH1D("leadingjetPhoDrEE1_denominator","leadingjetPhoDrEE1_denominator",500,0.,5.);
  TH1D* leadingjetPhoDrEE2_denominator = new TH1D("leadingjetPhoDrEE2_denominator","leadingjetPhoDrEE2_denominator",500,0.,5.);

  TH1D* secondleadingjetPhoDrEB_numerator = new TH1D("secondleadingjetPhoDrEB_numerator","secondleadingjetPhoDrEB_numerator",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE_numerator = new TH1D("secondleadingjetPhoDrEE_numerator","secondleadingjetPhoDrEE_numerator",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE1_numerator = new TH1D("secondleadingjetPhoDrEE1_numerator","secondleadingjetPhoDrEE1_numerator",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE2_numerator = new TH1D("secondleadingjetPhoDrEE2_numerator","secondleadingjetPhoDrEE2_numerator",500,0.,5.);

  TH1D* secondleadingjetPhoDrEB_faketemplate = new TH1D("secondleadingjetPhoDrEB_faketemplate","secondleadingjetPhoDrEB_faketemplate",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE_faketemplate = new TH1D("secondleadingjetPhoDrEE_faketemplate","secondleadingjetPhoDrEE_faketemplate",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE1_faketemplate = new TH1D("secondleadingjetPhoDrEE1_faketemplate","secondleadingjetPhoDrEE1_faketemplate",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE2_faketemplate = new TH1D("secondleadingjetPhoDrEE2_faketemplate","secondleadingjetPhoDrEE2_faketemplate",500,0.,5.);

  TH1D* secondleadingjetPhoDrEB_denominator = new TH1D("secondleadingjetPhoDrEB_denominator","secondleadingjetPhoDrEB_denominator",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE_denominator = new TH1D("secondleadingjetPhoDrEE_denominator","secondleadingjetPhoDrEE_denominator",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE1_denominator = new TH1D("secondleadingjetPhoDrEE1_denominator","secondleadingjetPhoDrEE1_denominator",500,0.,5.);
  TH1D* secondleadingjetPhoDrEE2_denominator = new TH1D("secondleadingjetPhoDrEE2_denominator","secondleadingjetPhoDrEE2_denominator",500,0.,5.);

  TH1D* thirdleadingjetPhoDrEB_numerator = new TH1D("thirdleadingjetPhoDrEB_numerator","thirdleadingjetPhoDrEB_numerator",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE_numerator = new TH1D("thirdleadingjetPhoDrEE_numerator","thirdleadingjetPhoDrEE_numerator",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE1_numerator = new TH1D("thirdleadingjetPhoDrEE1_numerator","thirdleadingjetPhoDrEE1_numerator",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE2_numerator = new TH1D("thirdleadingjetPhoDrEE2_numerator","thirdleadingjetPhoDrEE2_numerator",500,0.,5.);

  TH1D* thirdleadingjetPhoDrEB_faketemplate = new TH1D("thirdleadingjetPhoDrEB_faketemplate","thirdleadingjetPhoDrEB_faketemplate",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE_faketemplate = new TH1D("thirdleadingjetPhoDrEE_faketemplate","thirdleadingjetPhoDrEE_faketemplate",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE1_faketemplate = new TH1D("thirdleadingjetPhoDrEE1_faketemplate","thirdleadingjetPhoDrEE1_faketemplate",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE2_faketemplate = new TH1D("thirdleadingjetPhoDrEE2_faketemplate","thirdleadingjetPhoDrEE2_faketemplate",500,0.,5.);

  TH1D* thirdleadingjetPhoDrEB_denominator = new TH1D("thirdleadingjetPhoDrEB_denominator","thirdleadingjetPhoDrEB_denominator",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE_denominator = new TH1D("thirdleadingjetPhoDrEE_denominator","thirdleadingjetPhoDrEE_denominator",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE1_denominator = new TH1D("thirdleadingjetPhoDrEE1_denominator","thirdleadingjetPhoDrEE1_denominator",500,0.,5.);
  TH1D* thirdleadingjetPhoDrEE2_denominator = new TH1D("thirdleadingjetPhoDrEE2_denominator","thirdleadingjetPhoDrEE2_denominator",500,0.,5.);

  std::vector<TH1D*> sIeIeNumeratorEB;
  std::vector<TH1D*> sIeIeNumeratorEE;
  std::vector<TH1D*> sIeIeNumeratorEE1;
  std::vector<TH1D*> sIeIeNumeratorEE2;
  std::vector<TH1D*> denomPtEB;
  std::vector<TH1D*> denomPtEE;
  std::vector<TH1D*> denomPtEE1;
  std::vector<TH1D*> denomPtEE2;

  // loop over bins increments and create histograms
  for (int i = 0; i < nBins-1; i++) {
    double binLowEdge = ptBinArray[i];
    double binUpperEdge = ptBinArray[i+1];

    for (chIsoIt it = chIsoSidebands.begin(); it != chIsoSidebands.end(); ++it){

      double sidebandLow = it->first;
      double sidebandHigh = it->second;

      TH1D* sieieEB_faketemplate = new TH1D(Form( "sieieEB_faketemplate_pt%dTo%d_chIso%dTo%d",(int)binLowEdge,(int)binUpperEdge,(int)sidebandLow,(int)sidebandHigh ),"",200,0.,0.1);
      sieieEB_faketemplate->Sumw2();
      sIeIeFakeTemplatesEB.at(i).push_back( sieieEB_faketemplate );

      TH1D* sieieEE_faketemplate = new TH1D(Form( "sieieEE_faketemplate_pt%dTo%d_chIso%dTo%d",(int)binLowEdge,(int)binUpperEdge,(int)sidebandLow,(int)sidebandHigh ),"",200,0.,0.1);
      sieieEE_faketemplate->Sumw2();
      sIeIeFakeTemplatesEE.at(i).push_back( sieieEE_faketemplate );

      TH1D* sieieEE1_faketemplate = new TH1D(Form( "sieieEE1_faketemplate_pt%dTo%d_chIso%dTo%d",(int)binLowEdge,(int)binUpperEdge,(int)sidebandLow,(int)sidebandHigh ),"",200,0.,0.1);
      sieieEE1_faketemplate->Sumw2();
      sIeIeFakeTemplatesEE1.at(i).push_back( sieieEE1_faketemplate );

      TH1D* sieieEE2_faketemplate = new TH1D(Form( "sieieEE2_faketemplate_pt%dTo%d_chIso%dTo%d",(int)binLowEdge,(int)binUpperEdge,(int)sidebandLow,(int)sidebandHigh ),"",200,0.,0.1);
      sieieEE2_faketemplate->Sumw2();
      sIeIeFakeTemplatesEE2.at(i).push_back( sieieEE2_faketemplate );

    } // end loop over sidebands
    
    // TH1D *hEB_fakeTemplate = new TH1D(Form("sieieEB_faketemplate_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"sigmaIetaIetaEB",200,0.,0.1);
    // hEB_fakeTemplate->Sumw2();
    // sIeIeFakeTemplateEB.push_back(hEB_fakeTemplate);
    
    // TH1D *hEE_fakeTemplate = new TH1D(Form("sieieEE_faketemplate_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"sigmaIetaIetaEE",200,0.,0.1);
    // hEE_fakeTemplate->Sumw2();
    // sIeIeFakeTemplateEE.push_back(hEE_fakeTemplate);

    TH1D *hEB_numerator = new TH1D(Form("sieieEB_numerator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"sigmaIetaIetaEB",200,0.,0.1);
    hEB_numerator->Sumw2();
    sIeIeNumeratorEB.push_back(hEB_numerator);

    TH1D *hEE_numerator = new TH1D(Form("sieieEE_numerator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"sigmaIetaIetaEE",200,0.,0.1);
    hEE_numerator->Sumw2();
    sIeIeNumeratorEE.push_back(hEE_numerator);

    TH1D *hEE1_numerator = new TH1D(Form("sieieEE1_numerator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"sigmaIetaIetaEE1",200,0.,0.1);
    hEE1_numerator->Sumw2();
    sIeIeNumeratorEE1.push_back(hEE1_numerator);

    TH1D *hEE2_numerator = new TH1D(Form("sieieEE2_numerator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"sigmaIetaIetaEE2",200,0.,0.1);
    hEE2_numerator->Sumw2();
    sIeIeNumeratorEE2.push_back(hEE2_numerator);

    // pt binned denominator histograms
    TH1D *hEB_denominator = new TH1D(Form("PtEB_denominator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"PtEB",100,binLowEdge,binUpperEdge);
    hEB_denominator->Sumw2();
    denomPtEB.push_back(hEB_denominator);

    TH1D *hEE_denominator = new TH1D(Form("PtEE_denominator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"PtEE",100,binLowEdge,binUpperEdge);
    hEE_denominator->Sumw2();
    denomPtEE.push_back(hEE_denominator);

    TH1D *hEE1_denominator = new TH1D(Form("PtEE1_denominator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"PtEE1",100,binLowEdge,binUpperEdge);
    hEE1_denominator->Sumw2();
    denomPtEE1.push_back(hEE1_denominator);

    TH1D *hEE2_denominator = new TH1D(Form("PtEE2_denominator_pt%dTo%d",(int)binLowEdge,(int)binUpperEdge),"PtEE2",100,binLowEdge,binUpperEdge);
    hEE2_denominator->Sumw2();
    denomPtEE2.push_back(hEE2_denominator);

  }

  // pileup debug plots

  TH1D* chIsoEB_pT50To70_denom = new TH1D("chIsoEB_pT50To70_denom","",100,0.,50.);
  TH1D* phoIsoEB_pT50To70_denom = new TH1D("phoIsoEB_pT50To70_denom","",200,-50.,50.);
  TH1D* hOverEEB_pT50To70_denom = new TH1D("hOverEBE_pT50To70_denom","",100,0.,0.16);
  TH1D* sieieEB_pT50To70_denom = new TH1D("sieieEB_pT50To70_denom","",100,0.,0.1);
  TH1D* chIsoEB_pT50To70_num = new TH1D("chIsoEB_pT50To70_num","",100,0.,5.);
  TH1D* phoIsoEB_pT50To70_num = new TH1D("phoIsoEB_pT50To70_num","",650,-50.,3.);
  TH1D* hOverEEB_pT50To70_num = new TH1D("hOverEBE_pT50To70_num","",100,0.,0.05);
  TH1D* sieieEB_pT50To70_num = new TH1D("sieieEB_pT50To70_num","",100,0.,0.03);

  TH1D* chIsoEE_pT50To70_denom = new TH1D("chIsoEE_pT50To70_denom","",100,0.,50.);
  TH1D* phoIsoEE_pT50To70_denom = new TH1D("phoIsoEE_pT50To70_denom","",200,-50.,50.);
  TH1D* hOverEEE_pT50To70_denom = new TH1D("hOverEEE_pT50To70_denom","",100,0.,0.16);
  TH1D* sieieEE_pT50To70_denom = new TH1D("sieieEE_pT50To70_denom","",100,0.,0.1);
  TH1D* chIsoEE_pT50To70_num = new TH1D("chIsoEE_pT50To70_num","",100,0.,5.);
  TH1D* phoIsoEE_pT50To70_num = new TH1D("phoIsoEE_pT50To70_num","",650,-50.,2.);
  TH1D* hOverEEE_pT50To70_num = new TH1D("hOverEEE_pT50To70_num","",100,0.,0.05);
  TH1D* sieieEE_pT50To70_num = new TH1D("sieieEE_pT50To70_num","",100,0.,0.03);

  TH1D* chIsoEE1_pT50To70_denom = new TH1D("chIsoEE1_pT50To70_denom","",100,0.,50.);
  TH1D* phoIsoEE1_pT50To70_denom = new TH1D("phoIsoEE1_pT50To70_denom","",200,-50.,50.);
  TH1D* hOverEEE1_pT50To70_denom = new TH1D("hOverEEE1_pT50To70_denom","",100,0.,0.16);
  TH1D* sieieEE1_pT50To70_denom = new TH1D("sieieEE1_pT50To70_denom","",100,0.,0.1);
  TH1D* chIsoEE1_pT50To70_num = new TH1D("chIsoEE1_pT50To70_num","",100,0.,5.);
  TH1D* phoIsoEE1_pT50To70_num = new TH1D("phoIsoEE1_pT50To70_num","",650,-50.,2.);
  TH1D* hOverEEE1_pT50To70_num = new TH1D("hOverEEE1_pT50To70_num","",100,0.,0.05);
  TH1D* sieieEE1_pT50To70_num = new TH1D("sieieEE1_pT50To70_num","",100,0.,0.03);

  TH1D* chIsoEE2_pT50To70_denom = new TH1D("chIsoEE2_pT50To70_denom","",100,0.,50.);
  TH1D* phoIsoEE2_pT50To70_denom = new TH1D("phoIsoEE2_pT50To70_denom","",200,-50.,50.);
  TH1D* hOverEEE2_pT50To70_denom = new TH1D("hOverEEE2_pT50To70_denom","",100,0.,0.16);
  TH1D* sieieEE2_pT50To70_denom = new TH1D("sieieEE2_pT50To70_denom","",100,0.,0.1);
  TH1D* chIsoEE2_pT50To70_num = new TH1D("chIsoEE2_pT50To70_num","",100,0.,5.);
  TH1D* phoIsoEE2_pT50To70_num = new TH1D("phoIsoEE2_pT50To70_num","",650,-50.,2.);
  TH1D* hOverEEE2_pT50To70_num = new TH1D("hOverEEE2_pT50To70_num","",100,0.,0.05);
  TH1D* sieieEE2_pT50To70_num = new TH1D("sieieEE2_pT50To70_num","",100,0.,0.03);
  TH1D* npv = new TH1D("npv", "", 200, 0, 200);

  // loop over all entries
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if (jentry % 100000 == 0) std::cout << "Number of entries looped over: " << jentry << std::endl;

    const double etaCutEBmax = 1.4442;
    const double etaCutEEmin = 1.566;
    const double etaCutEE1max = 2.033;
    const double etaCutEEmax = 2.5;

    // reject beam halo
    //if (Event_beamHaloIDTight2015) continue;
    if (Photon_sigmaIphiIphi5x5 < 0.009) continue;
    if (Photon_r9_5x5 < 0.8) continue; // r9 cut to sync with resonant analysis

    // calculate nPV
    int numVtxAfterCut = 0;
    for(unsigned int i=0; i < VertexCollInfo_vx->size(); i++){
      int ndof = VertexCollInfo_ndof->at(i);
      double absZ = fabs(VertexCollInfo_vz->at(i));
      double d0 = VertexCollInfo_d0->at(i);

      if ( (ndof>=4) && (absZ<=24.) && (d0 <= 2.) ) {
        numVtxAfterCut++;
      }
    }
    npv->Fill(numVtxAfterCut);
    if(numVtxAfterCut< pvCutLow || numVtxAfterCut > pvCutHigh) continue;
    // if (!TriggerBit_HLT_PFHT900) continue;

    // evaluate jet trigger groupings
    // bool singleJetFired = TriggerBit_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p45_v3==1 || TriggerBit_HLT_AK8PFJet360_TrimMass30_v3==1 || TriggerBit_HLT_CaloJet500_NoJetID_v2==1 || TriggerBit_HLT_DiCaloJetAve140_v1==1 || TriggerBit_HLT_DiCaloJetAve200_v1==1 || TriggerBit_HLT_DiCaloJetAve260_v1==1 || TriggerBit_HLT_DiCaloJetAve320_v1==1 || TriggerBit_HLT_DiCaloJetAve400_v1==1 || TriggerBit_HLT_DiCaloJetAve40_v1==1 || TriggerBit_HLT_DiCaloJetAve500_v1==1 || TriggerBit_HLT_DiCaloJetAve60_v1==1 || TriggerBit_HLT_DiCaloJetAve80_v1==1 || TriggerBit_HLT_DiPFJetAve100_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve140_v2==1 || TriggerBit_HLT_DiPFJetAve160_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve200_v2==1 || TriggerBit_HLT_DiPFJetAve220_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve260_v2==1 || TriggerBit_HLT_DiPFJetAve300_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve30_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve320_v2==1 || TriggerBit_HLT_DiPFJetAve400_v2==1 || TriggerBit_HLT_DiPFJetAve40_v2==1 || TriggerBit_HLT_DiPFJetAve500_v2==1 || TriggerBit_HLT_DiPFJetAve60_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve60_v2==1 || TriggerBit_HLT_DiPFJetAve80_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve80_v2==1 || TriggerBit_HLT_PFJet140_v4==1 || TriggerBit_HLT_PFJet200_v4==1 || TriggerBit_HLT_PFJet260_v4==1 || TriggerBit_HLT_PFJet320_v4==1 || TriggerBit_HLT_PFJet400_v4==1 || TriggerBit_HLT_PFJet40_v4==1 || TriggerBit_HLT_PFJet450_v4==1 || TriggerBit_HLT_PFJet500_v4==1 || TriggerBit_HLT_PFJet60_v4==1 || TriggerBit_HLT_PFJet80_v4==1;

    // bool htFired = TriggerBit_HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45_v2==1 || TriggerBit_HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_v2==1 || TriggerBit_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v3==1 || TriggerBit_HLT_HT2000_v1==1 || TriggerBit_HLT_HT200_v1==1 || TriggerBit_HLT_HT2500_v1==1 || TriggerBit_HLT_HT275_v1==1 || TriggerBit_HLT_HT325_v1==1 || TriggerBit_HLT_HT425_v1==1 || TriggerBit_HLT_HT575_v1==1 || TriggerBit_HLT_L1_TripleJet_VBF_v4==1 || TriggerBit_HLT_PFHT200_v2==1 || TriggerBit_HLT_PFHT250_v2==1 || TriggerBit_HLT_PFHT300_v2==1 || TriggerBit_HLT_PFHT350_v3==1 || TriggerBit_HLT_PFHT400_SixJet30_BTagCSV0p55_2PFBTagCSV0p72_v3==1 || TriggerBit_HLT_PFHT400_SixJet30_v3==1 || TriggerBit_HLT_PFHT400_v2==1 || TriggerBit_HLT_PFHT450_SixJet40_PFBTagCSV0p72_v3==1 || TriggerBit_HLT_PFHT450_SixJet40_v3==1 || TriggerBit_HLT_PFHT475_v2==1 || TriggerBit_HLT_PFHT550_4JetPt50_v1==1 || TriggerBit_HLT_PFHT600_v3==1 || TriggerBit_HLT_PFHT650_4JetPt50_v1==1 || TriggerBit_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v3==1 || TriggerBit_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v3==1 || TriggerBit_HLT_PFHT650_v3==1 || TriggerBit_HLT_PFHT750_4JetPt50_v3==1 || TriggerBit_HLT_PFHT800_v2==1 || TriggerBit_HLT_QuadPFJet_VBF_v4==1;

    // bool PFJet80Fired = TriggerBit_HLT_PFJet80_v4 == 1;
    // bool PFJet400Fired = TriggerBit_HLT_PFJet400_v4 == 1;

    TLorentzVector photon;
    TLorentzVector leadingJet;
    TLorentzVector secondleadingJet;
    TLorentzVector thirdleadingJet;

    double photonLeadingJetDr = -1.;
    double photonSecondLeadingJetDr = -1.;
    double photonThirdLeadingJetDr = -1.;
    bool matched = false;

    if (iCut == 1){
      if (Jet_nJets >= 1){

        photon.SetPtEtaPhiM(Photon_pt,Photon_scEta,Photon_scPhi,0.);
        leadingJet.SetPtEtaPhiM(Jet_leadingJetPt,Jet_leadingJetEta,Jet_leadingJetPhi,Jet_leadingJetMass);
        // secondleadingJet.SetPtEtaPhiM(Jet_secondleadingJetPt,Jet_secondleadingJetEta,Jet_secondleadingJetPhi,Jet_secondleadingJetMass);
        // thirdleadingJet.SetPtEtaPhiM(Jet_thirdleadingJetPt,Jet_thirdleadingJetEta,Jet_thirdleadingJetPhi,Jet_thirdleadingJetMass);

        photonLeadingJetDr = photon.DeltaR(leadingJet);
        // photonSecondLeadingJetDr = photon.DeltaR(secondleadingJet);
        // photonThirdLeadingJetDr = photon.DeltaR(thirdleadingJet);

        double dRCut = 0.6;
        // these will all work because the jet 4 vectors are filled with dummy information, but I'll only use them if they are real jets
        bool matchedToLeadingJet = (photonLeadingJetDr < dRCut);
        // bool matchedToSecondLeadingJet = (photonSecondLeadingJetDr < dRCut);
        // bool matchedToThirdLeadingJet = (photonThirdLeadingJetDr < dRCut);

        matched = matchedToLeadingJet;

      }
    }
    else if (iCut == 2){
      if (Jet_nJets >= 2){

        photon.SetPtEtaPhiM(Photon_pt,Photon_scEta,Photon_scPhi,0.);
        leadingJet.SetPtEtaPhiM(Jet_leadingJetPt,Jet_leadingJetEta,Jet_leadingJetPhi,Jet_leadingJetMass);
        secondleadingJet.SetPtEtaPhiM(Jet_secondleadingJetPt,Jet_secondleadingJetEta,Jet_secondleadingJetPhi,Jet_secondleadingJetMass);
        // thirdleadingJet.SetPtEtaPhiM(Jet_thirdleadingJetPt,Jet_thirdleadingJetEta,Jet_thirdleadingJetPhi,Jet_thirdleadingJetMass);

        photonLeadingJetDr = photon.DeltaR(leadingJet);
        photonSecondLeadingJetDr = photon.DeltaR(secondleadingJet);
        // photonThirdLeadingJetDr = photon.DeltaR(thirdleadingJet);

        double dRCut = 0.6;
        // these will all work because the jet 4 vectors are filled with dummy information, but I'll only use them if they are real jets
	//        bool matchedToLeadingJet = (photonLeadingJetDr < dRCut);
        bool matchedToSecondLeadingJet = (photonSecondLeadingJetDr < dRCut);
        // bool matchedToThirdLeadingJet = (photonThirdLeadingJetDr < dRCut);

        matched = matchedToSecondLeadingJet;

      }
    }

    // jet matching cut
    if ( (iCut == 1 || iCut == 2) && !matched ) continue;
      
    // plot fake templates first
    // start with pt plots

    for (unsigned int i=0; i < chIsoSidebands.size(); i++){
      double sidebandLow = chIsoSidebands.at(i).first;
      double sidebandHigh = chIsoSidebands.at(i).second;
      bool inChIsoSideband = (sidebandLow < Photon_chargedHadIso03) && (Photon_chargedHadIso03 < sidebandHigh);
      bool isFakeTemplateObj = Photon_isNumeratorObjCand && inChIsoSideband;

      if (fabs(Photon_scEta) < etaCutEBmax && isFakeTemplateObj) phoPtEB_faketemplates.at(i)->Fill(Photon_pt);
      else if (etaCutEEmin < fabs(Photon_scEta) && fabs(Photon_scEta) < etaCutEEmax && isFakeTemplateObj) {
	phoPtEE_faketemplates.at(i)->Fill(Photon_pt);
	if (etaCutEEmin < fabs(Photon_scEta) && fabs(Photon_scEta) < etaCutEE1max) {
	  phoPtEE1_faketemplates.at(i)->Fill(Photon_pt);
	}
	else {
	  phoPtEE2_faketemplates.at(i)->Fill(Photon_pt);
	}

      }
    } 

    bool isNumeratorObj = Photon_isNumeratorObjCand && Photon_passChIso;
    // bool isDenomObj = Photon_isDenominatorObj && Photon_hadronicOverEm < 0.1;
    bool isDenomObj = Photon_isDenominatorObj;
    // if ( fabs(Photon_scEta) < 1.4442 )
    //   isDenomObj = Photon_isDenominatorObj && Photon_hadronicOverEm < 0.1;
    // else if ( 1.566 < fabs(Photon_scEta) && fabs(Photon_scEta) < 2.5 )
    //   isDenomObj = Photon_isDenominatorObj && Photon_hadronicOverEm < 0.1 && Photon_passCorPhoIso; //tighten phoIso in the denominator for the endcaps

    // fill debug plots
    if (fabs(Photon_scEta) < etaCutEBmax && Photon_pt > 50. && Photon_pt < 70.)  {
      if (Photon_passHighPtID){
        chIsoEB_pT50To70_num->Fill(Photon_chargedHadIso03);
        phoIsoEB_pT50To70_num->Fill(Photon_corPhotonIso03);
        hOverEEB_pT50To70_num->Fill(Photon_hadTowerOverEm);
        sieieEB_pT50To70_num->Fill(Photon_sigmaIetaIeta5x5);
      }
      else if (isDenomObj){
        chIsoEB_pT50To70_denom->Fill(Photon_chargedHadIso03);
        phoIsoEB_pT50To70_denom->Fill(Photon_corPhotonIso03);
        hOverEEB_pT50To70_denom->Fill(Photon_hadTowerOverEm);
        sieieEB_pT50To70_denom->Fill(Photon_sigmaIetaIeta5x5);
      }
    }
    else if (etaCutEEmin < fabs(Photon_scEta) && fabs(Photon_scEta) < etaCutEEmax && Photon_pt > 50. && Photon_pt < 70.)  {
      if (Photon_passHighPtID){
        chIsoEE_pT50To70_num->Fill(Photon_chargedHadIso03);
        phoIsoEE_pT50To70_num->Fill(Photon_corPhotonIso03);
        hOverEEE_pT50To70_num->Fill(Photon_hadTowerOverEm);
        sieieEE_pT50To70_num->Fill(Photon_sigmaIetaIeta5x5);
      }
      else if (isDenomObj){
        chIsoEE_pT50To70_denom->Fill(Photon_chargedHadIso03);
        phoIsoEE_pT50To70_denom->Fill(Photon_corPhotonIso03);
        hOverEEE_pT50To70_denom->Fill(Photon_hadTowerOverEm);
        sieieEE_pT50To70_denom->Fill(Photon_sigmaIetaIeta5x5);
      }
      if ( fabs(Photon_scEta) < etaCutEE1max ) {
	if (Photon_passHighPtID){
	  chIsoEE1_pT50To70_num->Fill(Photon_chargedHadIso03);
	  phoIsoEE1_pT50To70_num->Fill(Photon_corPhotonIso03);
	  hOverEEE1_pT50To70_num->Fill(Photon_hadTowerOverEm);
	  sieieEE1_pT50To70_num->Fill(Photon_sigmaIetaIeta5x5);
	}
	else if (isDenomObj){
	  chIsoEE1_pT50To70_denom->Fill(Photon_chargedHadIso03);
	  phoIsoEE1_pT50To70_denom->Fill(Photon_corPhotonIso03);
	  hOverEEE1_pT50To70_denom->Fill(Photon_hadTowerOverEm);
	  sieieEE1_pT50To70_denom->Fill(Photon_sigmaIetaIeta5x5);
	}
      }
      else {
	if (Photon_passHighPtID){
	  chIsoEE2_pT50To70_num->Fill(Photon_chargedHadIso03);
	  phoIsoEE2_pT50To70_num->Fill(Photon_corPhotonIso03);
	  hOverEEE2_pT50To70_num->Fill(Photon_hadTowerOverEm);
	  sieieEE2_pT50To70_num->Fill(Photon_sigmaIetaIeta5x5);
	}
	else if (isDenomObj){
	  chIsoEE2_pT50To70_denom->Fill(Photon_chargedHadIso03);
	  phoIsoEE2_pT50To70_denom->Fill(Photon_corPhotonIso03);
	  hOverEEE2_pT50To70_denom->Fill(Photon_hadTowerOverEm);
	  sieieEE2_pT50To70_denom->Fill(Photon_sigmaIetaIeta5x5);
	}
      }
    }

    // end debug plots


    // bool inChIsoSideband = (sidebandLow < Photon_chargedHadIso03) && (Photon_chargedHadIso03 < sidebandHigh);
    // bool isFakeTemplateObj = Photon_isNumeratorObjCand && inChIsoSideband;

    if (fabs(Photon_scEta) < etaCutEBmax) {
      phoPtEB.Fill( Photon_pt );
      if (isNumeratorObj){
      	phoPtEB_numerator.Fill(Photon_pt);
      	phoPtEB_numerator_varbin.Fill(Photon_pt);
        if (Jet_nJets >= 1) leadingjetPhoDrEB_numerator->Fill(photonLeadingJetDr);
        if (Jet_nJets >= 2) secondleadingjetPhoDrEB_numerator->Fill(photonSecondLeadingJetDr);
        if (Jet_nJets >= 3) thirdleadingjetPhoDrEB_numerator->Fill(photonThirdLeadingJetDr);
      }
      if (isDenomObj){
      	phoPtEB_denominator.Fill(Photon_pt);
      	phoPtEB_denominator_varbin.Fill(Photon_pt);
        if (Jet_nJets >= 1) leadingjetPhoDrEB_denominator->Fill(photonLeadingJetDr);
        if (Jet_nJets >= 2) secondleadingjetPhoDrEB_denominator->Fill(photonSecondLeadingJetDr);
        if (Jet_nJets >= 3) thirdleadingjetPhoDrEB_denominator->Fill(photonThirdLeadingJetDr);
      }
      // if (isFakeTemplateObj){
      // 	phoPtEB_faketemplate.Fill(Photon_pt);
      // 	phoPtEB_faketemplate_varbin.Fill(Photon_pt);
      // }
    }

    else if (etaCutEEmin < fabs(Photon_scEta) && fabs(Photon_scEta) < etaCutEEmax) {
      phoPtEE.Fill( Photon_pt );
      if (isNumeratorObj){
      	phoPtEE_numerator.Fill(Photon_pt);
      	phoPtEE_numerator_varbin.Fill(Photon_pt);
        if (Jet_nJets >= 1) leadingjetPhoDrEE_numerator->Fill(photonLeadingJetDr);
        if (Jet_nJets >= 2) secondleadingjetPhoDrEE_numerator->Fill(photonSecondLeadingJetDr);
        if (Jet_nJets >= 3) thirdleadingjetPhoDrEE_numerator->Fill(photonThirdLeadingJetDr);
      }
      if (isDenomObj){
      	phoPtEE_denominator.Fill(Photon_pt);
      	phoPtEE_denominator_varbin.Fill(Photon_pt);
        if (Jet_nJets >= 1) leadingjetPhoDrEE_denominator->Fill(photonLeadingJetDr);
        if (Jet_nJets >= 2) secondleadingjetPhoDrEE_denominator->Fill(photonSecondLeadingJetDr);
        if (Jet_nJets >= 3) thirdleadingjetPhoDrEE_denominator->Fill(photonThirdLeadingJetDr);
      }
      if ( fabs(Photon_scEta) < etaCutEE1max ) {
	phoPtEE1.Fill( Photon_pt );
	if (isNumeratorObj){
	  phoPtEE1_numerator.Fill(Photon_pt);
	  phoPtEE1_numerator_varbin.Fill(Photon_pt);
	  if (Jet_nJets >= 1) leadingjetPhoDrEE1_numerator->Fill(photonLeadingJetDr);
	  if (Jet_nJets >= 2) secondleadingjetPhoDrEE1_numerator->Fill(photonSecondLeadingJetDr);
	  if (Jet_nJets >= 3) thirdleadingjetPhoDrEE1_numerator->Fill(photonThirdLeadingJetDr);
	}
	if (isDenomObj){
	  phoPtEE1_denominator.Fill(Photon_pt);
	  phoPtEE1_denominator_varbin.Fill(Photon_pt);
	  if (Jet_nJets >= 1) leadingjetPhoDrEE1_denominator->Fill(photonLeadingJetDr);
	  if (Jet_nJets >= 2) secondleadingjetPhoDrEE1_denominator->Fill(photonSecondLeadingJetDr);
	  if (Jet_nJets >= 3) thirdleadingjetPhoDrEE1_denominator->Fill(photonThirdLeadingJetDr);
	}
      }
      else {
	phoPtEE2.Fill( Photon_pt );
	if (isNumeratorObj){
	  phoPtEE2_numerator.Fill(Photon_pt);
	  phoPtEE2_numerator_varbin.Fill(Photon_pt);
	  if (Jet_nJets >= 1) leadingjetPhoDrEE2_numerator->Fill(photonLeadingJetDr);
	  if (Jet_nJets >= 2) secondleadingjetPhoDrEE2_numerator->Fill(photonSecondLeadingJetDr);
	  if (Jet_nJets >= 3) thirdleadingjetPhoDrEE2_numerator->Fill(photonThirdLeadingJetDr);
	}
	if (isDenomObj){
	  phoPtEE2_denominator.Fill(Photon_pt);
	  phoPtEE2_denominator_varbin.Fill(Photon_pt);
	  if (Jet_nJets >= 1) leadingjetPhoDrEE2_denominator->Fill(photonLeadingJetDr);
	  if (Jet_nJets >= 2) secondleadingjetPhoDrEE2_denominator->Fill(photonSecondLeadingJetDr);
	  if (Jet_nJets >= 3) thirdleadingjetPhoDrEE2_denominator->Fill(photonThirdLeadingJetDr);
	}

      }
      // if (isFakeTemplateObj){
      // 	phoPtEE_faketemplate.Fill(Photon_pt);
      // 	phoPtEE_faketemplate_varbin.Fill(Photon_pt);
      // }
    }


    //loop over pt bin low edges (also equal to or half of hist vector entry numbers) to fill numerator and fake templates
    for (int i = 0; i < nBins-1; i++){
      double binLowEdge = ptBinArray[i];
      double binUpperEdge = ptBinArray[i+1];

      // fill fake templates
      for (unsigned int j=0; j < chIsoSidebands.size(); j++){
        double sidebandLow = chIsoSidebands.at(j).first;
        double sidebandHigh = chIsoSidebands.at(j).second;
        bool inChIsoSideband = (sidebandLow < Photon_chargedHadIso03) && (Photon_chargedHadIso03 < sidebandHigh);
        bool isFakeTemplateObj = Photon_isNumeratorObjCand && inChIsoSideband;

        if ( (binLowEdge < Photon_pt) && (Photon_pt < binUpperEdge) && isFakeTemplateObj ){
          if (fabs(Photon_scEta) < etaCutEBmax){
            sIeIeFakeTemplatesEB.at(i).at(j)->Fill( Photon_sigmaIetaIeta5x5 );
            if (sidebandLow==9.){
              if (Jet_nJets >= 1) leadingjetPhoDrEB_faketemplate->Fill(photonLeadingJetDr);
              if (Jet_nJets >= 2) secondleadingjetPhoDrEB_faketemplate->Fill(photonSecondLeadingJetDr);
              if (Jet_nJets >= 3) thirdleadingjetPhoDrEB_faketemplate->Fill(photonThirdLeadingJetDr);
            }
          }
          else if ( (etaCutEEmin < fabs(Photon_scEta)) && (fabs(Photon_scEta) < etaCutEEmax) ){
            sIeIeFakeTemplatesEE.at(i).at(j)->Fill( Photon_sigmaIetaIeta5x5 );
            if (sidebandLow==9.){
              if (Jet_nJets >= 1) leadingjetPhoDrEE_faketemplate->Fill(photonLeadingJetDr);
              if (Jet_nJets >= 2) secondleadingjetPhoDrEE_faketemplate->Fill(photonSecondLeadingJetDr);
              if (Jet_nJets >= 3) thirdleadingjetPhoDrEE_faketemplate->Fill(photonThirdLeadingJetDr);
            }           
	    if (fabs(Photon_scEta) < etaCutEE1max ) {
	      sIeIeFakeTemplatesEE1.at(i).at(j)->Fill( Photon_sigmaIetaIeta5x5 );
	      if (sidebandLow==9.){
		if (Jet_nJets >= 1) leadingjetPhoDrEE1_faketemplate->Fill(photonLeadingJetDr);
		if (Jet_nJets >= 2) secondleadingjetPhoDrEE1_faketemplate->Fill(photonSecondLeadingJetDr);
		if (Jet_nJets >= 3) thirdleadingjetPhoDrEE1_faketemplate->Fill(photonThirdLeadingJetDr);
	      }
	    }
	    else {
	      sIeIeFakeTemplatesEE2.at(i).at(j)->Fill( Photon_sigmaIetaIeta5x5 );
	      if (sidebandLow==9.){
		if (Jet_nJets >= 1) leadingjetPhoDrEE2_faketemplate->Fill(photonLeadingJetDr);
		if (Jet_nJets >= 2) secondleadingjetPhoDrEE2_faketemplate->Fill(photonSecondLeadingJetDr);
		if (Jet_nJets >= 3) thirdleadingjetPhoDrEE2_faketemplate->Fill(photonThirdLeadingJetDr);
	      }

	    }
          }
        } // end if statement on fake template obj and pT bin
      } // end loop over sidebands to fill fake templates


      // if ( (binLowEdge < Photon_pt) && (Photon_pt < binUpperEdge) && isFakeTemplateObj ){

      // 	if (fabs(Photon_scEta) < 1.4442) sIeIeFakeTemplateEB.at(i)->Fill( Photon_sigmaIetaIeta5x5 );
      // 	else if ( (1.566 < fabs(Photon_scEta)) && (fabs(Photon_scEta) < 2.5) ) sIeIeFakeTemplateEE.at(i)->Fill( Photon_sigmaIetaIeta5x5 );

      // }

      // fill numerator histograms
      if ( (binLowEdge < Photon_pt) && (Photon_pt < binUpperEdge) && isNumeratorObj ){
	if (fabs(Photon_scEta) < etaCutEBmax) sIeIeNumeratorEB.at(i)->Fill( Photon_sigmaIetaIeta5x5 );
	else if ( (etaCutEEmin < fabs(Photon_scEta)) && (fabs(Photon_scEta) < etaCutEEmax) ) {
	  sIeIeNumeratorEE.at(i)->Fill( Photon_sigmaIetaIeta5x5 );
	  if (fabs(Photon_scEta) < etaCutEE1max) {
	    sIeIeNumeratorEE1.at(i)->Fill( Photon_sigmaIetaIeta5x5 );
	  }
	  else {
	    sIeIeNumeratorEE2.at(i)->Fill( Photon_sigmaIetaIeta5x5 );
	  }
	}
      }

      // fill denominator histograms
      if ( (binLowEdge < Photon_pt) && (Photon_pt < binUpperEdge) && isDenomObj ){
        if (fabs(Photon_scEta) < etaCutEBmax) denomPtEB.at(i)->Fill( Photon_pt );
        else if ( (etaCutEEmin < fabs(Photon_scEta)) && (fabs(Photon_scEta) < etaCutEEmax) ) {
	  denomPtEE.at(i)->Fill( Photon_pt );
	  if ( fabs(Photon_scEta) < etaCutEE1max ) {
	    denomPtEE1.at(i)->Fill( Photon_pt );
	  }
	  else {
	    denomPtEE2.at(i)->Fill( Photon_pt );
	  }
	}
      }

    } // end loop over pt bins
  } // end loop over entries

  // write histograms out to root files
  
  // TString outName = TString::Format("diphoton_fakeRate_JetHT_Run2015_16Dec2015-v1_MINIAOD_histograms_chIsoSB%iTo%i.root",(int)sidebandLow,(int)sidebandHigh);
  // TFile file_out("diphoton_fakeRate_JetHT_Run2015_16Dec2015-v1_MINIAOD_histograms_matchedToLeadingJetDr0p6.root","RECREATE");
  TString jetMatch = "";
  if (iCut == 1) jetMatch = "_matchedtoLeadingJet";
  else if (iCut == 2) jetMatch = "_matchedtoSubleadingJet";
  TString pv = Form("_nPV%i-%i", pvCutLow, pvCutHigh);
  TString outName = TString::Format("%s_fakerate_%s%s%s_newDenomDef.root", dataset.Data(), era.Data(), jetMatch.Data(), pv.Data());
  TFile file_out(outName,"RECREATE");
  
  // sigmaIetaIetaEB->Write();
  // sigmaIetaIetaEE->Write();
  file_out.cd();
  phoPtEB.Write();
  phoPtEE.Write();
  phoPtEE1.Write();
  phoPtEE2.Write();
  phoPtEB_numerator.Write();
  phoPtEE_numerator.Write();
  phoPtEE1_numerator.Write();
  phoPtEE2_numerator.Write();
  phoPtEB_denominator.Write();
  phoPtEE_denominator.Write();
  phoPtEE1_denominator.Write();
  phoPtEE2_denominator.Write();
  // phoPtEB_faketemplate.Write();
  // phoPtEE_faketemplate.Write();
  phoPtEB_numerator_varbin.Write();
  phoPtEE_numerator_varbin.Write();
  phoPtEE1_numerator_varbin.Write();
  phoPtEE2_numerator_varbin.Write();
  phoPtEB_denominator_varbin.Write();
  phoPtEE_denominator_varbin.Write();
  phoPtEE1_denominator_varbin.Write();
  phoPtEE2_denominator_varbin.Write();
  // phoPtEB_faketemplate_varbin.Write();
  // phoPtEE_faketemplate_varbin.Write();
  for (unsigned int i=0; i < phoPtEB_faketemplates.size(); i++){
    phoPtEB_faketemplates.at(i)->Write();
    phoPtEE_faketemplates.at(i)->Write();
    phoPtEE1_faketemplates.at(i)->Write();
    phoPtEE2_faketemplates.at(i)->Write();
  }

  std::vector<std::vector<TH1D*>> hists_to_write = {sIeIeNumeratorEB, sIeIeNumeratorEE, sIeIeNumeratorEE1, sIeIeNumeratorEE2, // numerator
						    denomPtEB, denomPtEE, denomPtEE1, denomPtEE2}; // denominator

  for(auto& hists : hists_to_write) {
    for (auto& it : hists) {
      std::cout << it->GetName() << "\t integral: " << it->Integral() << std::endl;
      it->Write();
    }
  }

  // scale fake template histograms to unity and write to file
  // for (std::vector<TH1D*>::iterator it = sIeIeFakeTemplateEB.begin() ; it != sIeIeFakeTemplateEB.end(); ++it) {
  //   std::cout << (*it)->GetName() << "\t integral: " << (*it)->Integral() << std::endl;
  //   (*it)->Scale(1.0/(*it)->Integral());
  //   (*it)->Write();
  // }
  // for (std::vector<TH1D*>::iterator it = sIeIeFakeTemplateEE.begin() ; it != sIeIeFakeTemplateEE.end(); ++it) {
  //   std::cout << (*it)->GetName() << "\t integral: " << (*it)->Integral() << std::endl;
  //   (*it)->Scale(1.0/(*it)->Integral());
  //   (*it)->Write();
  // }
  for (int i = 0; i < nBins-1; i++){
    for (unsigned int j=0; j < chIsoSidebands.size(); j++){
      TH1D* tempHistEB = sIeIeFakeTemplatesEB.at(i).at(j);
      TH1D* tempHistEE = sIeIeFakeTemplatesEE.at(i).at(j);
      TH1D* tempHistEE1 = sIeIeFakeTemplatesEE1.at(i).at(j);
      TH1D* tempHistEE2 = sIeIeFakeTemplatesEE2.at(i).at(j);

      std::cout << tempHistEB->GetName() << "\t integral: " << tempHistEB->Integral() << std::endl;
      tempHistEB->Scale(1./tempHistEB->Integral());
      tempHistEB->Write();

      std::cout << tempHistEE->GetName() << "\t integral: " << tempHistEE->Integral() << std::endl;
      tempHistEE->Scale(1./tempHistEE->Integral());
      tempHistEE->Write();

      std::cout << tempHistEE1->GetName() << "\t integral: " << tempHistEE1->Integral() << std::endl;
      tempHistEE1->Scale(1./tempHistEE1->Integral());
      tempHistEE1->Write();

      std::cout << tempHistEE2->GetName() << "\t integral: " << tempHistEE2->Integral() << std::endl;
      tempHistEE2->Scale(1./tempHistEE2->Integral());
      tempHistEE2->Write();
    }
  }
  chIsoEB_pT50To70_num->Write();
  chIsoEB_pT50To70_denom->Write();
  phoIsoEB_pT50To70_num->Write();
  phoIsoEB_pT50To70_denom->Write();
  hOverEEB_pT50To70_num->Write();
  hOverEEB_pT50To70_denom->Write();
  sieieEB_pT50To70_num->Write();
  sieieEB_pT50To70_denom->Write();
  chIsoEE_pT50To70_num->Write();
  chIsoEE_pT50To70_denom->Write();
  phoIsoEE_pT50To70_num->Write();
  phoIsoEE_pT50To70_denom->Write();
  hOverEEE_pT50To70_num->Write();
  hOverEEE1_pT50To70_num->Write();
  hOverEEE2_pT50To70_num->Write();
  hOverEEE_pT50To70_denom->Write();
  hOverEEE1_pT50To70_denom->Write();
  hOverEEE2_pT50To70_denom->Write();
  sieieEE_pT50To70_num->Write();
  sieieEE1_pT50To70_num->Write();
  sieieEE2_pT50To70_num->Write();
  sieieEE_pT50To70_denom->Write();
  sieieEE1_pT50To70_denom->Write();
  sieieEE2_pT50To70_denom->Write();
  leadingjetPhoDrEB_numerator->Write();
  leadingjetPhoDrEE_numerator->Write();
  leadingjetPhoDrEE1_numerator->Write();
  leadingjetPhoDrEE2_numerator->Write();
  leadingjetPhoDrEB_denominator->Write();
  leadingjetPhoDrEE_denominator->Write();
  leadingjetPhoDrEE1_denominator->Write();
  leadingjetPhoDrEE2_denominator->Write();
  leadingjetPhoDrEB_faketemplate->Write();
  leadingjetPhoDrEE_faketemplate->Write();
  leadingjetPhoDrEE1_faketemplate->Write();
  leadingjetPhoDrEE2_faketemplate->Write();
  secondleadingjetPhoDrEB_numerator->Write();
  secondleadingjetPhoDrEE_numerator->Write();
  secondleadingjetPhoDrEE1_numerator->Write();
  secondleadingjetPhoDrEE2_numerator->Write();
  secondleadingjetPhoDrEB_denominator->Write();
  secondleadingjetPhoDrEE_denominator->Write();
  secondleadingjetPhoDrEE1_denominator->Write();
  secondleadingjetPhoDrEE2_denominator->Write();
  secondleadingjetPhoDrEB_faketemplate->Write();
  secondleadingjetPhoDrEE_faketemplate->Write();
  secondleadingjetPhoDrEE1_faketemplate->Write();
  secondleadingjetPhoDrEE2_faketemplate->Write();
  thirdleadingjetPhoDrEB_numerator->Write();
  thirdleadingjetPhoDrEE_numerator->Write();
  thirdleadingjetPhoDrEE1_numerator->Write();
  thirdleadingjetPhoDrEE2_numerator->Write();
  thirdleadingjetPhoDrEB_denominator->Write();
  thirdleadingjetPhoDrEE_denominator->Write();
  thirdleadingjetPhoDrEE1_denominator->Write();
  thirdleadingjetPhoDrEE2_denominator->Write();
  thirdleadingjetPhoDrEB_faketemplate->Write();
  thirdleadingjetPhoDrEE_faketemplate->Write();
  thirdleadingjetPhoDrEE1_faketemplate->Write();
  thirdleadingjetPhoDrEE2_faketemplate->Write();
  npv->Write();

  file_out.ls();
  file_out.Close();
   
} // end Loop()
