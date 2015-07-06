// Ian Hunt-Isaak
// ianhuntisaak@gmail.com
// ihuntisa@oberlin.edu Primary email until May 2017

// Created: 29 June 2015

// Macro to compare outputs of 11 different root files each with different pthat ranges
// To plot output run multPTHATPlot.C

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

int JR_pt_max=400;
int JR_pt_min=10;
int JR_bins=20;
TStopwatch timer;

void multPTHATAnalysis(const int startfile=0, int endfile=-1/*,string infile="med1Filelist.txt"*/ ){

  timer.Start();  
  TH1::SetDefaultSumw2();
  std::string infile;
  infile = "25kFilelist.txt";
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
  medType=medType+"_";
  std::string filename;

  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    instr >> filename;
  }

  int nFiles = endfile - startfile;
  cout<<"Running on "<<nFiles<<" forest files"<<endl;
  TFile *pythia= TFile::Open("root://eosuser.cern.ch://eos/user/i/ihuntisa/PythiaZ2_0_numEvent100000.root");
  
  TTree * pnt = (TTree*)pythia->Get("dijet/nt");
  TTree * pt  = (TTree*)pythia->Get("dijet/t");

  TFile f(Form("%sPTHAT_histograms_endFile%d.root",medType.c_str(),endfile),"RECREATE");//define output file.

   TH1D * pythia_Phi = new TH1D("pythia_Phi","",20,3.14159/2,3.1416);
  TH1D * pythia_Aj =  new TH1D("pythia_Aj","",20,0,1);
  TH1D * pythia_Raa =  new TH1D("pythia_Raa","",20,100,300);
  TProfile * pythia_JR =  new TProfile("pythia_JR","",JR_bins,JR_pt_min,JR_pt_max);
  /*
  pnt -> Draw("acos(cos(dphi))>>pythia_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
  pnt->Draw("(pt1-pt2)/(pt1+pt2)>>pythia_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  pt->Draw("jtpt>>pythia_Raa","","goff");
  pt->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>pythia_JR","Sum$(jtpt>30)>1","goff");

  */
  pnt -> Draw("acos(cos(dphi))>>pythia_Phi","acos(cos(dphi))>0.5*3.14159","goff");
  pnt->Draw("(pt1-pt2)/(pt1+pt2)>>pythia_Aj","acos(cos(dphi))>2/3.*3.14159","goff");
  pt->Draw("jtpt>>pythia_Raa","","goff");
  pt->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>pythia_JR","Sum$(jtpt>30)>1","goff");


  stringstream myString;

  TH1D * Phi[12];
  TH1D *  Aj[12];
  TH1D * Raa[12];
  TH1D * jtpt[12];
  TProfile * JR[12];
  for(int ifile=startfile;ifile<=endfile;ifile++){
  
    // naming histograms ========================
    myString<<medType<<ifile<<"_Phi_25K";
    cout<<myString.str()<<"\n";

    Phi[ifile] = new TH1D(myString.str().c_str(),"",20,3.14159/2,3.1416);    
    myString.str("");
    myString<<medType<<ifile<<"_Aj_25K";
    cout<<myString.str()<<"\n";
    Aj[ifile] =  new TH1D(myString.str().c_str(),"",20,0,1);
    myString.str("");
    myString<<medType<<ifile<<"_Raa_25K";
    cout<<myString.str()<<"\n";
    Raa[ifile] =  new TH1D(myString.str().c_str(),"",20,100,300);
    myString.str("");
    myString<<medType<<ifile<<"_JR_25K";
    cout<<myString.str()<<"\n";
    JR[ifile] =  new TProfile(myString.str().c_str(),"",JR_bins,JR_pt_min,JR_pt_max);
    myString.str("");
    myString<<ifile<<"_jtpt_25K";
    jtpt[ifile] =  new TH1D(myString.str().c_str(),"",20,10,540 );
    myString.str("");    
  }
  for(int ifile=startfile;ifile<=endfile;ifile++){ // file loop
    instr >> filename;
    cout<<"Reading From: "<<filename<<std::endl;
    
    TFile *fin = TFile::Open(filename.c_str());
    TTree * nt = (TTree*)fin->Get("dijet/nt");
    TTree * t  = (TTree*)fin->Get("dijet/t");
   

   

    //drawing to temp histograms========================
    TH1D * temp_Phi = new TH1D("temp_Phi","",20,3.14159/2,3.1416);
    TH1D * temp_Aj =  new TH1D("temp_Aj","",20,0,1);
    TH1D * temp_Raa =  new TH1D("temp_Raa","",20,100,300);
    TH1D * temp_jtpt =  new TH1D("temp_jtpt","",20,10,540);
    TProfile * temp_JR =  new TProfile("temp_JR","",JR_bins,JR_pt_min,JR_pt_max);


    /*    nt -> Draw("acos(cos(dphi))>>temp_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
    nt->Draw("(pt1-pt2)/(pt1+pt2)>>temp_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
    t->Draw("jtpt>>temp_Raa","","goff");
    t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>temp_JR","Sum$(jtpt>30)>1","goff");
   
    t->Draw("jtpt>>temp_jtpt","","goff");
    */
    nt -> Draw("acos(cos(dphi))>>temp_Phi","pt2>15&&acos(cos(dphi))>0.5*3.14159","goff");
    nt->Draw("(pt1-pt2)/(pt1+pt2)>>temp_Aj","pt2>15&&acos(cos(dphi))>2/3.*3.14159","goff");
    t->Draw("jtpt>>temp_Raa","","goff");
    t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>temp_JR","Sum$(jtpt>30)>1","goff");
    t->Draw("jtpt>>temp_jtpt","","goff");
    
      cout<<temp_Phi->GetEntries()<<"   temp Phi entries\n";
      cout<<temp_Aj->GetEntries()<<"   temp Aj entries\n";
      cout<<temp_Raa->GetEntries()<<"   temp Raa entries\n";
      cout<<temp_JR->GetEntries()<<"   temp JR entries\n";
      cout<<temp_jtpt->GetEntries()<<"   temp jtpt entries\n\n\n";
      
      Phi[ifile]->Add(temp_Phi);
      Aj[ifile]->Add(temp_Aj);
      Raa[ifile]->Add(temp_Raa);
      JR[ifile]->Add(temp_JR);
      jtpt[ifile]->Add(temp_jtpt);
      
      cout<<jtpt[ifile]->GetEntries()<<"   jtpt entries\n\n\n";
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
