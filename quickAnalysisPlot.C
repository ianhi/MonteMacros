
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>

void quickAnalysisPlot(){


  TH1::SetDefaultSumw2();
  TFile *f = new TFile("quickPlot.root");
  TH1D* ha_Aj = (TH1D*)f->Get("ha_Aj");
  TH1D* ha_Phi = (TH1D*)f->Get("ha_Phi");
  TH1D* ha_R = (TH1D*)f->Get("ha_R");
  TProfile * ha_Jr = (TProfile*)f->Get("ha_Jr");  
  
  TCanvas *cAj = new TCanvas("cAj","",600,600);
  int na_Aj = ha_Aj->GetEntries();  ha_Aj->Scale(1./na_Aj);
  ha_Aj->SetMaximum(0.3);
  TH2D *h0_Aj = new TH2D("h0_Aj","",20,0,1,200,0,0.4);
  
  h0_Aj->SetXTitle("A_{J}");
  h0_Aj->SetYTitle("Event Fraction");
  h0_Aj->GetYaxis()->SetTitleOffset(1.5);
  h0_Aj->Draw();
  ha_Aj->Draw("same");
  cAj->SaveAs("Tchanged_Aj.png","RECREATE");

  TCanvas *cPhi = new TCanvas("cPhi","",600,600);
  cPhi->cd();
  int na_Phi=ha_Phi->GetEntries(); ha_Phi->Scale(1./na_Phi);
  TH2D *h0_Phi = new TH2D("h0_Phi","",20,3.14159/2,3.1416,2000,0,1);
  cPhi->SetLogy();
  h0_Phi->SetXTitle("#Delta#phi");
  h0_Phi->SetYTitle("Event Fraction");
  h0_Phi->GetYaxis()->SetTitleOffset(1.5);
  h0_Phi->Draw();
  ha_Phi->Draw("same");
  cPhi->SaveAs("Tchanged_Phi.png","RECREATE");

  TCanvas *cR = new  TCanvas("cR","",600,600);
  cR->cd();
  TH2D *h0_R = new TH2D("h0_R","",10,100,200,2000,0,2);
  h0_R->SetXTitle("Jet p_{T} (GeV/c)");
  h0_R->SetYTitle("R_{AA}");
  h0_R->Draw();
  ha_R ->Draw("hist same");
  cR->SaveAs("Tchanged_R.png","RECREATE");


  TCanvas *cJr = new TCanvas("cJr","",600,600); 
  cJr->cd();
  TH2D *h0_Jr = new TH2D("h0_Jr","",10,100,200,2000,0,1.5);
  h0_Jr->SetXTitle("Leading Jet p_{T} (GeV/c)");
  h0_Jr->SetYTitle("3-Jet / 2-Jet ratio");
  h0_Jr->Draw();
  ha_Jr->Draw("same");
  cJr->SaveAs("Tchanged_Jr.png","RECREATE");  



}
