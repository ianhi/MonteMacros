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

Float_t jtpt[1000];
Int_t nref;
void jtptWeight(){
  bool DEBUG=true;
  bool DEBUGLONG=false;//true -> much longer runtime

  double pthatBinning[] = {15,30,50,80,120,170,220,280,330,400,460,540};
  //                0           1           2      3       4           5       6  7       8        9          10
  double xsQCD[] = {4878812.4,4218696.2,4659866.4,4049616,2934218.1,1695768.4,-1,718081.6,578537.1,291444.26,168207.79}; //-1 is for run six
  double xsSUM[]={286240,   444780,     494830,  514200,  554520,   482280,    -1,309090,304490,173850,114700};

  double * xsQ=xsQCD;
  double * xsS=xsSUM;
  double *pthats = pthatBinning;

  TChain* tChain;
  TChain* ntChain;
  TFile* outf;
  tChain = new TChain("dijet/t");
  ntChain = new TChain("dijet/nt");
  // Order of files matters a lot!  
  tChain->AddFile("../outputs/0_numEvents25000/med1_15_30_JewelDijet_0_numEvent25000.root");
  cout<<"0 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/1_numEvents25000/med1_30_50_JewelDijet_1_numEvent25000.root");
  cout<<"1 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/2_numEvents25000/med1_50_80_JewelDijet_2_numEvent25000.root");
  cout<<"2 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/3_numEvents25000/med1_80_120_JewelDijet_3_numEvent25000.root");
  cout<<"3 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/4_numEvents25000/med1_120_170_JewelDijet_4_numEvent25000.root");
  cout<<"4 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/5_numEvents25000/med1_170_220_JewelDijet_5_numEvent25000.root");
  cout<<"5 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/7_numEvents25000/med1_280_330_JewelDijet_7_numEvent25000.root");
  cout<<"7 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/8_numEvents25000/med1_330_400_JewelDijet_8_numEvent25000.root");
  cout<<"8 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/9_numEvents25000/med1_400_460_JewelDijet_9_numEvent25000.root");
  cout<<"9 events: "<<tChain->GetEntries()<<endl;
  tChain->AddFile("../outputs/10_numEvents25000/med1_460_540_JewelDijet_10_numEvent25000.root");
  cout<<"10 events: "<<tChain->GetEntries()<<endl;

  ntChain->AddFile("../outputs/0_numEvents25000/med1_15_30_JewelDijet_0_numEvent25000.root");
  ntChain->AddFile("../outputs/1_numEvents25000/med1_30_50_JewelDijet_1_numEvent25000.root");
  ntChain->AddFile("../outputs/2_numEvents25000/med1_50_80_JewelDijet_2_numEvent25000.root");
  ntChain->AddFile("../outputs/3_numEvents25000/med1_80_120_JewelDijet_3_numEvent25000.root");
  ntChain->AddFile("../outputs/4_numEvents25000/med1_120_170_JewelDijet_4_numEvent25000.root");
  ntChain->AddFile("../outputs/5_numEvents25000/med1_170_220_JewelDijet_5_numEvent25000.root");
  ntChain->AddFile("../outputs/7_numEvents25000/med1_280_330_JewelDijet_7_numEvent25000.root");
  ntChain->AddFile("../outputs/8_numEvents25000/med1_330_400_JewelDijet_8_numEvent25000.root");
  ntChain->AddFile("../outputs/9_numEvents25000/med1_400_460_JewelDijet_9_numEvent25000.root");
  ntChain->AddFile("../outputs/10_numEvents25000/med1_460_540_JewelDijet_10_numEvent25000.root");

  tChain->AddFriend(ntChain);
  outf = new TFile(Form("weights.root"),"recreate");
  TH1D * Qjtpt = new TH1D("Qjtpt","weighted by QCD counts;jtpt",20,0,460);
  TH1D * Sjtpt = new TH1D("Sjtpt","weighted by SUM counts;jtpt",20,0,460);
  TH1D * hQpthat = new TH1D("hQpthat","weighted by QCD count;pthat",500,0,500);
  TH1D * hSpthat = new TH1D("hSpthat","weighted by SUM counts;pthat",500,0,500);
  TH1D * hpthat = new TH1D("hpthat","not weighted counts;pthat",500,0,500);
  
  double pthatweightQ = 0;//weight for just QCD xs
  double pthatweightS = 0;//weight for just SUM xs
  int nev[20];
  int n[20];
  int Npt = 11;

  if(DEBUG) cout<<"total number of events = "<<ntChain->GetEntries()<<endl;
  
  for(int i = 0; i < Npt; ++i){//fill n[i] loop
    if(i==6) continue;
    TCut pthatCut(Form("pthat >= %f && pthat < %f",pthats[i],pthats[i+1]));
    n[i] = tChain->GetEntries(pthatCut);
    if(DEBUG){
      cout<<"In fill n[i] loop iteration: "<<i<<"\n";
      cout<<"pthat low/high:  "<<pthats[i]<<"  "<<pthats[i+1]<<endl;
      cout<<"n[i]: "<<n[i]<<"\n\n";
    }
  }
  Float_t varpthat;
  
  ntChain->SetBranchAddress("pthat",&varpthat);
  tChain->SetBranchAddress("jtpt",jtpt);
  tChain->SetBranchAddress("nref",&nref);
  
  for(int ie = 0; ie < tChain->GetEntries(); ++ie){
    tChain->GetEntry(ie);
    for(int i = 0; i < Npt; ++i){
      if(n[i] > 0 && varpthat >= pthats[i]) {
	pthatweightQ = xsQ[i]/n[i];
	pthatweightS = xsS[i]/n[i];
	if(DEBUGLONG){
	  cout<<"in changing weights\n\n";
	  cout<<"Q weight:  "<<pthatweightQ<<endl;
	  cout<<"S weight:  "<<pthatweightS<<endl;
	}
      }
      /*cout<<jtpt[0]<<"   jtpt[0]\n\n";
      cout<<pthatweightQ<<" weight Q\n\n";
      */
      hQpthat->Fill(varpthat,pthatweightQ);
      hSpthat->Fill(varpthat,pthatweightS);
      hpthat->Fill(varpthat);
      for(int i = 0; i <= nref; ++i){//loop through the events in a jet
	Qjtpt->Fill(jtpt[i],pthatweightQ);
	Sjtpt->Fill(jtpt[i],pthatweightS); 
      }
    }
  }
  TCanvas * c = new TCanvas("c","",600,600);
  c->cd();
  c->SetLogy();
  hpthat->Draw();
  TCanvas * cQ = new TCanvas("cQ","",600,600);
  cQ->cd();
  cQ->SetLogy();
  hQpthat->Draw();
  TCanvas * cS = new TCanvas("cS","",600,600);
  cS->cd();
  cS->SetLogy();
  hSpthat->Draw();
  
  outf->cd();
  outf->Write();
  outf->Close();
  
}
