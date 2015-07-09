
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
void jtptWeightPlotCheck(){
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  TFile *f = TFile::Open(Form("weights.root"));


  TLegend *leg = new TLegend(0.7,0.5,0.99,0.9);


  TH1D * Jet2_hT = (TH1D*)f->Get("Jet2_hT_HI");
  TH1D * Jet3_hT = (TH1D*)f->Get("Jet3_hT_HI");
  leg->AddEntry(Jet2_hT,"Jet2");
  leg->AddEntry(Jet3_hT,"Jet3");

  TCanvas * cJR_hT = new TCanvas("cJR_hT","",600,600);
  cJR_hT->cd();

  Jet2_hT->SetMarkerColor(kGreen);
  Jet2_hT->SetMarkerStyle(20);
  Jet3_hT->SetMarkerStyle(20);

  Jet2_hT->Draw();
  Jet3_hT->Draw("same");
  leg->Draw(); 
  cJR_hT->SaveAs("PNG/check_hT_med1.png","RECREATE");


  TH1D * Jet2_pT = (TH1D*)f->Get("Jet2_pT_HI");
  TH1D * Jet3_pT = (TH1D*)f->Get("Jet3_pT_HI");
  TCanvas * cpT = new TCanvas("chT","",600,600);
  cpT->cd();
  
  Jet2_pT->SetMarkerColor(kGreen);
  Jet2_pT->SetMarkerStyle(20);
  Jet3_pT->SetMarkerStyle(20);

  Jet2_pT->Draw();
  Jet3_pT->Draw("same");
  leg->Draw();
  cpT->SaveAs("PNG/check_pT_med1.png","RECREATE");
  
}