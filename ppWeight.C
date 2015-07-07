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

TStopwatch timer;

void ppWeight(const int startfile=0,int endfile=-1){
  bool DEBUG=true;
  
  timer.Start();



  //create the trees and set the branch address
  //jet tree
  int nrefe;
  float jtpt[1000];
  //float old_pt3[1000];
  float raw[1000];
  float eta[1000];
  float phi[1000];
  //event tree
  int evt;
  int run;
  int lumi;
  float vz;
  Double_t pthatweight;
  Float_t varpthat;

  TH1::SetDefaultSumw2();
  std::string infile;
  infile = "jetRAA_pp_mc_forest.txt";
  cout<<"\n\nReading from: "+infile<<endl;
  std::ifstream instr(infile.c_str(), std::ifstream::in);
 
  if(endfile==-1){
    std::ifstream fi(infile.c_str());
    std::string line;
    int number_of_lines=0;
    while (std::getline(fi, line))
      {
	++number_of_lines;
      }
    endfile+=number_of_lines;//-1 accounts for line telling medium type.
    cout<<"You did not specify number of files will run on all: "<<endfile<<" lines\n";
  }
  std::string filename;

  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    instr >> filename;
  }

  int nFiles = endfile - startfile;
  cout<<"Running on "<<nFiles<<" forest files"<<endl;



  //output file:
  TFile f(Form("pp_weight_%d.root",endfile),"RECREATE");
  // declare the output histograms/ntuples or whatever you want
  TH1F * hvz = new TH1F("hvz","",40,-20, 20);
 
  TH1D * Jet2 = new TH1D("Jet2","2-Jet;Leading Jet pt",100,0,500);
  TH1D * Jet3 = new TH1D("Jet3","3-Jet;Leading Jet pt",100,0,500);  

  //==============ACTUALLY READ FILES=============
  stringstream weightName;
  for(int ifile=startfile;ifile<endfile;ifile++){
    instr >> filename;
    weightName.str(""); weightName<<"weights/weights_pp_"<<ifile+1<<".root";
 
    if(DEBUG) cout<<"ifile: "<<ifile<<"\nFile: "<<filename<<endl<<"weightFile: "<<weightName.str()<<"\n\n";

    TFile *fin = TFile::Open(filename.c_str());
    TFile *wFile= TFile::Open(weightName.str().c_str());

    TTree* jetTree = (TTree*)fin->Get("akPu3PFJetAnalyzer/t");
    TTree* skimTree_in = (TTree*)fin->Get("skimanalysis/HltTree");
    TTree* evtTree_in = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
    TTree* hltTree_in = (TTree*)fin->Get("hltanalysis/HltTree");
    TTree* weights = (TTree*)wFile->Get("weights");

    //ADD FRIENDS
    jetTree->AddFriend(weights);
    jetTree->AddFriend(evtTree_in);


    //SET BRANCH ADDRESSES
    jetTree->SetBranchAddress("evt",&evt);
    jetTree->SetBranchAddress("run",&run);
    jetTree->SetBranchAddress("lumi",&lumi);
    jetTree->SetBranchAddress("vz",&vz);
    jetTree->SetBranchAddress("nref",&nrefe);
    jetTree->SetBranchAddress("jtpt",&jtpt);
    jetTree->SetBranchAddress("jteta",&eta);
    jetTree->SetBranchAddress("jtphi",&phi);
    jetTree->SetBranchAddress("pthat",&varpthat);
    jetTree->SetBranchAddress("pthatweight",&pthatweight);



    Long64_t nentries = jetTree->GetEntries();

    if(DEBUG)nentries = 100;
    for (int i = 0; i < nentries; i++){ //start of event loop.
      jetTree->GetEntry(i);

      if(DEBUG){
	cout<<"pthatweight: "<<pthatweight<<endl;
      }
      if(i%1000==0)cout<<"event = "<<i<<"; run = "<<run<<endl;
      // apply your event selection cuts here:
      if(fabs(vz)>15) continue;
      hvz->Fill(vz);
      // jet loop
      for(int g = 0; g<nrefe; ++g){
	// fill your jet histograms here:
	bool skip2=false;
	if(nrefe==3){ Jet3->Fill(jtpt[0],pthatweight); skip2=true;}
	if(nrefe==2 && !skip2) Jet2->Fill(jtpt[0],pthatweight);

      }
    }// event loop
    fin->Close();
  }//end of file loop
 f.cd();
 f.Write();
 f.Close();  

}
