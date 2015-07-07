
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

  bool bJetRatio=true; //jet ratio using nref
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile *f = TFile::Open(Form("pp_weight_2.root"));
 
  if(bJetRatio){
    TH1D * Jet2 = (TH1D*)f->Get("Jet2");
    TH1D * Jet3 = (TH1D*)f->Get("Jet3");
    TCanvas * cJR = new TCanvas("cJR","",600,600);
    cJR->cd();
    TH1D * ratio = new TH1D("ratio","3-Jet Events /2-Jet Events Ratio",100,0,500);
    ratio->Add(Jet3);
    //  ratio->Divide(Jet2);
    ratio->Draw();
    cJR->SaveAs("PP_JR_Weight.png","RECREATE");
  }
}
