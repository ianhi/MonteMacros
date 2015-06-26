// Ian Hunt-Isaak
// ianhuntisaak@gmail.com
// ihuntisa@oberlin.edu Primary email until May 2017

// Created: 25 June 2015

// Macro to read output root files from multiple Jewel Runs
// Files are stored on cernbox and read in by a filelist
// File list can be split into multiple jobs with _______ BATCH SCRIPT HERE
// Can also be run on the filelist as one job 
// Which of above options is best is depended on number and sizes of files


//better to bring a bazooka to kill a goat [import all things]- Raghav K
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


using namespace std;
 
TStopwatch timer;

void multJewelAnalysis(const int startfile=0, int endfile=-1/*,string infile="med1Filelist.txt"*/ ){

  timer.Start();  
  TH1::SetDefaultSumw2();
  std::string infile;
  infile = "med1Filelist.txt";
  cout<<"\n\nReading from: "+infile<<endl;
  std::ifstream instr(infile.c_str(), std::ifstream::in);
 
  if(endfile==-1){
    std::ifstream fi(infile.c_str());
    std::string line;
    int number_of_lines=0;
    while (std::getline(fi, line))
      {
	++number_of_lines;
      }
    endfile+=number_of_lines;//-1 accounts for line telling medium type.
    cout<<"You did not specify number of files will run on all: "<<endfile<<" lines\n";
  }

  std::string medType;
  getline(instr, medType);// get name of medium params
  cout<<"\n\n medType:  "+medType+"\n";

  std::string filename;

  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    instr >> filename;
  }

  int nFiles = endfile - startfile;
  cout<<"Running on "<<nFiles<<" forest files"<<endl;
  
  TFile f(Form("%s_histograms_endFile%d.root",medType.c_str(),endfile),"RECREATE");
  std::string name;
  name=medType+"_jewel_Phi";
  
  TH1D * jewel_Phi = new TH1D(name.c_str(),"",20,3.14159/2,3.1416);
  name=medType+"_jewel_Aj";
  TH1D * jewel_Aj =  new TH1D(name.c_str(),"",20,0,1);
  name=medType+"_jewel_Raa";  
  TH1D * jewel_Raa =  new TH1D(name.c_str(),"",20,100,300);
  name=medType+"_jewel_JR";
  TProfile * jewel_JR =  new TProfile(name.c_str(),"",10,100,200);
  
  for(int ifile=startfile;ifile<endfile;ifile++){ // file loop
    instr >> filename;
    
    TFile *fin = TFile::Open(filename.c_str());
    TTree * nt = (TTree*)fin->Get("dijet/nt");
    TTree * t  = (TTree*)fin->Get("dijet/t");
    cout<<"File: "<<filename<<std::endl;
    
    TH1D * temp_Phi = new TH1D("temp_Phi","",20,3.14159/2,3.1416);
    TH1D * temp_Aj =  new TH1D("temp_Aj","",20,0,1);
    TH1D * temp_Raa =  new TH1D("temp_Raa","",20,100,300);
    TProfile * temp_JR =  new TProfile("temp_JR","",10,100,200);

    nt -> Draw("acos(cos(dphi))>>temp_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
    nt->Draw("(pt1-pt2)/(pt1+pt2)>>temp_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
    t->Draw("jtpt>>temp_Raa","","goff");
    t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>temp_JR","Sum$(jtpt>30)>1","goff");
    
    
      cout<<temp_Phi->GetEntries()<<"   temp Phi entries\n\n";
      cout<<temp_Aj->GetEntries()<<"   temp Aj entries\n\n";
      cout<<temp_Raa->GetEntries()<<"   temp Raa entries\n\n";
      cout<<temp_JR->GetEntries()<<"   temp JR entries\n\n";

      jewel_Phi->Add(temp_Phi);
      jewel_Aj->Add(temp_Aj);
      jewel_Raa->Add(temp_Raa);
      jewel_JR->Add(temp_JR);
    
    fin->Close();
    
  } // end of file loop
 
  
  f.cd();
  f.Write();
  f.Close();
  timer.Stop();
  float rtime = timer.RealTime();
 
  std::cout<<"\t"<<std::endl;
  std::cout<<Form("RealTime=%f seconds",rtime)<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"Good bye : " <<"\t"<<std::endl;
}
