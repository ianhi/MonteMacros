#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TChain.h>
#include <TProfile.h>
#include <TStopwatch.h>
#include <TCut.h>
#include <cstdlib>
#include <cmath>
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLine.h"
#include <stdlib.h>
#include <string>
#include <sstream>
#include <TH1D.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>
#include <cmath>
void testOpen(){
  std::string prefix;
  prefix="med1";
  std::string infile;
  infile = "TEXTFILES/"+prefix+"_fileList.txt";
  
  std::ifstream fi(infile.c_str());
  std::string line;
  int number_of_lines=0;
  while (std::getline(fi, line)) ++number_of_lines;
  cout<<"Number of line: "<<number_of_lines<<endl;

 //TCHAIN FILES TOGETHER=======================================
  std::ifstream instr(infile.c_str(), std::ifstream::in);
  std::string filename;
  TChain* tChain;
  tChain = new TChain("dijet/t");
  for(int i=0;i<number_of_lines;i++){
    instr >> filename;
    cout<<filename<<endl<<endl;
    TFile *f = TFile::Open(filename.c_str());
    f->Close();
  }

}
