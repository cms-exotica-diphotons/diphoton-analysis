#ifndef ISO_CORRECTIONS_INC
#define ISO_CORRECTIONS_INC

#include "TFile.h"
#include "TVectorD.h"
#include "TH1.h"
#include "TRandom.h"

namespace ExoDiPhotons{

  // These are the additional parameters for the data/mc correction to the photon isolation.  They were derived from a root file from the resonant analysis, and it was easier to just hard code the parameters
  std::vector<float> eta_centers_ = { 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1, 1.125, 1.25, 1.375, 1.625, 1.75, 1.875, 2, 2.125, 2.25, 2.375};
  std::vector<float> rho_centers_eb_ = { 3, 4.5, 6, 7.5, 9, 10.5, 12, 13.5, 15, 16.5, 18, 19.5, 21, 22.5, 24, 25.5, 27, 28.5, 30, 31.5 };
  std::vector<float> rho_centers_ee_ = { 4.25, 6.375, 8.5, 10.625, 12.75, 14.875, 17, 19.125, 21.25, 23.375, 25.5, 27.625, 29.75, 31.875 };
  std::vector<float> extra_multiplicity_ = { 0.065848, 0.0525788, 0.0618049, 0.0527343, 0.0380554, 0.059265, 0.0961537, 0.0669666, 0.0788063, 0.0896756, 0.276756, 0.437338, 0.552818, 0.693268, 0.74009, 0.735159, 0.67401, 0.608931 };
  std::vector<float> extra_multiplicity_slope_ = { 0.0566472, 0.0570162, 0.0554019, 0.0523072, 0.0497512, 0.0470667, 0.0438137, 0.0458391, 0.0439682, 0.0422244, -0.000396314, -0.00209133, -0.00538064, -0.0101258, -0.0131767, -0.0162798, -0.0179164, -0.0176048 };
  std::vector<int> multiplicity_offset_ = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0 };

  int n_rho_centers_;
  std::vector<TH1*> histograms_;

  int index(int ieta, int irho, int n_rho_centers_) {
    return ieta*n_rho_centers_ + irho;
  }    
  int findIndex(float val, std::vector<float> & vec) {
      
    if( val < vec.front() ) return 0;
    if( val >= vec.back() ) return vec.size()-1;
    int lb = std::distance(vec.begin(), std::lower_bound(vec.begin(),vec.end(), val) );
    return ( fabs(vec[lb] - val) < fabs(vec[lb-1]-val) ? lb : lb -1) ;  
  }
  void prepIsoCorrectionHistos(){
    // initiate everything needed for the data/mc phoIso correction
    // code is mostly lifted from https://github.com/cms-analysis/flashgg/blob/master/Taggers/src/IsolationCorrection.C
    auto * fin = TFile::Open("../data/pho_iso_corrections_hybrid_moriond17_v3.root"); // filename hardcoded for now
    // fin->ls();

    n_rho_centers_ = std::max(rho_centers_eb_.size(),rho_centers_ee_.size());

    histograms_.resize(n_rho_centers_*eta_centers_.size(),0);

    for(size_t ieta=0; ieta<eta_centers_.size(); ++ieta) {
      auto & eta = eta_centers_[ieta];
      // std::cerr << eta << std::endl;
      auto & rho_centers = ( eta<1.5 ? rho_centers_eb_ : rho_centers_ee_ );
            
      for(size_t irho=0; irho<rho_centers.size(); ++irho) {
        auto ibin = ExoDiPhotons::index(ieta,irho,n_rho_centers_);
        auto & rho = rho_centers[irho];

        /// std::cerr << rho << std::endl;
        TString name = TString::Format("hist_%1.3f_%1.2f",eta,rho);
        name.ReplaceAll(".","p");
        // std::cerr << name << std::endl;
        auto hist = dynamic_cast<TH1*>(fin->Get(name)->Clone());
        // std::cerr << name << " " << hist << std::endl;
        hist->SetDirectory(0);
                
        histograms_[ibin] = hist;
      }
    } 
          
    fin->Close();

  } // end prepIsoCorrectionHistos function


}

#endif