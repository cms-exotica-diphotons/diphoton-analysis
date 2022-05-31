# EXO DiPhoton Analysis Code

## To build. Note that the recipe is different for 2016/2017 and 2018 data/MC.

```
# select cmssw environment
## 2015 (bash syntax)
export SCRAM_ARCH=slc6_amd64_gcc493  
export CMSSW_VERSION=CMSSW_7_6_4
## 2016 + 2017 (tcsh syntax)
setenv SCRAM_ARCH slc6_amd64_gcc630
setenv CMSSW_VERSION CMSSW_9_4_13
## 2018 (bash syntax)
export SCRAM_ARCH=slc6_amd64_gcc700
export CMSSW_VERSION=CMSSW_10_2_16

# Use slc7 instead of slc6 since lpc and lxplus clusters no longer use scientific linux 6
export SCRAM_ARCH=slc7_amd64_gcc700
export CMSSW_VERSION=CMSSW_10_2_26

# setup cmssw release
cmsrel $CMSSW_VERSION  
cd $CMSSW_BASE/src  
cmsenv  

# EGM recipe from https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaMiniAODV2
# only for 2018 data/MC
# reverts the changes to EgammaPostRecoTools needed to run in 10_6_X
git cms-merge-topic -u christopheralanwest:revert-41-EgammaPostRecoTools_dev
#git cms-merge-topic cms-egamma:EgammaPostRecoTools #just adds in an extra file to have a setup function to make things easier
git cms-merge-topic cms-egamma:PhotonIDValueMapSpeedup1029 #optional but speeds up the photon ID value module so things fun faster
#now to add the scale and smearing for 2018 (eventually this will not be necessary in later releases but is harmless to do regardless)
git cms-addpkg EgammaAnalysis/ElectronTools
rm EgammaAnalysis/ElectronTools/data -rf
git clone git@github.com:cms-data/EgammaAnalysis-ElectronTools.git EgammaAnalysis/ElectronTools/data

# only for 2016/2017 data/MC
# reverts the changes to EgammaPostRecoTools needed to run in 10_6_X
git cms-merge-topic -u christopheralanwest:revert-41-EgammaPostRecoTools_dev
#git cms-merge-topic cms-egamma:EgammaPostRecoTools #just adds in an extra file to have a setup function to make things easier

# clone repository
git clone git@github.com:cms-exotica-diphotons/diphoton-analysis  

# compile code
cd diphoton-analysis  
scram b -j 8
```

## For Pull Requests

Make sure to get the latest changes from the master branch and work from there.
```bash

 git clone git@github.com:uzzielperez/diphoton-analysis.git
 cd diphoton-analysis
 git remote add upstream git@github.com:cms-exotica-diphotons/diphoton-analysis.git
 git checkout master
 git pull upstream master # pull latest from master

 # check diff
 git diff -U0 --color remotes/upstream/master

 # to reset
 git reset --hard upstream/master

 git push origin master

 ```

## To run full analysis
### k-factor analysis
- Generate all needed ntuples using `ExoDiPhotonAnalyzer/test/submit_crab_cfg.py` (for the main diphoton ntuples) and `ExoDiPhotonFakeRateAnalyzer/test/submit_crab_cfg.py` (for the fake rate ntuples)
- Run MCFM k-factor jobs and k-factor uncertainty jobs
- Run `plot_sherpa.exe` to create sherpa histograms for k-factor calculation; copy outputs to `diphoton-analysis/Tools/data`
- Modify paths in plotKfactor.cc to refer to new Sherpa files and MCFM outputs. Then create k-factor root files with `plotKfactor.exe`

### Real and fake template analysis
```
cd ${CMSSW_BASE}/src/diphoton-analysis/FakeRateAnalysis
python bin/create_templates.py | bash
```
- Copy the output files to your prefered location and modify "basefilename" in `rooFitClosureTest.C` and `rooFitFakeRateProducer.C`
- Run `python bin/fit_histos.py | bash`

### Run limits
```
cd ${CMSSW_BASE}/src/
git clone -b v8.0.1-ADD https://github.com/christopheralanwest/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
scram b -j 6
cd HiggsAnalysis/CombinedLimit
source scripts/run_all.sh
```
 
### Make plots with output from limits
```
cd ${CMSSW_BASE}/src/diphoton-analysis/Tools
plot_blinded.exe
limit.exe
```
###
