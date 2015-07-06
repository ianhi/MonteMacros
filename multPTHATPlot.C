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
int nFiles=11;

void multPTHATPlot(){
  
  bool DEBUG =true;
  bool Phi=false;
  bool  Aj=false;
  bool  JR=false;
  bool Raa=true;
  bool jtpt=false;
  timer.Start(); 
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  stringstream name;
  std::string medType="med1_";
  TFile *f = TFile::Open(Form("med1_PTHAT_histograms_endFile10.root"));
  //Color array==============================//
  //good resource here https://root.cern.ch/root/html522/TColor.html
  int colors[nFiles];
  for(int i=0;i<nFiles;i++){
    colors[i]=i+1;
    if(i==9)  colors[i]=12;
    if(i==8 ) colors[i]=28;
    if(i==10) colors[i]=41;
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

    cAj->SaveAs("ptAj.png","RECREATE");

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
    cPhi->SaveAs("ptPhi.png","RECREATE");

  }
  //===================JR====================//
  if(JR){
    TCanvas *cJR = new TCanvas("cJR","",600,600);
    cJR->cd();
    
    TLegend *leg_JR = new TLegend(0.7,0.5,0.99,0.9);
    leg_JR->SetFillStyle(0);
    leg_JR->SetBorderSize(0);
    TH2D *h0_JR = new TH2D("h0_JR","",10,10,540,2000,0,1.1);
    h0_JR->SetXTitle("Leading Jet p_{T} (GeV/c)");
    h0_JR->SetYTitle("3-Jet / 2-Jet ratio");
    h0_JR->GetYaxis()->SetTitleOffset(1.5);
    h0_JR->Draw();
  
    TH1D * JR[nFiles];
    for(int i=0;i<nFiles;i++){
      if(DEBUG){
	cout<<"i: "<<i<<"\n";
	cout<<"legend: "<<legends[i]<<"\n";
      }
      if(i==6) continue;//run six is empty
      name.str("");
      name<<medType<<i<<"_JR_25K";
      cout<<name.str()<<"\n\n";
      JR[i]=(TH1D*)f->Get(name.str().c_str());
      JR[i]->SetMarkerStyle(20);
      JR[i]->SetMarkerColor(colors[i]);
      JR[i]->SetLineColor(colors[i]);
      JR[i]->Draw("same");
      
      leg_JR->AddEntry(JR[i], legends[i].c_str());
    }
    leg_JR->Draw();

    cJR->SaveAs("ptJR.png","RECREATE");
  }
  //===================RAA===================//
   if(Raa){
   TCanvas *cRaa = new TCanvas("cRaa","",600,600);
    cRaa->cd();
    
    TLegend *leg_Raa = new TLegend(0.7,0.5,0.99,0.9);
    leg_Raa->SetFillStyle(0);
    leg_Raa->SetBorderSize(0);
    
    TH2D *h0_Raa = new TH2D("h0_Raa","",10,100,200,2000,0,2);
    h0_Raa->SetXTitle("leading jet pt");
    h0_Raa->SetYTitle("R_{AA}");
    h0_Raa->GetYaxis()->SetTitleOffset(1.5);
    h0_Raa->Draw();
    
    TH1D * pRaa = (TH1D*)f->Get("pythia_Raa");
    int nPRaa=pRaa->GetEntries(); pRaa->Scale(1./nPRaa);
    TH1D * Raa[nFiles];
    for(int i=0;i<nFiles;i++){
      if(DEBUG){
	cout<<"i: "<<i<<"\n";
	cout<<"legend: "<<legends[i]<<"\n";
      }
      if(i==6) continue;//run six is empty
      name.str("");
      name<<medType<<i<<"_Raa_25K";
      cout<<name.str()<<"\n\n";
      Raa[i]=(TH1D*)f->Get(name.str().c_str());
      Raa[i]->SetMarkerStyle(20);
      Raa[i]->SetMarkerColor(colors[i]);
      Raa[i]->SetLineColor(colors[i]);
      Raa[i]->Scale(1./Raa[i]->GetEntries());
      Raa[i]->Divide(pRaa);
      Raa[i]->Draw("same");
      
      leg_Raa->AddEntry(Raa[i], legends[i].c_str());
    }
    pRaa->Draw("hist same");
    leg_Raa->Draw();
    cRaa->SaveAs("ptRaa.png","RECREATE");
  }
   //====================JTPT=========================//
  if(jtpt){
    TCanvas *cjtpt = new TCanvas("cjtpt","",600,600);
    cjtpt->cd();
    cjtpt->SetLogy();
    TLegend *leg_jtpt = new TLegend(0.7,0.5,0.99,0.9);
    leg_jtpt->SetFillStyle(0);
    leg_jtpt->SetBorderSize(0);
    
    TH2D *h0_jtpt = new TH2D("h0_jtpt","",10,10,540,2000,0,2000);
    h0_jtpt->SetXTitle("jtpt");
    h0_jtpt->SetYTitle("Counts");
    h0_jtpt->GetYaxis()->SetTitleOffset(1.5);
    h0_jtpt->Draw();
  
    TH1D * jtpt[nFiles];
    for(int i=0;i<nFiles;i++){
      if(DEBUG){
	cout<<"i: "<<i<<"\n";
	cout<<"legend: "<<legends[i]<<"\n";
      }
      if(i==6) continue;//run six is empty
      name.str("");
      name<<i<<"_jtpt_25K";
      cout<<name.str()<<"\n\n";
      jtpt[i]=(TH1D*)f->Get(name.str().c_str());
      jtpt[i]->SetMarkerStyle(20);
      jtpt[i]->SetMarkerColor(colors[i]);
      jtpt[i]->SetLineColor(colors[i]);
      int njtpt=jtpt[i]->GetEntries(); jtpt[i]->Scale(1./njtpt);
      jtpt[i]->Draw("same");
      
      leg_jtpt->AddEntry(jtpt[i], legends[i].c_str());
    }
    leg_jtpt->Draw();

    cjtpt->SaveAs("ptJtpt.png","RECREATE");
  }
}
