
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
void jtptWeightPlot(){
  bool bQjtpt=false;//jtpt weighted by QCD xs only
  bool bSjtpt=false;//jtpt weighted by sum of xs
  bool bhQpthat=false;//weighted by QCD xs only pthat
  bool bhSpthat=false;//weighted by sum of xs pthat spectra
  bool bhpthat=false;//unweighted pthat spectra
  bool bJetRatio=true;//3 jet event to 2 jet event ratio
  bool bNref=true; // histogram of nref
  bool bNJetRatio=true; //jet ratio using nref
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  TFile *f = TFile::Open(Form("weights.root"));
  if(bQjtpt){
    TH1D * Qjtpt = (TH1D*)f->Get("Qjtpt");
    TCanvas * cQj = new TCanvas("cQj","",600,600);
    cQj->cd();
    cQj->SetLogy();
    Qjtpt->Draw();
    cQj->SaveAs("QCD_Weight_jtpt.png","RECREATE");
  }
  if(bSjtpt){
    TH1D * Sjtpt = (TH1D*)f->Get("Sjtpt");
    TCanvas * cSj = new TCanvas("cSj","",600,600);
    cSj->cd();
    cSj->SetLogy();
    Sjtpt->Draw();    
    cSj->SaveAs("SUM_Weight_jtpt.png","RECREATE");
  }
  if(bhQpthat){
    TH1D * hQpthat = (TH1D*)f->Get("hQpthat");
    TCanvas * cQp = new TCanvas("cQp","",600,600);
    cQp->cd();
    cQp->SetLogy();
    hQpthat->Draw();
    cQp->SaveAs("pthat_QCD_Weight.png","RECREATE");
  }
  if(bhSpthat){
    TH1D * hSpthat = (TH1D*)f->Get("hSpthat");
    TCanvas * cSp = new TCanvas("cSp","",600,600);
    cSp->cd();
    cSp->SetLogy();
    hSpthat->Draw();
    cSp->SaveAs("pthat_SUM_Weight.png","RECREATE");
  }
  if(bhpthat){
    TH1D * hpthat = (TH1D*)f->Get("hpthat");
    TCanvas * cp = new TCanvas("cp","",600,600);
    cp->cd();
    cp->SetLogy();
    hpthat->Draw();
    cp->SaveAs("pthat_NO_Weight.png","RECREATE");
  }
  if(bJetRatio){
    TH1D * Jet2 = (TH1D*)f->Get("Jet2");
    TH1D * Jet3 = (TH1D*)f->Get("Jet3");
    TCanvas * cJR = new TCanvas("cJR","",600,600);
    cJR->cd();
    TH1D * ratio = new TH1D("ratio","3-Jet Events /2-Jet Events Ratio",100,0,500);
    ratio->Add(Jet3);
    ratio->Divide(Jet2);
    ratio->Draw();
    cJR->SaveAs("JR_SUM_Weight.png","RECREATE");
  }
  if(bNJetRatio){
    TH1D * nJet2 = (TH1D*)f->Get("Jet2");
    TH1D * nJet3 = (TH1D*)f->Get("Jet3");
    TCanvas * cnJR = new TCanvas("cnJR","",600,600);
    cnJR->cd();
    TH1D * Nratio = new TH1D("Nratio","NREF 3-Jet Events /2-Jet Events Ratio",100,0,500);
    Nratio->Add(nJet3);
    Nratio->Divide(nJet2);
    Nratio->Draw();
    cnJR->SaveAs("NREF_JR_SUM_Weight.png","RECREATE");
  }
  if(bNref){
    TH1D * Hnref = (TH1D*)f->Get("Hnref");
    TCanvas * cNR = new TCanvas("cNR","",600,600);
    cNR->cd();
    Hnref->Scale(1./Hnref->GetEntries());
    Hnref->SetXTitle("nref");
    Hnref->SetYTitle("Event Fraction");
    Hnref->GetYaxis()->SetTitleOffset(1.5);
    Hnref->Draw();
    cNR->SaveAs("NREF.png","RECREATE");
  }

}
