// Created 10 July, 2015
// Ian Hunt-Isaak
// Plot JR with multiple med types on one plot
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


using namespace std;
void jtptWeightMultPlot(){
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  

  //COLORS ARRAY===============================
  //good resource here https://root.cern.ch/root/html522/TColor.html
  int colors[10];
  for(int i=0;i<10;i++){
    colors[i]=i+1;
    if(i==9) colors[i]=12;
    if(i==8 ) colors[i]=28;
  }
  std::string filename;
  std::string prefix[]={"med1","med5","med4"};
  std::string legend[]={"0-10","40-60","70-90"};
  int prefixLength=3;//NEED TO CHANGE THIS WHEN CHANGING PREFIX. I know its an inelegant solution. vector would be better but intializing a vector from a list in c++98 isn't nearly as easy as array or in c++11
  double x1=.75;
  double y1=.1;
  double x2=.9;
  double y2=.3;
  TLegend *leg_pT = new TLegend(x1,y1,x2,y2);
  TLegend *leg_hT = new TLegend(x1,y1,x2,y2);
  
  TH1D * Jet2_pT[prefixLength]; // Intialize histogram array
  TH1D * Jet2_hT[prefixLength]; 
  TH1D * Jet3_pT[prefixLength]; 
  TH1D * Jet3_hT[prefixLength]; 

  TH1D * ratio_pT[prefixLength];
  TH1D * ratio_hT[prefixLength];

  TCanvas * cpT = new TCanvas("cpT","",600,600);
  TH2D * h0_PT =  new TH2D("h0_PT","PbPb 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)",20,0,500,2000,0,2);
  h0_PT->SetYTitle("R_{32}");
  h0_PT->Draw();
  TCanvas * chT = new TCanvas("chT","",600,600);
  TH2D * h0_HT =  new TH2D("h0_HT","PbPb 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)",20,0,500,2000,0,5);
  h0_HT->SetYTitle("R_{32}");
  h0_HT->Draw();
  
  for(int i=0;i<prefixLength;i++){
    filename="ROOT/Jewel/"+prefix[i]+"_weights.root";
    cout<<"LOOP: "<<i<<endl;
    cout<<"FILE: "<<filename<<endl;
    TFile *f = TFile::Open(filename.c_str());

    Jet2_pT[i]=(TH1D*)f->Get((prefix[i]+"_Jet2_pT_HI").c_str());
    Jet2_hT[i]=(TH1D*)f->Get((prefix[i]+"_Jet2_hT_HI").c_str());
    std::string name;
    name=prefix[i]+"_Jet3_pT_HI";
    cout<<"name: "<<name<<endl<<endl;
    Jet3_pT[i]=(TH1D*)f->Get(name.c_str());
    Jet3_hT[i]=(TH1D*)f->Get((prefix[i]+"_Jet3_hT_HI").c_str());


    ratio_pT[i]=new TH1D((prefix[i]+"ratio_pT").c_str(),"PbPb 3-Jet Events /2-Jet Events Ratio;Leading Jet P_{T} (GeV)",100,0,500);
    ratio_hT[i]=new TH1D((prefix[i]+"ratio_hT").c_str(),"PbPb 3-Jet Events /2-Jet Events Ratio;H_{T} (GeV)",100,0,500);

    ratio_pT[i]->Add(Jet3_pT[i]);
    ratio_pT[i]->Divide(Jet2_pT[i]);
    
    ratio_hT[i]->Add(Jet3_hT[i]);
    ratio_hT[i]->Divide(Jet2_hT[i]);

    ratio_pT[i]->SetMarkerStyle(22);
    ratio_pT[i]->SetMarkerColor(colors[i]);
    ratio_pT[i]->SetLineColor(colors[i]);
    ratio_pT[i]->SetYTitle("R_{32}");
    cpT->cd();
    ratio_pT[i]->Draw("same");

    ratio_hT[i]->SetMarkerStyle(20);
    ratio_hT[i]->SetMarkerColor(colors[i]);
    ratio_hT[i]->SetLineColor(colors[i]);
    ratio_hT[i]->SetYTitle("R_{32}");
    chT->cd();
    ratio_hT[i]->Draw("same");

    /*   leg_pT->AddEntry(ratio_pT[i], prefix[i].c_str());
    leg_hT->AddEntry(ratio_hT[i], prefix[i].c_str());
    */
    leg_pT->AddEntry(ratio_pT[i], legend[i].c_str());
    leg_hT->AddEntry(ratio_hT[i], legend[i].c_str());
   
  }
  cpT->cd(); leg_pT->Draw();
  cpT->SaveAs("PNG/mixedMED_pT.png","RECREATE");
  chT->cd(); leg_hT->Draw();
  chT->SaveAs("PNG/mixedMED_hT.png","RECREATE");

}
