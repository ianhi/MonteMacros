
//  Ian Hunt-Isaak
//  created: 16 June 2015

//  Macro to read output root files from multiple HIGenerator batch runs

//better to bring a bazooka to kill a goat - include all things
//ORDER OF FILES IN FILELIST MUST BE AS FOLLOWS
/*
  PYTHIA
  Pyquen
  PyqeunWide
  Jewel
  QPythia
*/
#include <iostream>
#include <fstream>
#include <TRandom.h>
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
#include <TRandom3.h>
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


using namespace std;

int nPythia;
int nPyquen;
int nPyquenWide;
int nJewel;
int nQPythia;

int beginPythia;
int beginPyquen;
int beginPyquenWide;
int beginJewel;
int beginQPythia;

TStopwatch timer;

void combineAnalysis(const int startfile=0, const int endfile=30){

  TH1::SetDefaultSumw2();

  timer.Start();
  
  std::string infile;
  infile = "filelist.txt";
  std::ifstream instr(infile.c_str(), std::ifstream::in);

  std::string s;
  getline(instr, s);//ignore first line
  getline(instr, s);


  stringstream ss(s);ss>>nPythia;
  ss<<s;  ss>>nPyquen; s.erase(0,s.find(" ")+1);
  ss<<s;s.erase(0,s.find(" ")+1);  ss>>nPyquenWide; 
  ss<<s;s.erase(0,s.find(" ")+1);  ss>>nJewel;
  ss<<s;s.erase(0,s.find(" ")+1);  ss>>nQPythia; 

  beginPythia=0;
  beginPyquen=beginPythia+nPythia;
  beginPyquenWide=beginPyquen+nPyquen;
  beginJewel=beginPyquenWide+nPyquenWide;
  beginQPythia=beginJewel+nJewel;

  cout<<nPythia<<"     nPythia \n";
  cout<<nPyquen<<"     nPyquen \n";
  cout<<nPyquenWide<<"     nPyquenWide \n";
  cout<<nJewel<<"     nJewel \n";
  cout<<nQPythia<<"     nQPythia\n\n";
  
  cout<<beginPythia<<"     beginPythia \n";
  cout<<beginPyquen<<"     beginPyquen \n";
  cout<<beginPyquenWide<<"     beginPyquenWide \n";
  cout<<beginJewel<<"     beginJewel \n";
  cout<<beginQPythia<<"     beginQPythia\n";
  
  std::string filename;
  int nFiles = endfile - startfile;
  cout<<"Running on "<<nFiles<<" forest files"<<endl;
  // we are not TChaining here since its easier to just open and close one file at a time. 
  
  //just to read the files till the start number.
  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    cout<<"in here \n";
    instr >> filename;
  }

  //output file:
  
  TFile f(Form("test_outputFile_%d.root",endfile),"RECREATE");

  //defining histograms
  TH1D * pythia_Phi = new TH1D("pythia_Phi","",20,3.14159/2,3.1416);
  TH1D * pythia_Aj =  new TH1D("pythia_Aj","",20,0,1);
  TH1D * pythia_Raa =  new TH1D("pythia_Raa","",20,100,300);
  TProfile * pythia_JR =  new TProfile("pythia_JR","",10,100,200);


  TH1D * jewel_Phi = new TH1D("jewel_Phi","",20,3.14159/2,3.1416);
  TH1D * jewel_Aj =  new TH1D("jewel_Aj","",20,0,1);
  TH1D * jewel_Raa =  new TH1D("jewel_Raa","",20,100,300);
  TProfile * jewel_JR =  new TProfile("jewel_JR","",10,100,200);

  TH1D * pyquen_Phi = new TH1D("pyquen_Phi","",20,3.14159/2,3.1416);
  TH1D * pyquen_Aj =  new TH1D("pyquen_Aj","",20,0,1);
  TH1D * pyquen_Raa =  new TH1D("pyquen_Raa","",20,100,300);
  TProfile * pyquen_JR =  new TProfile("pyquen_JR","",10,100,200);
   
  TH1D * pyquenWide_Phi = new TH1D("pyquenWide_Phi","",20,3.14159/2,3.1416);
  TH1D * pyquenWide_Aj =  new TH1D("pyquenWide_Aj","",20,0,1);
  TH1D * pyquenWide_Raa =  new TH1D("pyquenWide_Raa","",20,100,300);
  TProfile * pyquenWide_JR =  new TProfile("pyquenWide_JR","",10,100,200);

  TH1D * QPythia_Phi = new TH1D("QPythia_Phi","",20,3.14159/2,3.1416);
  TH1D * QPythia_Aj =  new TH1D("QPythia_Aj","",20,0,1);
  TH1D * QPythia_Raa =  new TH1D("QPythia_Raa","",20,100,300);
  TProfile * QPythia_JR =  new TProfile("QPythia_JR","",10,100,200);

  //looping through files yet to be read
  cout<<startfile<<"    startfile\n";
  cout<<endfile<<"    endfile\n";
  for(int ifile=startfile;ifile<endfile;ifile++){
    cout<<"in file loop\n";
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

    if(ifile<beginPyquen){
      cout<<"Pythia File\n\n";
      pythia_Phi->Add(temp_Phi);
      pythia_Aj->Add(temp_Aj);
      pythia_Raa->Add(temp_Raa);
      pythia_JR->Add(temp_JR);

    }
    else if(ifile<beginPyquenWide){
      cout<<"Pyquen File\n\n";
      pyquen_Phi->Add(temp_Phi);
      pyquen_Aj->Add(temp_Aj);
      pyquen_Raa->Add(temp_Raa);
      pyquen_JR->Add(temp_JR);
    }
    else if(ifile<beginJewel){
      cout<<"PyquenWide File\n\n";
      pyquenWide_Phi->Add(temp_Phi);
      pyquenWide_Aj->Add(temp_Aj);
      pyquenWide_Raa->Add(temp_Raa);
      pyquenWide_JR->Add(temp_JR);
    }
    else if(ifile<beginQPythia){
      cout<<"Jewel File\n\n";
      jewel_Phi->Add(temp_Phi);
      jewel_Aj->Add(temp_Aj);
      jewel_Raa->Add(temp_Raa);
      jewel_JR->Add(temp_JR);
    }
    else if(ifile<beginQPythia+nQPythia){
      QPythia_Phi->Add(temp_Phi);
      QPythia_Aj->Add(temp_Aj);
      QPythia_Raa->Add(temp_Raa);
      QPythia_JR->Add(temp_JR);
    }
    else{
      cout<<"ERROR   met no conditions --- something is very wrong\n\n";
    }

    fin->Close();//hehe fin

  }//end of file loop
  f.cd();
  f.Write();
  f.Close();
  // cout<< pythia_Phi->GetEntries()<<"pythia entries\n\n";
  
    timer.Stop();
    float rtime = timer.RealTime();
    //  float ctime = time.CpuTime();

    std::cout<<"\t"<<std::endl;
    std::cout<<Form("RealTime=%f seconds, CpuTime=%f seconds",rtime,ctime)<<std::endl;
    std::cout<<"\t"<<std::endl;
    std::cout<<"Good bye : " <<"\t"<<std::endl;
  
}
