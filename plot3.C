#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TProfile.h>
#include <TH2D.h>

void plot3() {
  TFile *a = new TFile("PythiaZ2Star10000.root");
  TFile *b = new TFile("PyquenWide10000.root");
  TFile *c = new TFile("Pyquen10000.root");
  
  TTree *ta = (TTree*)a->Get("dijet/t");
  TTree *tb = (TTree*)b->Get("dijet/t");
  TTree *tc = (TTree*)c->Get("dijet/t");

  TCanvas *c1 = new TCanvas("c1","",600,600);
   
  TH2D *h0 = new TH2D("h0","",10,100,200,2000,0,1.5);
  TProfile *ha = new TProfile("ha","",10,100,200);
  TProfile *hb = new TProfile("hb","",10,100,200);
  TProfile *hc = new TProfile("hc","",10,100,200);

  ta->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>ha","Sum$(jtpt>30)>1");
  tb->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hb","Sum$(jtpt>30)>1");
  tc->Draw("Sum$(jtpt>30)>2:Max$(jtpt)>>hc","Sum$(jtpt>30)>1");


  hb->SetMarkerColor(2);
  hb->SetLineColor(2);
  hc->SetMarkerColor(4);
  hc->SetLineColor(4);
   
  ha->Draw();
  hb->SetMarkerStyle(2);
  hb->SetMarkerStyle(20);
  hc->SetMarkerStyle(2);
  hc->SetMarkerStyle(20);
   
  h0->SetXTitle("Leading Jet p_{T} (GeV/c)");
  h0->SetYTitle("3-Jet / 2-Jet ratio");
  gStyle->SetOptStat(0);
  h0->SetAxisRange(0.,1.,"Y");
  h0->GetYaxis()->SetTitleOffset(1.5);
  h0->Draw();
  //   ha->SetFillStyle(3001);
  //   ha->SetFillColor(kGray);
  ha->SetLineWidth(2);
  ha->Draw("hist c same");
  hb->Draw("hist c same");
  hc->Draw("hist c same");

  ha->Draw("same");
  hb->Draw("same");
  hc->Draw("same");

  TLegend *leg = new TLegend(0.4,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();
  leg->AddEntry(ha,"Leading Jet p_{T}> 100 GeV","");
  leg->AddEntry(ha,"Jet p_{T}> 30 GeV","");
  leg->AddEntry(ha,"PYTHIA Z2* GEN","l");
  leg->AddEntry(hb,"JEWEL 0-5% GEN","pl");
  leg->AddEntry(hc,"YAJEM d#bar{d} GEN","pl");


  leg->Draw();
   
}
