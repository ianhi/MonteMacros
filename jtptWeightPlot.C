
#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TChain.h>
#include <TProfile.h>
#include <TStopwatch.h>
#include <TCut.h>
#include <cstdlib>
#include <cmath>
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLine.h"
#include <stdlib.h>
#include <string>
#include <sstream>
#include <TH1D.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>

void jtptWeightPlot(){
  bool bQjtpt=false;//jtpt weighted by QCD xs only
  bool bSjtpt=false;//jtpt weighted by sum of xs
  bool bhQpthat=false;//weighted by QCD xs only pthat
  bool bhSpthat=true;//weighted by sum of xs pthat spectra
  bool bhpthat=false;//unweighted pthat spectra
  bool bJetRatio_pT=true;//3 jet event to 2 jet event ratio
  bool bJetRatio_hT=true;//3 jet event to 2 jet event ratio

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  std::string prefix="med4_10K";
  std::string filename="ROOT/Jewel/"+prefix+"_weights.root";
  std::string saveName;
  TFile *f = TFile::Open(filename.c_str());
  if(bQjtpt){
    TH1D * Qjtpt = (TH1D*)f->Get("Qjtpt");
    TCanvas * cQj = new TCanvas("cQj","",600,600);
    cQj->cd();
    cQj->SetLogy();
    Qjtpt->Draw();
    saveName="PNG/QCD_Weight_jtpt_"+prefix+".png";
    cQj->SaveAs(saveName.c_str(),"RECREATE");
  }
  if(bSjtpt){
    TH1D * Sjtpt = (TH1D*)f->Get("Sjtpt");
    TCanvas * cSj = new TCanvas("cSj","",600,600);
    cSj->cd();
    cSj->SetLogy();
    Sjtpt->Draw();    
    saveName="PNG/SUM_Weight_jtpt_"+prefix+".png";
    cSj->SaveAs(saveName.c_str(),"RECREATE");
  }
  if(bhQpthat){
    TH1D * hQpthat = (TH1D*)f->Get((prefix+"_hQpthat").c_str());
    TCanvas * cQp = new TCanvas("cQp","",600,600);
    cQp->cd();
    cQp->SetLogy();
    hQpthat->Draw();
    saveName="PNG/pthat_QCD_Weight_"+prefix+".png";
    cQp->SaveAs(saveName.c_str(),"RECREATE");
  }
  if(bhSpthat){
    TH1D * hSpthat = (TH1D*)f->Get((prefix+"_hSpthat").c_str());
    TCanvas * cSp = new TCanvas("cSp","",600,600);
    cSp->cd();
    cSp->SetLogy();
    hSpthat->Draw();
    saveName="PNG/pthat_SUM_Weight_"+prefix+".png";
    cSp->SaveAs(saveName.c_str(),"RECREATE");
  }
  if(bhpthat){
    TH1D * hpthat = (TH1D*)f->Get("hpthat");
    TCanvas * cp = new TCanvas("cp","",600,600);
    cp->cd();
    cp->SetLogy();
    hpthat->Draw();
    saveName="PNG/pthat_NO_Weight_"+prefix+".png";
    cp->SaveAs(saveName.c_str(),"RECREATE");
  }
  if(bJetRatio_pT){
    TH1D * Jet2_pT = (TH1D*)f->Get((prefix+"_Jet2_pT_HI").c_str());
    TH1D * Jet3_pT = (TH1D*)f->Get((prefix+"_Jet3_pT_HI").c_str());
    TCanvas * cJR_pT = new TCanvas("cJR_pT","",600,600);
    cJR_pT->cd();
    TH1D * ratio_pT = new TH1D("ratio_pT",(prefix+" PbPb 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)").c_str(),100,0,500);
    ratio_pT->Add(Jet3_pT);
    ratio_pT->Divide(Jet2_pT);
    ratio_pT->SetMarkerStyle(20);
    ratio_pT->SetMarkerColor(kBlack);
    ratio_pT->SetYTitle("R_{32}");
    ratio_pT->Draw();
    saveName="PNG/JR_pT_"+prefix+".png";
    cJR_pT->SaveAs(saveName.c_str(),"RECREATE");
  }
  if(bJetRatio_hT){
    TH1D * Jet2_hT = (TH1D*)f->Get((prefix+"_Jet2_hT_HI").c_str());
    TH1D * Jet3_hT = (TH1D*)f->Get((prefix+"_Jet3_hT_HI").c_str());
    TCanvas * cJR_hT = new TCanvas("cJR_hT","",600,600);
    cJR_hT->cd();
    TH1D * ratio_hT = new TH1D("ratio_hT",(prefix+" PbPb 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)").c_str(),100,0,500);
    ratio_hT->Add(Jet3_hT);
    ratio_hT->Divide(Jet2_hT);
    ratio_hT->SetMarkerStyle(20);
    ratio_hT->SetMarkerColor(kBlack);
    ratio_hT->SetYTitle("R_{32}");
    ratio_hT->Draw();
    saveName="PNG/JR_hT_"+prefix+".png";
    cJR_hT->SaveAs(saveName.c_str(),"RECREATE");
  }


}
