
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>

void plotAnalysis(){
  bool aj = false;
  bool phi = false;
  bool ratio = false;
  bool raa = true;

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  TFile *f = TFile::Open(Form("analyzed.root"));

  // ==================== Aj ======================//
  if(aj){
    TH2D *h0_Aj = new TH2D("h0_Aj","",20,0,1,200,0,0.4);
    TH1D *ha_Aj = (TH1D*)f->Get("ha_Aj");
    TH1D *hb_Aj = (TH1D*)f->Get("hb_Aj");
    TH1D *hc_Aj = (TH1D*)f->Get("hc_Aj");

    TCanvas *cAj = new TCanvas("cAj","",600,600);
    cAj ->cd();

    hb_Aj->SetMarkerColor(2);
    hb_Aj->SetLineColor(2);
    hc_Aj->SetMarkerColor(4);
    hc_Aj->SetLineColor(4);
    ha_Aj->SetMaximum(0.3);

    int na = ha_Aj->GetEntries();  ha_Aj->Scale(1./na);
    int nb = hb_Aj->GetEntries();  hb_Aj->Scale(1./nb);
    int nc = hc_Aj->GetEntries();  hc_Aj->Scale(1./nc);

    hb_Aj->SetMarkerStyle(2);
    hb_Aj->SetMarkerStyle(20);
    hc_Aj->SetMarkerStyle(2);
    hc_Aj->SetMarkerStyle(20);

    //h0===========
    h0_Aj->SetXTitle("A_{J}");
    h0_Aj->SetYTitle("Event Fraction");
    h0_Aj->GetYaxis()->SetTitleOffset(1.5);
    h0_Aj->Draw();

    ha_Aj->SetFillStyle(3001);
    ha_Aj->SetFillColor(kGray);

    ha_Aj->Draw("same HIST");
    hb_Aj->Draw("same");
    hc_Aj->Draw("same");

    TLegend *leg_Aj = new TLegend(0.4,0.5,0.9,0.9);
    leg_Aj->SetFillStyle(0);
    leg_Aj->SetBorderSize(0);
    leg_Aj->AddEntry(ha_Aj,"p_{T,1} > 100 GeV, p_{T,2} > 30 GeV","");
    leg_Aj->AddEntry(ha_Aj,"#Delta#phi>2#pi/3","");
    leg_Aj->AddEntry(ha_Aj,"PYTHIA Z2* GEN","l");
    leg_Aj->AddEntry(hb_Aj,"PYQUEN wide GEN","pl");
    leg_Aj->AddEntry(hc_Aj,"PYQUEN  GEN","pl");

    leg_Aj->Draw();
  }  

  //==================PLOT PHI ==================//
  if(phi){
    TCanvas *cPhi = new TCanvas("cPhi","",600,600);
    cPhi->cd();
    TH2D *h0_Phi = new TH2D("h0_Phi","",20,3.14159/2,3.1416,2000,0,1);
    TH1D *ha_Phi = (TH1D*)f->Get("ha_Phi");
    TH1D *hb_Phi = (TH1D*)f->Get("hb_Phi");
    TH1D *hc_Phi = (TH1D*)f->Get("hc_Phi");

    ha_Phi->SetMaximum(0.3);
    ha_Phi->SetFillStyle(3001);
    ha_Phi->SetFillColor(kGray);

    hb_Phi->SetMarkerColor(2);
    hb_Phi->SetLineColor(2);
    hb_Phi->SetMarkerStyle(2);
    hb_Phi->SetMarkerStyle(20);

    hc_Phi->SetMarkerColor(4);
    hc_Phi->SetLineColor(4);
    hc_Phi->SetMarkerStyle(2);
    hc_Phi->SetMarkerStyle(20);
  
    h0_Phi->SetXTitle("#Delta#phi");
    h0_Phi->SetYTitle("Event Fraction");
    h0_Phi->GetYaxis()->SetTitleOffset(1.5);
    h0_Phi->Draw();

    cPhi->SetLogy();

    ha_Phi->Draw("same HIST");
    hb_Phi->Draw("same");
    hc_Phi->Draw("same");

    TLegend *leg_Phi = new TLegend(0.4,0.5,0.9,0.9);
    leg_Phi->SetFillStyle(0);
    leg_Phi->SetBorderSize(0);

    leg_Phi->AddEntry(ha_Phi,"p_{T,1} > 100 GeV, p_{T,2} > 30 GeV","");
    leg_Phi->AddEntry(ha_Phi,"#Delta#phi>2#pi/3","");
    leg_Phi->AddEntry(ha_Phi,"PYTHIA Z2* GEN","l");
    leg_Phi->AddEntry(hb_Phi,"PYQUEN wide GEN","pl");
    leg_Phi->AddEntry(hc_Phi,"PYQUEN  GEN","pl");

    leg_Phi->Draw();
  }
  //=======================JET RAIO=================
  if(ratio){
    TCanvas *cJr = new TCanvas("cJr","",600,600); 
    cJr->cd();

    TH2D *h0_Jr = new TH2D("h0_Jr","",10,100,200,2000,0,1.5);
    TProfile *ha_Jr = (TProfile*)f->Get("ha_Jr");
    TProfile *hb_Jr = (TProfile*)f->Get("hb_Jr");
    TProfile *hc_Jr = (TProfile*)f->Get("hc_Jr");
    hb_Jr->SetMarkerColor(2);
    hb_Jr->SetLineColor(2);
    hc_Jr->SetMarkerColor(4);
    hc_Jr->SetLineColor(4);
   
    hb_Jr->SetMarkerStyle(2);
    hb_Jr->SetMarkerStyle(20);
    hc_Jr->SetMarkerStyle(2);
    hc_Jr->SetMarkerStyle(20);
   
    h0_Jr->SetXTitle("Leading Jet p_{T} (GeV/c)");
    h0_Jr->SetYTitle("3-Jet / 2-Jet ratio");

    h0_Jr->SetAxisRange(0.,1.,"Y");
    h0_Jr->GetYaxis()->SetTitleOffset(1.5);
    h0_Jr->Draw();

    ha_Jr->SetLineWidth(2);
    ha_Jr->Draw("hist cP same");
    hb_Jr->Draw("hist cP same");
    hc_Jr->Draw("hist cP same");
    
    ha_Jr->Draw("same");
    hb_Jr->Draw("same");
    hc_Jr->Draw("same");
    
    TLegend *leg_Jr = new TLegend(0.4,0.6,0.9,0.9);
    leg_Jr->SetFillStyle(0);
    leg_Jr->SetBorderSize(0);
    leg_Jr->Draw();
    leg_Jr->AddEntry(ha_Jr,"Leading Jet p_{T}> 100 GeV","");
    leg_Jr->AddEntry(ha_Jr,"Jet p_{T}> 30 GeV","");
    leg_Jr->AddEntry(ha_Jr,"PYTHIA Z2* GEN","l");
    leg_Jr->AddEntry(hb_Jr,"JEWEL 0-5% GEN","pl");
    leg_Jr->AddEntry(hc_Jr,"YAJEM d#bar{d} GEN","pl");
    leg_Jr->Draw();
  }

  //==========================RAA========================//
  if(raa){
    TCanvas *cR = new  TCanvas("cR","",600,600);
    cR->cd();

    TH2D *h0_R = new TH2D("h0_R","",10,100,200,2000,0,2);
    TH1D *ha_R = (TH1D*)f->Get("ha_R");
    TH1D *hb_R = (TH1D*)f->Get("hb_R");
    TH1D *hc_R = (TH1D*)f->Get("hc_R");

    ha_R->Sumw2();
    h0_R ->Draw();
    ha_R ->Draw("hist same");
    
    hb_R->SetMarkerColor(2);
    hb_R->SetLineColor(2);
    hc_R->SetMarkerColor(4);
    hc_R->SetLineColor(4);
  
    hb_R->SetMarkerStyle(2);
    hb_R->SetMarkerStyle(20);
    hc_R->SetMarkerStyle(2);
    hc_R->SetMarkerStyle(20);
    
    h0_R->SetXTitle("Jet p_{T} (GeV/c)");
    h0_R->SetYTitle("R_{AA}");
    
    ha_R->Sumw2();
    hb_R->Sumw2();
    hc_R->Sumw2();
   
    ha_R->Draw("hist same");
    
    hb_R->Draw("hist c same");
    hc_R->Draw("hist c same");
    hb_R->Draw("same");
    hc_R->Draw("same");
 
    TLegend *leg_R = new TLegend(0.55,0.7,0.9,0.9);
    leg_R->SetFillStyle(0);
    leg_R->SetBorderSize(0);
    leg_R->Draw();
    leg_R->AddEntry(ha_R,"PYTHIA Z2* GEN","l");
    leg_R->AddEntry(hb_R,"PYQUEN wide GEN","pl");
    leg_R->AddEntry(hc_R,"PYQUEN GEN","pl");
    leg_R->Draw();
    
  }
}
