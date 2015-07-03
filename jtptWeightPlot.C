
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>

void jtptWeightPlot(){
  bool bQjtpt=true;
  bool bSjtpt=true;
  bool bhQpthat=true;
  bool bhSpthat=true;
  bool bhpthat=true;

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


}
