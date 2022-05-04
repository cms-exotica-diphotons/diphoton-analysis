#include "diphoton-analysis/Tools/interface/fakePrediction.C"
#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include <iostream>

#include "TChain.h"

template <class T>
bool isAllowedParameter(const T& parameter, const std::vector<T>& allowedParameters)
{
  for(const auto& allowedParameter : allowedParameters) {
    if(parameter == allowedParameter) {
      return true;
    }
  }

  return false;
}

template <class T>
void printAllowed(const std::vector<T>& allowedParameters)
{
  for(const auto& allowedParameter : allowedParameters) {
    std::cout << allowedParameter << "\n";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  std::string source, year, dataset;

  std::vector<std::string> allowedSources({"gg", "data"});
  std::vector<std::string> allowedYears({"2016", "2017", "2018"});
  std::vector<std::string> allowedDatasets({"average", "jetht", "doublemuon"});
  std::map<std::string, std::vector<std::string>> allowedParameters;
  allowedParameters["sources"] = allowedSources;
  allowedParameters["years"] = allowedYears;
  allowedParameters["datasets"] = allowedDatasets;

  if(argc != static_cast<int>(allowedParameters.size()+1)) {
    std::cout << "Syntax: getFakeRatePrediction.exe [gg/data] [2016/2017/2018] [average/doublemuon/jetht]" << std::endl;
    return -1;
  }
  else {
    source = argv[1];
    if(!isAllowedParameter(source, allowedSources)) {
      std::cout << "Allowed sources: " << std::endl;
      printAllowed(allowedSources);
      return -1;
    }
    year = argv[2];
    if(!isAllowedParameter(year, allowedYears)) {
      std::cout << "Allowed years:" << std::endl;
      printAllowed(allowedYears);
      return -1;
    }
    dataset = argv[3];
    if(!isAllowedParameter(dataset, allowedDatasets)) {
      std::cout << "Allowed datasets:" << std::endl;
      printAllowed(allowedDatasets);
      return -1;
    }
  }

  std::string chainType(source);
  chainType += "_" + year;

  init();
  TChain *ch = chains[chainType];
  fakePrediction f(ch);

  if(source=="gg") f.setIsMC(true);
  else f.setIsMC(false);

  f.Loop(atoi(year.c_str()), dataset, source);

  return 0;
}

