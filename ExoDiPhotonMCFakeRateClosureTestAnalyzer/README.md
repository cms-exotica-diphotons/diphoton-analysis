# EXO DiPhoton Analysis Code

## Instructions for MC Fake Rate Closure Test Analyzer

export SCRAM_ARCH=slc6_amd64_gcc493 (bash)  
setenv SCRAM_ARCH slc6_amd64_gcc493 (tcsh)

cmsrel CMSSW_7_6_3_patch2  
cd CMSSW_7_6_3_patch2/src  
cmsenv  
git clone git@github.com:cms-exotica-diphotons/diphoton-analysis  
cd diphoton-analysis   
cd ExoDiPhotonMCFakeRateClosureTestAnalyzer  
scram b -j 8  