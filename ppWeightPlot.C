
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

  bool bJetRatio=true; //jet ratio 
  bool bNJetRatio=false; //jet ratio using nref
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *f = TFile::Open(Form("ROOT/pp_weight_44.root"));
 
  if(bJetRatio){
    TH1D * Jet2 = (TH1D*)f->Get("Jet2");
    TH1D * Jet3 = (TH1D*)f->Get("Jet3");

    TCanvas * cJR = new TCanvas("cJR","",600,600);
    cJR->cd();
    TH1D * ratio = new TH1D("ratio","pp 3-Jet Events /2-Jet Events Ratio;Leading Jet p_{T}",100,0,500);
    ratio->Add(Jet3);
    ratio->Divide(Jet2);
    ratio->Draw();
    cJR->SaveAs("PNG/PP_JR_Weight.png","RECREATE");
  }

  if(bNJetRatio){
    TH1D * nJet2 = (TH1D*)f->Get("nJet2");
    TH1D * nJet3 = (TH1D*)f->Get("nJet3");
    
    TCanvas * cNJR = new TCanvas("cNJR","",600,600);
    cNJR->cd();
    TH1D * Nratio = new TH1D("Nratio","NREF pp 3-Jet Events /2-Jet Events Ratio;Leading Jet p_{T}",100,0,500);
    Nratio->Add(nJet3);
    Nratio->Divide(nJet2);
    Nratio->Draw();
    cNJR->SaveAs("PNG/NREF_PP_JR_Weight.png","RECREATE");
  }
}
