
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>

void quickAnalysis(){

  TH1::SetDefaultSumw2();

  TFile *a = new TFile("TCHANged_numEvent500.root");//!
  TFile *Pythia = new TFile("PythiaZ2_numEvent1000.root");//!
  TTree *ta = (TTree*)a->Get("dijet/nt");
  TTree *taT = (TTree*)a->Get("dijet/t");
  TTree *tPythia = (TTree*)Pythia->Get("dijet/t");
    TFile *f = new TFile("quickPlot.root","RECREATE");
  TH1D *ha_Aj = new TH1D("ha_Aj","",20,0,1);
  ta->Draw("(pt1-pt2)/(pt1+pt2)>>ha_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  TH1D *ha_Phi = new TH1D("ha_Phi","",20,3.14159/2,3.1416);
  ta->Draw("acos(cos(dphi))>>ha_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

  TProfile *ha_Jr = new TProfile("ha_Jr","",10,100,200);
  taT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>ha_Jr","Sum$(jtpt>30)>1","goff");
  TH1D *ha_R = new TH1D("ha_R","",20,100,300);
  TH1D *hPythia_R = new TH1D("hPythia_R","",20,100,300);
  taT->Draw("jtpt>>ha_R","","goff");

  tPythia->Draw("jtpt>>hPythia_R","","goff");
  hPythia_R->Scale(1./tPythia->GetEntries());

  ha_R->Scale(1./taT->GetEntries());
  ha_R->Divide(hPythia_R);
  f->Write();
}
