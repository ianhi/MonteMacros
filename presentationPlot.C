
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

void presentationPlot(){
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  bool log =true; // if true both plots will be log scale
  //  gStyle->SetTitleSize(.1,"x"); 


  TFile * f1 = TFile::Open("ROOT/Jewel/med1_weights.root");
  TFile * f8 = TFile::Open("ROOT/Jewel/med8_weights.root");
  TFile * fP = TFile::Open("ROOT/Jewel/Pythia_weights.root");
  TFile *f = TFile::Open(Form("MCadded.root"));

  TCanvas * cJR = new TCanvas("cJR","",600,600);
  TH2D *h0_JR = new TH2D("h0_JR","",10,10,1000,2000,0,1.2);
 
  TLegend *leg_JR = new TLegend(0.50,0.1,0.87,0.45);
  leg_JR->SetFillStyle(0);
  leg_JR->SetBorderSize(0);

  h0_JR->SetXTitle("H_{T} (GeV/c)");
  h0_JR->SetYTitle("3-Jet / 2-Jet ratio");
  h0_JR->GetYaxis()->SetTitleOffset(1.5);
  h0_JR->GetXaxis()->CenterTitle();

  cJR->cd();
  if(log) cJR->SetLogy();
  TH1D * JR2_m1 = (TH1D*)f1->Get("med1_Jet2_hT_HI");
  TH1D * JR3_m1 = (TH1D*)f1->Get("med1_Jet3_hT_HI");
  TH1D * ratio1_hT = new TH1D("","",100,0,1000);
  ratio1_hT->Add(JR3_m1);
  ratio1_hT->Divide(JR2_m1);
  ratio1_hT->SetMarkerStyle(20); ratio1_hT->SetMarkerColor(kBlack);
  

  TH1D * JR2_m8 = (TH1D*)f8->Get("med8_Jet2_hT_HI");
  TH1D * JR3_m8 = (TH1D*)f8->Get("med8_Jet3_hT_HI");
  TH1D * ratio8_hT = new TH1D("","",100,0,1000);
  ratio8_hT->Add(JR3_m8);
  ratio8_hT->Divide(JR2_m8);
  ratio8_hT->SetMarkerStyle(20); ratio8_hT->SetMarkerColor(kBlue);
  
  /*
  TH1D * JR2_P = (TH1D*)fP->Get("Pythia_Jet2_hT_HI");
  TH1D * JR3_P = (TH1D*)fP->Get("Pythia_Jet3_hT_HI");
  TH1D * ratioP_hT = new TH1D("","",100,0,1000);
  ratioP_hT->Add(JR3_P);
  ratioP_hT->Divide(JR2_P);
  ratioP_hT->SetMarkerStyle(20); ratioP_hT->SetMarkerColor(kGreen);
  */
  
  TH1D * Jet2_hT = (TH1D*)f->Get("Jet2_hT_pp");
  TH1D * Jet3_hT = (TH1D*)f->Get("Jet3_hT_pp");
  TH1D * ratio_hT = new TH1D("","",100,0,1000);
  ratio_hT->Add(Jet3_hT);
  ratio_hT->Divide(Jet2_hT);
  ratio_hT->SetMarkerStyle(20); ratio_hT->SetMarkerColor(kRed);

  h0_JR->Draw();
  ratio1_hT->Draw("same");
  ratio8_hT->Draw("same");
  //ratioP_hT->Draw("same");
  ratio_hT->Draw("same");
  leg_JR->SetHeader("#splitline{#sqrt{s} =2.76 TeV}{anti-K_{T} R= .3}");
  leg_JR->AddEntry(ratio1_hT,"Jewel: 0-10%");
  leg_JR->AddEntry(ratio8_hT,"Jewel: 80-90%");
  //leg_JR->AddEntry(ratioP_hT,"Pythia");
  leg_JR->AddEntry(ratio_hT,"Pythia");
  leg_JR->Draw();
  cJR->SaveAs("PNG/PRESENTATION_JR.png","RECREATE");
 
  //==========================AJ============================

  TH1D*AJ_m1 = (TH1D*)f1->Get("med1_Aj_MC");
  TH1D*AJ_m8 = (TH1D*)f8->Get("med8_Aj_MC");
  TH1D*AJ_P  = (TH1D*)fP->Get("Pythia_Aj_MC");
  TH1D*AJ_Po = (TH1D*)f ->Get("");
  TH2D *h0_Aj = new TH2D("h0_Aj",";A_{J}",20,0,1,200,0,0.4);
  TCanvas *cAj = new TCanvas("cAj","",600,600);
  
  TLegend *leg_AJ = new TLegend(0.60,0.5,0.87,0.87);
  leg_AJ->SetFillStyle(0);
  leg_AJ->SetBorderSize(0);

  cAj->cd();
  if(log) cAj->SetLogy();
  h0_Aj->SetYTitle("Event Fraction");
  h0_Aj->GetYaxis()->SetTitleOffset(1.5);
  h0_Aj->GetXaxis()->CenterTitle();

  AJ_m1->SetMarkerStyle(20); AJ_m1->SetMarkerColor(kBlack);
  AJ_m8->SetMarkerStyle(20); AJ_m8->SetMarkerColor(kBlue);
  AJ_P ->SetMarkerStyle(20); AJ_P ->SetMarkerColor(kRed);

  h0_Aj->Draw();
  AJ_m1->Draw("same");
  AJ_m8->Draw("same");
  AJ_P ->Draw("same");
  leg_AJ->SetHeader("#splitline{#sqrt{s} =2.76 TeV}{anti-K_{T} R= .3}");
  leg_AJ->AddEntry(AJ_m1,"Jewel: 0-10");
  leg_AJ->AddEntry(AJ_m8,"Jewel: 80-90");
  leg_AJ->AddEntry(AJ_P ,"Pythia");
  leg_AJ->Draw();
  cAj->SaveAs("PNG/PRESENTATION_AJ.png","RECREATE");
}
