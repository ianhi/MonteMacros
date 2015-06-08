/*
  This will plot a histogram of Aj jet assymetry using the outputs of the MC generators.
  Aj = (pt1-pt2)/(pt1+pt2)
  where pt1 is momentum of leading jet and pt2 is momentum of subleading jet
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
Int_t nBins = 100;

int findMin(int min, int two,  int three)
{
  if(two<min){ min=two;}
  if(three<min){ min=three;}
  return min;
  }

void AjMC(){

  THStack *hsA = new THStack("hsA","Stacked A_{J}");

  TFile * file0 = TFile::Open("Pyquen10000.root");
  TFile * file1 = TFile::Open("PythiaZ2Star10000.root");
  TFile * file2 = TFile::Open("PyquenWide10000.root"); 

  //  TCanvas * cA = new TCanvas("c","Aj Comparison",1);
  
  TTree *Tq = (TTree*)file0 -> Get("dijet/t");
  TTree *Tz = (TTree*)file1 -> Get("dijet/t");
  TTree *Tw = (TTree*)file2 -> Get("dijet/t"); 

  TH1F * hQ_A = new TH1F ("hQ_A","",nBins,0,1);  
  TH1F * hZ_A = new TH1F ("hZ_A","PYTHIA Z2 Jet A_{j}",nBins,0,1);  
  TH1F * hW_A = new TH1F ("hW_A","PYQUEN WIDE Jet A_{j}",nBins,0,1);

  hQ_A ->Sumw2();
  hZ_A ->Sumw2();
  hW_A ->Sumw2();
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

    hQ_A ->Fill( (q_pt[0]-q_pt[1]) / (q_pt[0]+q_pt[1]) );
    hZ_A ->Fill( (z_pt[0]-z_pt[1]) / (z_pt[0]+z_pt[1]) );
    hW_A  ->Fill( (w_pt[0]-w_pt[1]) / (w_pt[0]+w_pt[1]) ); 
    
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
  hQ_A ->Scale(1./Nq);
  hZ_A ->Scale(1./Nz);
  hW_A ->Scale(1./Nw);

  hQ_A ->SetLineColor(kRed);
  hZ_A ->SetLineColor(kGreen);
  
  TFile *f=new TFile("testFileSave.root","RECREATE");
  TLegend *legend = new TLegend(.65,.70,.85,.85);
  
  
  legend->AddEntry(hQ_A, "PYQUEN", "p");
  legend->AddEntry(hZ_A, "PYTHIA Z2*", "p");
  legend->AddEntry(hW_A, "PYQUEN WIDE", "p");
 
  //PLOT AS POINTS
  hQ_A ->SetOption("PE");
  hZ_A ->SetOption("PE");
  hW_A ->SetOption("pE");

  hQ_A->GetXaxis()->SetTitle("A_{J}");
  hQ_A->GetYaxis()->SetTitle("Event Fraction");
  hQ_A->GetYaxis()->SetTitleOffset(1.4);
  
  gStyle->SetOptStat(0);


  // FOR PLOTTING FROM THIS MACRO
  // hQ_A ->Draw("P");
  //hZ_A ->Draw("same P");
  //hW_A ->Draw("same p");
  
  
  hQ_A->SetMarkerStyle(20); hQ_A->SetMarkerColor(kBlue); hQ_A->SetMarkerSize(.8);
  hZ_A->SetMarkerStyle(20); hZ_A->SetMarkerColor(kBlack); hZ_A->SetMarkerSize(.8);
  hW_A->SetMarkerStyle(20); hW_A->SetMarkerColor(kGreen); hW_A->SetMarkerSize(.8);

  hsA ->Add(hQ_A);
  hsA ->Add(hZ_A);
  hsA ->Add(hW_A);
  //hsA ->Add(legend);
  hsA ->Write();
  legend->Write();
  //hQ_A ->Write();
  //cA->SaveAs("Aj.pdf","RECREATE");
  f->Write();
}
