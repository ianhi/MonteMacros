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

void testList(const int startfile=0,int endfile=-1,int radius=3){
   //SET UP FILE LIST==========================================
  std::string infile;
  infile = "jetRAA_pp_data_forest.txt";
  cout<<"txt file in same dir\n";
  cout<<"\n\nReading from: "+infile<<endl;
  std::ifstream instr(infile.c_str(), std::ifstream::in);
 
  //If number of files to read not specified then read how many lines are in file
  if(endfile==-1){
    std::ifstream fi(infile.c_str());
    std::string line;
    int number_of_lines=0;
    while (std::getline(fi, line)) ++number_of_lines;
    endfile+=number_of_lines+1;
    cout<<"You did not specify number of files will run on all: "<<endfile<<" lines\n";
  }

  // If not starting from file 0 discard earlier lines
  std::string filename;
  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    instr >> filename;
  }
  cout<<"Running on "<<endfile-startfile<<" forest files"<<endl;


  for(int ifile=startfile;ifile<endfile;ifile++){
    instr >> filename;
    cout<<"ifile: "<<ifile<<"\nFile: "<<filename<<endl;
  }
}



