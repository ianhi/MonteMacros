#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
void ppWeightPlot(){

  bool bPT=true; //MC Jet  ratio with leading jet pt
  bool bHT=true; //MC  jet ratio using  H_{T}
  bool bPTHAT=true; //plot MC spectra
  bool bJTPT=true; //plot MC jtpt
  bool bDataPT=false;
  bool bDataHT=false;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *f = TFile::Open(Form("MCadded.root"));
 
  if(bPT){
    TH1D * Jet2_pT = (TH1D*)f->Get("Jet2_pT_pp");
    TH1D * Jet3_pT = (TH1D*)f->Get("Jet3_pT_pp");

    TCanvas * cPT = new TCanvas("cPT","",600,600);
    cPT->cd();
    TH1D * ratio_pT = new TH1D("ratio_pT","PT pp 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)",100,0,1000);
    ratio_pT->Add(Jet3_pT);
    ratio_pT->Divide(Jet2_pT);
    ratio_pT->SetMaximum(1.2);
    ratio_pT->Draw();
    cPT->SaveAs("PNG/PP_JR_PT_Weight.png","RECREATE");
  }
  if(bHT){

    TH1D * Jet2_hT = (TH1D*)f->Get("Jet2_hT_pp");
    TH1D * Jet3_hT = (TH1D*)f->Get("Jet3_hT_pp");

    TCanvas * cHT = new TCanvas("cHT","",600,600);
    cHT->cd();
    TH1D * ratio_hT = new TH1D("ratio_hT","HT pp 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)",100,0,1000);
    ratio_hT->Add(Jet3_hT);
    ratio_hT->Divide(Jet2_hT);
    ratio_hT->SetMaximum(1.2);
    ratio_hT->Draw();
    cHT->SaveAs("PNG/PP_JR_HT_Weight.png","RECREATE");
  }
  if(bPTHAT){
    TH1D * pthat = (TH1D*)f->Get("pthat_pp");
    TCanvas * cPTH = new TCanvas("cPTH","",900,600);
    cPTH->SetLogy();
    cPTH->cd();
    pthat->SetXTitle("pthat");
    pthat->Draw();
    cPTH->SaveAs("PNG/PP_PTHAT_Weight.png","RECREATE");
  }
  if(bJTPT){
    TH1D * jtpt = (TH1D*)f->Get("jtpt_pp");
    TCanvas * cJTP = new TCanvas("cJTP","",900,600);
    cJTP->SetLogy();
    cJTP->cd();
    jtpt->SetXTitle("jtpt");
    jtpt->Draw();
    cJTP->SaveAs("PNG/PP_JTPT_Weight.png","RECREATE");
  }
  if(bDataPT){
    TH1D * Jet2_pT_Data = (TH1D*)f->Get("Jet2_pT_pp_Data");
    TH1D * Jet3_pT_Data = (TH1D*)f->Get("Jet3_pT_pp_Data");

    TCanvas * cPT_Data = new TCanvas("cPT_Data","",600,600);
    cPT_Data->cd();
    TH1D * ratio_pT_Data = new TH1D("ratio_pT_Data","Data PT pp 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)",100,0,500);
    ratio_pT_Data->Add(Jet3_pT_Data);
    ratio_pT_Data->Divide(Jet2_pT_Data);
    ratio_pT_Data->Draw();
    cPT_Data->SaveAs("PNG/PP_JR_PT_Data.png","RECREATE");
  }
  if(bDataHT){

    TH1D * Jet2_hT_Data = (TH1D*)f->Get("Jet2_hT_pp_Data");
    TH1D * Jet3_hT_Data = (TH1D*)f->Get("Jet3_hT_pp_Data");

    TCanvas * cHT_Data = new TCanvas("cHT_Data","",600,600);
    cHT_Data->cd();
    TH1D * ratio_hT_Data = new TH1D("ratio_hT_Data","Data HT pp 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)",100,0,500);
    ratio_hT_Data->Add(Jet3_hT_Data);
    ratio_hT_Data->Divide(Jet2_hT_Data);
    ratio_hT_Data->Draw();
    cHT_Data->SaveAs("PNG/PP_JR_HT_Data.png","RECREATE");
  }
  f->Close();
}
