// Ian Hunt-Isaak
// Created 26 June 2015

// plot
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>

int aColor =3001;
int bColor = 2;
int cColor = 4;
int dColor = 6; // kGreen +1

void multJewelPlot(){
  bool aj = true;
  bool phi = true;
  bool ratio = true;
  bool raa = true;

  bool med1=true;
  bool med2=false;
  bool med3=false;
  bool med4=false;
  bool med5=false;

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  TFile * f = TFile::Open(Form("med1_histograms_endFile91.root");
  // ==================== Aj ======================//
  if(aj){
    TH2D *h0_Aj = new TH2D("h0_Aj","",20,0,1,200,0,0.4);
    TH1D * med1_Aj = new TH1D
    
    TCanvas *cAj = new TCanvas("cAj","",600,600);



  }

}
