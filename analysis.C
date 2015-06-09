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

  TTree *ta = (TTree*)a->Get("dijet/nt");
  TTree *tb = (TTree*)b->Get("dijet/nt");
  TTree *tc = (TTree*)c->Get("dijet/nt");

  TFile *f = new TFile("analyzed.root","RECREATE");

  //========================Aj============================//
  TH1D *ha_Aj = new TH1D("ha_Aj","",20,0,1);
  TH1D *hb_Aj = new TH1D("hb_Aj","",20,0,1);
  TH1D *hc_Aj = new TH1D("hc_Aj","",20,0,1);

  ta->Draw("(pt1-pt2)/(pt1+pt2)>>ha_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  tb->Draw("(pt1-pt2)/(pt1+pt2)>>hb_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");
  tc->Draw("(pt1-pt2)/(pt1+pt2)>>hc_Aj","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159","goff");

  //=========================Delta Phi====================================
  TH1D *ha_Phi = new TH1D("ha_Phi","",20,3.14159/2,3.1416);
  TH1D *hb_Phi = new TH1D("hb_Phi","",20,3.14159/2,3.1416);
  TH1D *hc_Phi = new TH1D("hc_Phi","",20,3.14159/2,3.1416);

  ta->Draw("acos(cos(dphi))>>ha_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
  tb->Draw("acos(cos(dphi))>>hb_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");
  tc->Draw("acos(cos(dphi))>>hc_Phi","pt1>100&&pt2>30&&acos(cos(dphi))>0.5*3.14159","goff");

  //=============================JET RATIO ====================//
  TTree *taT = (TTree*)a->Get("dijet/t");
  TTree *tbT = (TTree*)b->Get("dijet/t");
  TTree *tcT = (TTree*)c->Get("dijet/t");
  
  TProfile *ha_Jr = new TProfile("ha_Jr","",10,100,200);
  TProfile *hb_Jr = new TProfile("hb_Jr","",10,100,200);
  TProfile *hc_Jr = new TProfile("hc_Jr","",10,100,200);

  taT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>ha_Jr","Sum$(jtpt>30)>1","goff");
  tbT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hb_Jr","Sum$(jtpt>30)>1","goff");
  tcT->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hc_Jr","Sum$(jtpt>30)>1","goff");
  
  //=========================RAA=================================//
  TCanvas *c1 = new TCanvas("c1","",600,600);
  c1->cd();
   
  TH2D *h0_R = new TH2D("h0_R","",20,100,300,2000,0,2);
  TH1D *ha_R = new TH1D("ha_R","",20,100,300);
  TH1D *hb_R = new TH1D("hb_R","",20,100,300);
  TH1D *hc_R = new TH1D("hc_R","",20,100,300);
 
  taT->Draw("jtpt>>ha_R","");
  tbT->Draw("jtpt>>hb_R","");
  tcT->Draw("jtpt>>hc_R","");
 
  hb_R->SetMarkerColor(2);
  hb_R->SetLineColor(2);
  hc_R->SetMarkerColor(4);
  hc_R->SetLineColor(4);
  ha_R->SetMaximum(0.3);
 
  hb_R->SetMarkerStyle(2);
  hb_R->SetMarkerStyle(20);
  hc_R->SetMarkerStyle(2);
  hc_R->SetMarkerStyle(20);
 
  h0_R->SetXTitle("Jet p_{T} (GeV/c)");
  h0_R->SetYTitle("R_{AA}");

  ha_R->Sumw2();
  hb_R->Sumw2();
  hc_R->Sumw2();
 
  ha_R->Scale(1./taT->GetEntries());
  hb_R->Scale(1./tbT->GetEntries());
  hc_R->Scale(1./tcT->GetEntries());

  h0_R->Draw("hist");
  hb_R->Divide(ha_R);
  hc_R->Divide(ha_R);
  ha_R->Divide(ha_R);

  ha_R->Draw("hist same");
  hb_R->Draw("hist c same");
  hc_R->Draw("hist c same");
  hb_R->Draw("same");
  hc_R->Draw("same");
  

 /*   TH1D *ha_R = new TH1D("ha_R","",20,100,300);
   TH1D *hb_R = new TH1D("hb_R","",20,100,300);
   TH1D *hc_R = new TH1D("hc_R","",20,100,300);

   taT->Draw("jtpt>>ha_R","","goff");
   tbT->Draw("jtpt>>hb_R","","goff");
   tcT->Draw("jtpt>>hc_R","","goff");

   ha_R->Scale(1./taT->GetEntries());
   hb_R->Scale(1./tbT->GetEntries());
   hc_R->Scale(1./tcT->GetEntries());
   
   ha_R->Divide(ha_R);
   hb_R->Divide(ha_R);
   hc_R->Divide(ha_R);
  */
   f->Write();
}
