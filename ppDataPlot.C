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

void ppDataPlot(){
  bool bDataPT=true;
  bool bDataHT=true;
  bool bDataJT=true;
  int width = 900;
  int height = 600;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile * f = TFile::Open(Form("Data4_added.root"));

  if (bDataPT){
    TH1D * Jet2_pT_Data = (TH1D*)f->Get("Jet2_pT_pp_Data");
    TH1D * Jet3_pT_Data = (TH1D*)f->Get("Jet3_pT_pp_Data");

    TCanvas * cPT_Data = new TCanvas("cPT_Data","",width,height);
    cPT_Data->cd();
    TH1D * ratio_pT_Data = new TH1D("ratio_pT_Data","Data PT pp 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)",100,0,1000);
    ratio_pT_Data->Add(Jet3_pT_Data);
    ratio_pT_Data->Divide(Jet2_pT_Data);
    ratio_pT_Data->SetYTitle("R_{32}");
    ratio_pT_Data->SetAxisRange(0.000000001, 1.2, "Y");
    ratio_pT_Data->Draw();
    cPT_Data->SaveAs("PNG/PP_JR_PT_Data.png","RECREATE");

  }
  if(bDataHT){

    TH1D * Jet2_hT_Data = (TH1D*)f->Get("Jet2_hT_pp_Data");
    TH1D * Jet3_hT_Data = (TH1D*)f->Get("Jet3_hT_pp_Data");

    TCanvas * cHT_Data = new TCanvas("cHT_Data","",width,height);
    cHT_Data->cd();
    TH1D * ratio_hT_Data = new TH1D("ratio_hT_Data","Data HT pp 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)",100,0,1000);
    ratio_hT_Data->Add(Jet3_hT_Data);
    ratio_hT_Data->Divide(Jet2_hT_Data);
    ratio_hT_Data->SetYTitle("R_{32}");
    ratio_hT_Data->SetAxisRange(0.000000001, 1.2, "Y");
    ratio_hT_Data->Draw();
    cHT_Data->SaveAs("PNG/PP_JR_HT_Data.png","RECREATE");
  }
  if(bDataJT){

    TH1D * jtpt_pp_Data = (TH1D*)f->Get("jtpt_pp_Data");

    TCanvas * cJT_Data = new TCanvas("cJT_Data","",width,height);
    cJT_Data->cd();
    cJT_Data->SetLogy();
    jtpt_pp_Data->Draw();
    cJT_Data->SaveAs("PNG/PP_JTPT_Data.png","RECREATE");
  }
  f->Close();

}
