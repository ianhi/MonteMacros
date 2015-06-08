/*
  This will plot a histogram of delta phi assuming that this is between the leading and subleading jet using the outputs of the MC generators.

q = pyquen
w = pyquen wide
z = pythia z2*

*/
#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "TTree.h"

Float_t q_phi[1000];
Float_t w_phi[1000];
Float_t z_phi[1000];

Int_t q_njets;
Int_t w_njets;
Int_t z_njets;
Int_t nBins = 100;

int findMin(int min, int two,  int three)
{
  if(two<min){ min=two;}
  if(three<min){ min=three;}
  return min;
  }

void dPhi(){


  TFile * file0 = TFile::Open("Pyquen10000.root");
  TFile * file1 = TFile::Open("PythiaZ2Star10000.root");
  TFile * file2 = TFile::Open("PyquenWide10000.root"); 

  TCanvas * cPhi = new TCanvas("cPhi","Delta Phi  Comparison",1);
  
  TTree *Tq = (TTree*)file0 -> Get("dijet/t");
  TTree *Tz = (TTree*)file1 -> Get("dijet/t");
  TTree *Tw = (TTree*)file2 -> Get("dijet/t"); 

  TH1F * hQ_Ph = new TH1F ("hQ_Ph","PYQUEN Jet #delta #phi",nBins,2,3.14);  
  TH1F * hZ_Ph = new TH1F ("hZ_Ph","PYTHIA Z2 Jet #delta #phi",nBins,2,3.14);  
  TH1F * hW_Ph = new TH1F ("hW_Ph","PYQUEN WIDE #delta #phi",nBins,2,3.14);

  Int_t Nq = Tq->GetEntries();
  Int_t Nz = Tz->GetEntries();
  Int_t Nw = Tw->GetEntries();

  Tq ->SetBranchAddress("jtphi",q_phi);
  Tq ->SetBranchAddress("nref",&q_njets);

  Tz ->SetBranchAddress("jtphi",z_phi);
  Tz ->SetBranchAddress("nref",&z_njets);

  Tw  ->SetBranchAddress("jtphi",w_phi);
  Tw  ->SetBranchAddress("nref",&w_njets);

  
  for(int iev = 0; iev < findMin(Nq,Nz,Nw); ++iev){
    Tq ->GetEntry(iev);
    Tz ->GetEntry(iev);
    Tw ->GetEntry(iev);
    if(q_phi[0]-q_phi[1]>2*3.14/3){
      hQ_Ph ->Fill(q_phi[0]-q_phi[1]);
    }
    if(z_phi[0]-z_phi[1]>2*3.14/3){
      hZ_Ph ->Fill(z_phi[0]-z_phi[1]);
    }
    if(w_phi[0]-w_phi[1]>2*3.14/3){
      hW_Ph ->Fill(w_phi[0]-w_phi[1]);
    }
/*
      for(int i=0;i<pyq_njets;++i){
      
      hPyqA ->Fill(pyq_pt[i]);
      }
      for(int i=0;i<pyt_njets;++i){
      hPytA ->Fill(pyt_pt[i]);
      }
      for(int i=0;i<tf_njets;++i){
      hTfA ->Fill(tf_pt[i]);
      }*/
  }
  hQ_Ph ->Scale(1./Nq);
  hZ_Ph ->Scale(1./Nz);
  hW_Ph ->Scale(1./Nw);

  hQ_Ph ->SetLineColor(kRed);
  hZ_Ph ->SetLineColor(kGreen);
  

  TLegend *legend_Ph = new TLegend(.65,.70,.85,.85);
  cPhi -> cd()->SetLogy();
  
  legend_Ph->AddEntry(hQ_Ph, "PYQUEN", "p");
  legend_Ph->AddEntry(hZ_Ph, "PYTHIA Z2*", "p");
  legend_Ph->AddEntry(hW_Ph, "PYQUEN WIDE", "p");
 
  hQ_Ph ->SetOption("PL");
  hZ_Ph ->SetOption("PL");
  hW_Ph ->SetOption("L");

  hQ_Ph->GetXaxis()->SetTitle("#delta #phi");
  hQ_Ph->GetYaxis()->SetTitle("Event Fraction");
  hQ_Ph->GetYaxis()->SetTitleOffset(1.4);
  
  gStyle->SetOptStat(0);

  hQ_Ph ->Draw("PL");
  hZ_Ph ->Draw("same p");
  hW_Ph ->Draw("same p");

  
  hQ_Ph->SetMarkerStyle(20); hQ_Ph->SetMarkerColor(kBlue); hQ_Ph->SetMarkerSize(.8);
  hZ_Ph->SetMarkerStyle(20); hZ_Ph->SetMarkerColor(kBlack); hZ_Ph->SetMarkerSize(.8);
  hW_Ph->SetMarkerStyle(20); hW_Ph->SetMarkerColor(kGreen); hW_Ph->SetMarkerSize(.8);

  /* hsA ->Add(hQ_A);
  hsA ->Add(hZ_A);
  hsA ->Add(hW_A);
  hsA ->Draw("nostack");
  */
  legend_Ph->Draw("SAME");

  cPhi->SaveAs("Phi.pdf","RECREATE");
  
}
