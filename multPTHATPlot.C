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
 
TStopwatch timer;
int nFiles=10;
void multPTHATPlot(){
  
  bool DEBUG =true;

  bool Phi=true;
  bool  Aj=true;
  bool  JR=true;
  bool Raa=true;
  timer.Start(); 
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  stringstream name;
  std::string medType="med1_";
  TFile *f = TFile::Open(Form("med1_PTHAT_histograms_endFile10.root"));
  //Color array==============================//
  //good resource here https://root.cern.ch/root/html522/TColor.html
  int colors[10];
  for(int i=0;i<10;i++){
    colors[i]=i+1;
    if(i==9) colors[i]=12;
    if(i==8 ) colors[i]=28;
  }
  std::string legends[11]={"15-30","30-50","50-80","80-120","120-170","170-220","weee 6 doesn't matter","280-330","330-400","400-460","460-540"};
  //===================AJ====================//
  if(Aj){
    TCanvas *cAj = new TCanvas("cAj","",600,600);
    cAj->cd();
    
    TLegend *leg_Aj = new TLegend(0.7,0.5,0.99,0.9);
    leg_Aj->SetFillStyle(0);
    leg_Aj->SetBorderSize(0);

    TH2D *h0_Aj = new TH2D("h0_Aj","",20,0,1,200,0,0.4);
    h0_Aj->SetXTitle("A_{J}");
    h0_Aj->SetYTitle("Event Fraction");
    h0_Aj->GetYaxis()->SetTitleOffset(1.5);
    h0_Aj->Draw();
  
    TH1D * Aj[nFiles];
    for(int i=0;i<nFiles;i++){
      if(DEBUG){
	cout<<"i: "<<i<<"\n";
	cout<<"legend: "<<legends[i]<<"\n";
	cout<<"color: "<<colors[i]<<"\n";
      }
      if(i==6) continue;//run six is empty
      name.str("");
      name<<medType<<i<<"_Aj_25K";
      cout<<name.str()<<"\n\n";
      Aj[i]=(TH1D*)f->Get(name.str().c_str());
      Aj[i]->SetMarkerStyle(20);
      Aj[i]->SetMarkerColor(colors[i]);
      Aj[i]->SetLineColor(colors[i]);
      int nAj=Aj[i]->GetEntries(); Aj[i]->Scale(1./nAj);
      Aj[i]->Draw("same");
      
      leg_Aj->AddEntry(Aj[i], legends[i].c_str());
    }
    leg_Aj->Draw();


  }
  //===================PHI===================//
  if(Phi){
   TCanvas *cPhi = new TCanvas("cPhi","",600,600);
    cPhi->cd();
    
    TLegend *leg_Phi = new TLegend(0.7,0.5,0.99,0.9);
    leg_Phi->SetFillStyle(0);
    leg_Phi->SetBorderSize(0);
    TH2D *h0_Phi = new TH2D("h0_Phi","",20,3.14159/2,3.1416,2000,0,1);
    h0_Phi->SetXTitle("#Delta#phi");
    h0_Phi->SetYTitle("Event Fraction");
    h0_Phi->GetYaxis()->SetTitleOffset(1.5);
    h0_Phi->Draw();
  
    TH1D * Phi[nFiles];
    for(int i=0;i<nFiles;i++){
      if(DEBUG){
	cout<<"i: "<<i<<"\n";
	cout<<"legend: "<<legends[i]<<"\n";
      }
      if(i==6) continue;//run six is empty
      name.str("");
      name<<medType<<i<<"_Phi_25K";
      cout<<name.str()<<"\n\n";
      Phi[i]=(TH1D*)f->Get(name.str().c_str());
      Phi[i]->SetMarkerStyle(20);
      Phi[i]->SetMarkerColor(colors[i]);
      Phi[i]->SetLineColor(colors[i]);
      int nPhi=Phi[i]->GetEntries(); Phi[i]->Scale(1./nPhi);
      Phi[i]->Draw("same");
      
      leg_Phi->AddEntry(Phi[i], legends[i].c_str());
    }
    leg_Phi->Draw();

  }
  //===================JR====================//
  if(JR){
  }
  //===================RAA===================//
  if(Raa){
  }
}
