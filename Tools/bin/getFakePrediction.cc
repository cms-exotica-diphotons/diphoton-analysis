#include "diphoton-analysis/Tools/interface/fakePrediction.C"
#include "diphoton-analysis/Tools/interface/sampleList.hh"

#include <iostream>

#include "TChain.h"

int main(int argc, char *argv[])
{
  std::string source, dataset;

  int year = 0;
  if(argc!=3) {
    std::cout << "Syntax: getFakeRatePrediction.exe [data_2016/data_2017/data_2018/mc] [average/doublemuon/jetht]" << std::endl;
    return -1;
  }
  else {
    source = argv[1];
    //    if(source!="mc" and source!="data") {
    if(source!="mc" and source!="data_2016" and source!="data_2017" and source!="data_2018") {
      std::cout << "Only 'data_2016', 'data_2017', 'data_2018' and 'mc' are allowed input parameters. " << std::endl;
      return -1;
    }
    dataset = argv[2];
    if(dataset!= "average" && dataset!="jetht" && dataset!="doublemuon") {
      std::cout << "Only 'average', 'jetht' and 'doublemuon' are allowed datasets." << std::endl;
    }
  }
  if(source=="data_2016") year = 2016;
  if(source=="data_2017") year = 2017;
  if(source=="data_2018") year = 2018;

  init();
  TChain *ch = chains[source];
  fakePrediction f(ch);

  if(source=="mc") f.setIsMC(true);
  else f.setIsMC(false);

  f.Loop(year, dataset);

  return 0;
}
