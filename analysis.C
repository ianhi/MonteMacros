/*
  Creates histograms from the output of the montecarlo generators and saves to a .root file. Original code written by Yen-jie Lee https://github.com/yenjie/HIGenerator/tree/master/genAna/macros

  To plot run ______.C

*/

#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>

void analysis(){

  TH1::SetDefaultSumw2();

  TFile *a = new TFile("PythiaZ2Star10000.root");//!
  TFile *b = new TFile("PyquenWide10000.root");//!
  TFile *c = new TFile("Pyquen10000.root");//!
  TFile *d = new TFile("QPythia10000.root");//!

  TTree *ta = (TTree*)a->Get("dijet/nt");
  TTree *tb = (TTree*)b->Get("dijet/nt");
  TTree *tc = (TTree*)c->Get("dijet/nt");
  TTree *td = (TTree*)c->Get("dijet/nt");

  TFile *f = new TFile("analyzed.root","RECREATE");

  //========================Aj============================//
  TH1D *ha_Aj = new TH1D("ha_Aj","",20,0,1);
  TH1D *hb_Aj = new TH1D("hb_Aj","",20,0,1);
  TH1D *hc_Aj = new TH1D("hc_Aj","",20,0,1);
  TH1D *hd_Aj = new TH1D("hd_Aj","",20,0,1);
  ta->Draw("(pt1-pt2)/(pt1+pt2)>>ha_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  tb->Draw("(pt1-pt2)/(pt1+pt2)>>hb_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  tc->Draw("(pt1-pt2)/(pt1+pt2)>>hc_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  td->Draw("(pt1-pt2)/(pt1+pt2)>>hd_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  //=========================Delta Phi====================================
  TH1D *ha_Phi = new TH1D("ha_Phi","",20,3.14159/2,3.1416);
  TH1D *hb_Phi = new TH1D("hb_Phi","",20,3.14159/2,3.1416);
  TH1D *hc_Phi = new TH1D("hc_Phi","",20,3.14159/2,3.1416);
  TH1D *hd_Phi = new TH1D("hd_Phi","",20,3.14159/2,3.1416);

  ta->Draw("acos(cos(dphi))>>ha_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
  tb->Draw("acos(cos(dphi))>>hb_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
  tc->Draw("acos(cos(dphi))>>hc_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
  td->Draw("acos(cos(dphi))>>hd_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

  //=============================JET RATIO ====================//
  TTree *taT = (TTree*)a->Get("dijet/t");
  TTree *tbT = (TTree*)b->Get("dijet/t");
  TTree *tcT = (TTree*)c->Get("dijet/t");
  TTree *tdT = (TTree*)d->Get("dijet/t");
  
  TProfile *ha_Jr = new TProfile("ha_Jr","",10,100,200);
  TProfile *hb_Jr = new TProfile("hb_Jr","",10,100,200);
  TProfile *hc_Jr = new TProfile("hc_Jr","",10,100,200);
  TProfile *hd_Jr = new TProfile("hd_Jr","",10,100,200);

  taT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>ha_Jr","Sum$(jtpt>30)>1","goff");
  tbT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hb_Jr","Sum$(jtpt>30)>1","goff");
  tcT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hc_Jr","Sum$(jtpt>30)>1","goff");
  tdT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hd_Jr","Sum$(jtpt>30)>1","goff");
  
  //=========================RAA=================================//
  TH1D *ha_R = new TH1D("ha_R","",20,100,300);
  TH1D *hb_R = new TH1D("hb_R","",20,100,300);
  TH1D *hc_R = new TH1D("hc_R","",20,100,300);
  TH1D *hd_R = new TH1D("hd_R","",20,100,300);
 
  taT->Draw("jtpt>>ha_R","");
  tbT->Draw("jtpt>>hb_R","");
  tcT->Draw("jtpt>>hc_R","");
  tdT->Draw("jtpt>>hd_R","");
 
  ha_R->Sumw2();
  hb_R->Sumw2();
  hc_R->Sumw2();
  hd_R->Sumw2();

  ha_R->Scale(1./taT->GetEntries());
  hb_R->Scale(1./tbT->GetEntries());
  hc_R->Scale(1./tcT->GetEntries());
  hd_R->Scale(1./tdT->GetEntries());
  
  hb_R->Divide(ha_R);
  hc_R->Divide(ha_R);
  ha_R->Divide(ha_R);
  hd_R->Divide(ha_R);

  f->Write();
}
