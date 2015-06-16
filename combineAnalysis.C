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

using namespace std;

int nPythia;
int nPyquen;
int nPyquenWide;
int nJewel;
int nQPythia;

TStopwatch timer;

void combineAnalysis(const int startfile=0, const int endfile=1){

  TH1::SetDefaultSumw2();
  /*
    bool printDebug = true;
    bool pythia = true;
    bool pyquen = true;
    bool pyquenWide = true;
    bool jewel = true;
    bool Qpythia = true;
  */
  timer.Start();
  
  std::string infile;
  infile = "filelist.txt";
  std::ifstream instr(infile.c_str(), std::ifstream::in);

  std::string s;
  getline(instr, s);//ignore first line
  getline(instr, s);

  stringstream ss(s);s.erase(0,s.find(" ")+1);  ss>>nPythia;
  stringstream ss(s);s.erase(0,s.find(" ")+1);  ss>>nPyquen; 
  stringstream ss(s);s.erase(0,s.find(" ")+1);  ss>>nPyquenWide; 
  stringstream ss(s);s.erase(0,s.find(" ")+1);  ss>>nJewel;
  stringstream ss(s);s.erase(0,s.find(" ")+1);  ss>>nQPythia; 
  beginPythia=0;
  beginPyquen=beginPythia+nPythia;
  beginPyquenWide=beginPyquen+nPyquen;
  beginJewel=beginPyquenWide+nPyquenWide;
  beginQPythia=beginJewel+nJewel;

  cout<<nPythia<<"     nPythia \n";
  cout<<nPyquen<<"     nPyquen \n";
  cout<<nPyquenWide<<"     nPyquenWide \n";
  cout<<nJewel<<"     nJewel \n";
  cout<<nQPythia<<"     nQPythia\n";
  
  std::string filename;
  int nFiles = endfile - startfile;
  cout<<"Running on "<<nFiles<<" forest files"<<endl;
  // we are not TChaining here since its easier to just open and close one file at a time. 
  
  //just to read the files till the start number.
  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    instr >> filename;
    
  }

  //output file:
  
  TFile f(Form("test_outputFile_%d.root",endfile),"RECREATE");

  //defining histograms
  TH1D * pythia_Phi = new TH1D("pythia_Phi","",20,3.14159/2,3.1416);
  TH1D * pythia_Aj =  new TH1D("pythia_Aj","",20,0,1);
  TH1D * pythia_Raa =  new TH1D("pythia_R","",20,100,300);
  TProfile * pythia_JR =  new TProfile("pythia_JR","",10,100,200);


  TH1D * jewel_Phi = new TH1D("jewel_Phi","",20,3.14159/2,3.1416);
  TH1D * jewel_Aj =  new TH1D("jewel_Aj","",20,0,1);
  TH1D * jewel_Raa =  new TH1D("jewel_R","",20,100,300);
  TProfile * jewel_JR =  new TProfile("jewel_JR","",10,100,200);

  TH1D * pyquen_Phi = new TH1D("pyquen_Phi","",20,3.14159/2,3.1416);
  TH1D * pyquen_Aj =  new TH1D("pyquen_Aj","",20,0,1);
  TH1D * pyquen_Raa =  new TH1D("pyquen_R","",20,100,300);
  TProfile * pyquen_JR =  new TProfile("pyquen_JR","",10,100,200)
   
  TH1D * pyquenWide_Phi = new TH1D("pyquenWide_Phi","",20,3.14159/2,3.1416);
  TH1D * pyquenWide_Aj =  new TH1D("pyquenWide_Aj","",20,0,1);
  TH1D * pyquenWide_Raa =  new TH1D("pyquenWide_R","",20,100,300);
  TProfile * pyquenWide_JR =  new TProfile("pyquenWide_JR","",10,100,200);

  TH1D * QPythia_Phi = new TH1D("QPythia_Phi","",20,3.14159/2,3.1416);
  TH1D * QPythia_Aj =  new TH1D("QPythia_Aj","",20,0,1);
  TH1D * QPythia_Raa =  new TH1D("QPythia_R","",20,100,300);
  TProfile * QPythia_JR =  new TProfile("QPythia_JR","",10,100,200);

  //looping through files yet to be read
  for(int ifile=startfile;ifile<endfile;ifile++){
    instr >> filename;
    cout<<"File: "<<filename<<std::endl;
    TFile *fin = TFile::Open(filename.c_str());
    TTree * nt = (TTree*)fin->Get("dijet/nt");
    TTree * t  = (TTree*)fin->Get("dijet/t");

    if(ifile<beginPyquen){
      cout<<"Pythia File\n\n";

      nt->Draw("(pt1-pt2)/(pt1+pt2)>>pythia_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
      nt->Draw("acos(cos(dphi))>>pythia_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

      t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>pythia_Jr","Sum$(jtpt>30)>1","goff");
      t->Draw("jtpt>>pythia_R","","goff");
    }
    else if(ifile<beginPyquenWide){
      cout<<"Pyquen File\n\n";

      nt->Draw("(pt1-pt2)/(pt1+pt2)>>pyquen_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
      nt->Draw("acos(cos(dphi))>>pyquen_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

      t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>pyquen_Jr","Sum$(jtpt>30)>1","goff");
      t->Draw("jtpt>>pyquen_R","","goff");
      
    }
    else if(ifile<beginJewel){
      cout<<"PyquenWide File\n\n";

      nt->Draw("(pt1-pt2)/(pt1+pt2)>>pyquenWide_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
      nt->Draw("acos(cos(dphi))>>pyquenWide_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

      t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>pyquenWide_Jr","Sum$(jtpt>30)>1","goff");
      t->Draw("jtpt>>pyquenWide_R","","goff");

    }
    else if(ifile<beginQPythia){
      cout<<"Jewel File\n\n";

      nt->Draw("(pt1-pt2)/(pt1+pt2)>>QPythia_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
      nt->Draw("acos(cos(dphi))>>QPythia_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

      t->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>QPythia_Jr","Sum$(jtpt>30)>1","goff");
      t->Draw("jtpt>>QPythia_R","","goff");

    }
    else{
      cout<<"ERROR   met no conditions --- something is very wrong\n\n";
    }

    fin.Close();

  }//end of file loop
  f.cd();
  f.Write();
  f.Close();
  timer.Stop();
  float rtime = timer.RealTime();
  float ctime = time.CpuTime();

  std::cout<<"\t"<<std::endl;
  std::cout<<Form("RealTime=%f seconds, CpuTime=%f seconds",rtime,ctime)<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"Good bye : " <<"\t"<<std::endl;
}
