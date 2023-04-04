TH1F* Ratio(TH1F* hSyst, TH1F* hNom){
  TH1F* hRatio = dynamic_cast<TH1F* >( hSyst->Clone("hRatio") );
  for(int i=0; i<=hRatio->GetNbinsX()+1; i++){

    float numerator = hSyst->GetBinContent(i);
    float denominator = hNom->GetBinContent(i);
    hRatio->SetBinContent(i, denominator!=0 ? numerator/denominator : 0);
  }

  return hRatio;
}

TH1F* getHist(const char* name)
{
  TFile* rootfile = new TFile("Test2017_negInt-0_lT-4000.root");
  assert(rootfile);
  rootfile->cd();
  TH1F* h=dynamic_cast<TH1F*>( gROOT->FindObject(name) );
  if(!h)
    std::cout << "Cannot find object " << name << std::endl;
  assert(h);
  return h;
}

void systematicsRatio(){
  TCanvas *c=new TCanvas("c","c");
  c->Divide(3,2);

  // TH1F* h1=getHist("BE17__ADDNegInt1LT4000__energyScaleStat__minus"); //same as nominal
  // TH1F* h1=getHist("BE17__ADDNegInt1LT4000__energyScaleStat__plus"); //same as nominal

  // TH1F* h1=getHist("BE17__ADDNegInt1LT4000__pileup__plus");
  // TH1F* h2=getHist("BE17__ADDNegInt1LT4000");
  // TH1F* h3=getHist("BE17__ADDNegInt1LT4500__pileup__plus");
  // TH1F* h4=getHist("BE17__ADDNegInt1LT4500");

  // TH1F* h1=getHist("BE17__ADDNegInt1LT4000__energyScaleSyst__plus");
  // TH1F* h2=getHist("BE17__ADDNegInt1LT4000");
  // TH1F* h3=getHist("BE17__ADDNegInt1LT4500__energyScaleSyst__plus");
  // TH1F* h4=getHist("BE17__ADDNegInt1LT4500");

  TH1F* h1=getHist("BE17__ADDNegInt1LT4000__eff__plus");
  TH1F* h2=getHist("BE17__ADDNegInt1LT4000");
  TH1F* h3=getHist("BE17__ADDNegInt1LT4500__eff__plus");
  TH1F* h4=getHist("BE17__ADDNegInt1LT4500");

  TH1F* hR1 = Ratio(h1, h2);
  TH1F* hR2 = Ratio(h3, h4);

  c->cd(1);
  hR1->Fit("pol1");
  hR1->Draw();

  c->cd(2);
  h1->Draw();

  c->cd(3);
  h2->Draw();

  c->cd(4);
  hR2->Fit("pol1");
  hR2->Draw();

  c->cd(5);
  h3->Draw();

  c->cd(6);
  h4->Draw();


}
