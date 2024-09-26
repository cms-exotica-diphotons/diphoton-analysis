# EXO DiPhoton Analysis Code

# Tools

Resubmit CRAB2 jobs in direcotry "dir" by doing: ./resubmitCrabJobs.sh dir


## Commands

Go to CMSSW_BASE/src/diphoton-analysis/Tools

### `python commands.py`
To list available commands

Go to CMSSW_BASE/src to run the commands

```
cd $CMSSW_BASE/src
cmsenv
scram b -j 16
mkdir plots # important step
```

### `basicplots.exe`
makes plots without signal

### `getFakePrediction.exe`
makes the data-driven fake histograms

### `makeDatacards.exe`
makes the datacards for Combine
