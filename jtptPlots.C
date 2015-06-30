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

void jtptPlots(){
  
  bool DEBUG =true;

  bool Phi=false;
  bool  Aj=false;
  bool  JR=false;
  bool Raa=true;
  bool jtpt=true;
  timer.Start(); 
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  stringstream name;
  std::string medType="med1_";
  TFile *f = TFile::Open(Form("med1_PTHAT_histograms_endFile10.root"));
  //Color array==============================//
  //good resource here https://root.cern.ch/root/html522/TColor.html
  int colors[10];
  TCanvas *c = new TCanvas("cPhi","",600,600);
  c->cd();
  c->SetLogy();
  
  TLegend *leg = new TLegend(0.7,0.5,0.99,0.9);
  for(int i=0;i<10;i++){
    colors[i]=i+1;
    if(i==9) colors[i]=12;
    if(i==8 ) colors[i]=28;
  }
  std::string legends[11]={"15-30","30-50","50-80","80-120","120-170","170-220","weee 6 doesn't matter","280-330","330-400","400-460","460-540"};
  TH1D * h[10];
  for(int i=0;i<10;i++){
    name.str("");
    name<<i<<"_jtpt_25K";
    cout<<name.str()<<"\n\n";
    h[i]=(TH1D*)f->Get(name.str().c_str());
    h[i]->SetMarkerColor(colors[i]);
    h[i]->SetLineColor(colors[i]);
    //h[i]->Draw("same");
    leg->AddEntry(h[i], legends[i].c_str());
  }
  TH1D * total=h[0];
  for(int i=1;i<10;i++){
    total->Add(h[i]);
  }

  total->Draw();
  leg->Draw();

  /*
  TH1D * h0 = (TH1D*)f->Get("0_jtpt_25K");
  TH1D * h1 = (TH1D*)f->Get("1_jtpt_25K");
  TH1D * h2 = (TH1D*)f->Get("2_jtpt_25K");
  TH1D * h3 = (TH1D*)f->Get("3_jtpt_25K");
  TH1D * h4 = (TH1D*)f->Get("4_jtpt_25K");
  TH1D * h5 = (TH1D*)f->Get("5_jtpt_25K");
  TH1D * h6 = (TH1D*)f->Get("6_jtpt_25K");
  TH1D * h7 = (TH1D*)f->Get("7_jtpt_25K");
  TH1D * h8 = (TH1D*)f->Get("8_jtpt_25K");
  TH1D * h9 = (TH1D*)f->Get("9_jtpt_25K");
  
  h0->Draw();
  */
}
