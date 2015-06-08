/*
  Plots a ratio of 3 jet and 2 jet

  q = pyquen
  w = pyquen wide
  z = pythia z2*

*/
#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "TTree.h"

Float_t q_pt[1000];
Float_t w_pt[1000];
Float_t z_pt[1000];

Int_t q_njets;
Int_t w_njets;
Int_t z_njets;
Int_t nBinsJR = 15;

int findMin(int min, int two,  int three)
{
  if(two<min){ min=two;}
  if(three<min){ min=three;}
  return min;
}
int howMany30(Float_t pt[],Int_t size){
  for(int i=0;i< size;i++){
    if(pt[i] >= 30)
      continue;
    return i;
  } 
}
void jetRatio(){
  TFile *f=new TFile("JetRatio_Histograms.root","UPDATE");
  Float_t test [] = {60,40,20};
  //cout << howMany30(test,3)<<"\n\n\n\n";

  TFile * file0 = TFile::Open("Pyquen10000.root");
  TFile * file1 = TFile::Open("PythiaZ2Star10000.root");
  TFile * file2 = TFile::Open("PyquenWide10000.root"); 

  TCanvas * cRat = new TCanvas("cRat","3 Jet / 2 Jet Ratio",1);
  
  TTree *Tq = (TTree*)file0 -> Get("dijet/t");
  TTree *Tz = (TTree*)file1 -> Get("dijet/t");
  TTree *Tw = (TTree*)file2 -> Get("dijet/t"); 

  TH1F * hQ_JR = new TH1F ("hQ_JR","",nBinsJR,100,300);  
  TH1F * hZ_JR = new TH1F ("hZ_JR","",nBinsJR,100,300);  
  TH1F * hW_JR = new TH1F ("hW_JR","",nBinsJR,100,300);
 

  TH1F * hQ_JR2 = new TH1F ("hQ_JR2","",nBinsJR,100,300);  //! pyquen 2 jet events
  TH1F * hQ_JR3 = new TH1F ("hQ_JR3","",nBinsJR,100,300);  //! pyquen 3 jet events
 
  TH1F * hZ_JR2 = new TH1F ("hZ_JR2","",nBinsJR,100,300);  //! pythia z2* 2 jet events
  TH1F * hZ_JR3 = new TH1F ("hZ_JR3","",nBinsJR,100,300);  //! pythia z2* 3 jet events

  TH1F * hW_JR2 = new TH1F ("hW_JR2","",nBinsJR,100,300); //! pyquen wide 2 jet events
  TH1F * hW_JR3 = new TH1F ("hW_JR3","",nBinsJR,100,300); //! pyquen wide 3 jet events

  Int_t Nq = Tq->GetEntries();
  Int_t Nz = Tz->GetEntries();
  Int_t Nw = Tw->GetEntries();

  Tq ->SetBranchAddress("jtpt",q_pt);
  Tq ->SetBranchAddress("nref",&q_njets);

  Tz ->SetBranchAddress("jtpt",z_pt);
  Tz ->SetBranchAddress("nref",&z_njets);

  Tw  ->SetBranchAddress("jtpt",w_pt);
  Tw  ->SetBranchAddress("nref",&w_njets);

  
  for(int iev = 0; iev < findMin(Nq,Nz,Nw); ++iev){
    Tq ->GetEntry(iev);
    Tz ->GetEntry(iev);
    Tw ->GetEntry(iev);
    // PYQUEN
    if(q_pt[0]>=100 && howMany30(q_pt,q_njets)>=3){
      hQ_JR3 ->Fill(q_pt[0]);
    }
    if(q_pt[0]>=100 && howMany30(q_pt,q_njets)>=2){
      hQ_JR2 ->Fill(q_pt[0]);
    }
    //PYTHIA Z2*
   if(z_pt[0]>=100 && howMany30(z_pt,z_njets)>=3){
      hZ_JR3 ->Fill(z_pt[0]);
    }
    if(q_pt[0]>=100 && howMany30(q_pt,q_njets)>=2){
      hZ_JR2 ->Fill(z_pt[0]);
    }
    //PYQUEN WIDE
   if(w_pt[0]>=100 && howMany30(w_pt,w_njets)>=3){
      hW_JR3 ->Fill(w_pt[0]);
    }
    if(q_pt[0]>=100 && ho wMany30(q_pt,q_njets)>=2){
      hW_JR2 ->Fill(w_pt[0]);
    }
  }
  hQ_JR = hQ_JR3;
  hQ_JR->Divide(hQ_JR2);
  
  hZ_JR = hZ_JR3;
  hZ_JR ->Divide(hQ_JR2);

  hW_JR = hW_JR3;
  hW_JR ->Divide(hW_JR2);

  hQ_JR -> Write();
  hZ_JR -> Write();
  hW_JR -> Write();
  
  hQ_JR ->SetLineColor(kRed);
  hZ_JR ->SetLineColor(kGreen);
  

  TLegend *legend_JR = new TLegend(.75,.70,.95,.85);
  //cRat -> cd()->SetLogy();
  
  legend_JR->AddEntry(hQ_JR, "PYQUEN", "p");
  legend_JR->AddEntry(hZ_JR, "PYTHIA Z2*", "p");
  legend_JR->AddEntry(hW_JR, "PYQUEN WIDE", "p");
 
  hQ_JR ->SetOption("P");
  hZ_JR ->SetOption("P");
  hW_JR ->SetOption("p");

  hQ_JR->GetXaxis()->SetTitle("Leading Jet P_{T} (GeV/c)");
  hQ_JR->GetYaxis()->SetTitle("3-Jet/2-Jet Ratio");
  hQ_JR->GetYaxis()->SetTitleOffset(1.4);
  
  gStyle->SetOptStat(0);

  hQ_JR ->Draw("P");
  hZ_JR ->Draw("same p");
  hW_JR ->Draw("same p");

  
  hQ_JR->SetMarkerStyle(20); hQ_JR->SetMarkerColor(kBlue); hQ_JR->SetMarkerSize(.8);
  hZ_JR->SetMarkerStyle(20); hZ_JR->SetMarkerColor(kBlack); hZ_JR->SetMarkerSize(.8);
  hW_JR->SetMarkerStyle(20); hW_JR->SetMarkerColor(kGreen); hW_JR->SetMarkerSize(.8);

  /* hsA ->Add(hQ_A);
     hsA ->Add(hZ_A);
     hsA ->Add(hW_A);
     hsA ->Draw("nostack");
  */
  legend_JR->Draw("SAME");
  cRat->SaveAs("JetRatio.pdf","RECREATE");*/
  f->Write();
}
