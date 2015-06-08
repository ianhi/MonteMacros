#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
void plot() {
  TFile *a = new TFile("PythiaZ2Star10000.root");
  TFile *b = new TFile("PyquenWide10000.root");
  TFile *c = new TFile("Pyquen10000.root");
  
  TTree *ta = (TTree*)a->Get("dijet/nt");
  TTree *tb = (TTree*)b->Get("dijet/nt");
  TTree *tc = (TTree*)c->Get("dijet/nt");


  TCanvas *c1 = new TCanvas("c1","",600,600);

  TH2D *h0 = new TH2D("h0","",20,0,1,200,0,0.4);
  TH1D *ha = new TH1D("ha","",20,0,1);
  TH1D *hb = new TH1D("hb","",20,0,1);
  TH1D *hc = new TH1D("hc","",20,0,1);

  ta->Draw("(pt1-pt2)/(pt1+pt2)>>ha","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159");
  tb->Draw("(pt1-pt2)/(pt1+pt2)>>hb","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159");
  tc->Draw("(pt1-pt2)/(pt1+pt2)>>hc","pt1>100&&pt2>30&&acos(cos(dphi))>2/3.*3.14159");

  hb->SetMarkerColor(2);
  hb->SetLineColor(2);
  hc->SetMarkerColor(4);
  hc->SetLineColor(4);


  ha->SetMaximum(0.3);
  ha->Draw();

  int na=ha->GetEntries();
  ha->Scale(1./na);

  hb->Sumw2();
  int nb=hb->GetEntries();
  hb->Scale(1./nb);
  hb->SetMarkerStyle(2);
  hb->SetMarkerStyle(20);

  hc->Sumw2();
  int nc=hc->GetEntries();
  hc->Scale(1./nc);
  hc->SetMarkerStyle(2);
  hc->SetMarkerStyle(20);

  gStyle->SetOptStat(0);
  h0->SetXTitle("A_{J}");
  h0->SetYTitle("Event Fraction");
  h0->GetYaxis()->SetTitleOffset(1.5);
  h0->Draw();

  ha->SetFillStyle(3001);
  ha->SetFillColor(kGray);

  ha->Draw("same");
  hb->Draw("same");
  hc->Draw("same");

  TLegend *leg = new TLegend(0.4,0.5,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  leg->AddEntry(ha,"p_{T,1} > 100 GeV, p_{T,2} > 30 GeV","");
  leg->AddEntry(ha,"#Delta#phi>2#pi/3","");
  leg->AddEntry(ha,"PYTHIA Z2* GEN","l");

  leg->AddEntry(hb,"PYQUEN wide GEN","pl");

  leg->AddEntry(hc,"PYQUEN  GEN","pl");

  leg->Draw();
}
