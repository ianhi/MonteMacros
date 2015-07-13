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

  bool bPT=true; //jet ratio 
  bool bHT=true; //jet ratio using nref
  bool bPTHAT=true; //plot pthat spectra
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *f = TFile::Open(Form("added.root"));
 
  if(bPT){
    TH1D * Jet2_pT = (TH1D*)f->Get("Jet2_pT_pp");
    TH1D * Jet3_pT = (TH1D*)f->Get("Jet3_pT_pp");

    TCanvas * cPT = new TCanvas("cPT","",600,600);
    cPT->cd();
    TH1D * ratio_pT = new TH1D("ratio_pT","PT pp 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)",100,0,500);
    ratio_pT->Add(Jet3_pT);
    ratio_pT->Divide(Jet2_pT);
    ratio_pT->Draw();
    cPT->SaveAs("PNG/PP_JR_PT_Weight.png","RECREATE");
  }
  if(bHT){

    TH1D * Jet2_hT = (TH1D*)f->Get("Jet2_hT_pp");
    TH1D * Jet3_hT = (TH1D*)f->Get("Jet3_hT_pp");

    TCanvas * cHT = new TCanvas("cHT","",600,600);
    cHT->cd();
    TH1D * ratio_hT = new TH1D("ratio_hT","HT pp 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)",100,0,500);
    ratio_hT->Add(Jet3_hT);
    ratio_hT->Divide(Jet2_hT);
    ratio_hT->Draw();
    cHT->SaveAs("PNG/PP_JR_HT_Weight.png","RECREATE");
  }
  if(bPTHAT){
    TH1D * pthat = (TH1D*)f->Get("pthat_pp");
    TCanvas * cPTH = new TCanvas("cPTH","",600,600);
    cPTH->SetLogy();
    cPTH->cd();
    pthat->SetXTitle("pthat");
    pthat->Draw();
    cPTH->SaveAs("PNG/PP_PTHAT_Weight.png","RECREATE");
  }
  f->Close();
}
