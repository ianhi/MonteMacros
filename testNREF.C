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
#include <stdio.h>
Float_t jtpt[1000];//jet pt taken from dijet/t
Int_t nref; //believe this to be the number of jets per event - variable in dijet/nt


void testNREF(){
  
  bool DEBUG=true;
  TFile * f = TFile::Open("../outputs/5_numEvents25000/med1_170_220_JewelDijet_5_numEvent25000.root");
   TTree * t = (TTree*)f->Get("dijet/t");
   TTree * nt = (TTree*)f->Get("dijet/nt");
   t->AddFriend(nt);
   t->SetBranchAddress("jtpt",jtpt);
   t->SetBranchAddress("nref",&nref);
   int Nevents = t->GetEntries();
   if(DEBUG) Nevents=1000;
   
   for(int iev=0;iev<Nevents;iev++){
      t->GetEntry(iev);
      /*   if(nref==2){
	cout<<"nref: "<<nref<<endl;
	cout<<"jtpt[0]: "<<jtpt[0]<<endl;
	cout<<"jtpt[1]: "<<jtpt[1]<<endl;	
	cout<<"jtpt[2]: "<<jtpt[2]<<endl<<endl;	
	}*/
      cout<<"nref: "<<nref<<endl;
      for(int n=0;n<nref+1;n++){
	cout<<"jtpt["<<n<<"]: "<<jtpt[n]<<endl;
      }
      for(int i=0;i<1000;i++)
	jtpt[i]=0;
    cout<<endl<<endl;
   }
}