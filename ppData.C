// Created 13 July, 2015
// Ian Hunt-Isaak
// ihuntisa@NOSPAMPLEASEoberlin.edu primary email through may 2017
// ianhuntisaak@NOSPAMPLEASEgmail.com Permanent email
// This macro reads the pp data files and creates histograms of the 3 jet 2 jet ratio


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

void ppData(const int startfile=0,int endfile=-1,int radius=3){
  cout<<"IN MACRO\n";
  bool DEBUG=false;//Will dramatically increase time if runnign all events
  bool DEBUG_SHORT=false;//if true will run over only 100 events per file
  
  timer.Start();
  TH1::SetDefaultSumw2();
  
  //Variables===================================================
  int nref=0;//number of jets in an event
  float jtpt[1000];//jet pt array
  float jteta[1000];
  float hT; // scale sum of jet pT
  int evt=0;
  int run=0;
  int lumi=0;
  float vz=0;
  int pcollisionEventSelection=0;
  Long64_t TotalEntries=0;

  //SET UP FILE LIST==========================================
  std::string infile;
  infile = "jetRAA_pp_data_forest.txt";
  cout<<"txt file in same dir\n";
  cout<<"\n\nReading from: "+infile<<endl;
  std::ifstream instr(infile.c_str(), std::ifstream::in);
 
  //If number of files to read not specified then read how many lines are in file
  if(endfile==-1){
    std::ifstream fi(infile.c_str());
    std::string line;
    int number_of_lines=0;
    while (std::getline(fi, line)) ++number_of_lines;
    endfile+=number_of_lines+1;
    cout<<"You did not specify number of files will run on all: "<<endfile<<" lines\n";
  }

  // If not starting from file 0 discard earlier lines
  std::string filename;
  cout<<"reading from "<<startfile<<" to "<<endfile<<endl;  
  for(int ifile=0;ifile<startfile;ifile++){ 
    instr >> filename;
  }
  cout<<"Running on "<<endfile-startfile<<" forest files"<<endl;

  //DEFINE OUTPUT FILE===========================================
  TFile f(Form("ROOT/pp_data_sameDir_%d.root",endfile),"RECREATE");
  f.cd();
  cout<<"output file: "<<Form("ROOT/pp_data_%d.root",endfile)<<endl;
  //DEFINE HISTOGRAMS=============================================
  TH1D *Jet2_hT = new TH1D("Jet2_hT_pp_Data","Data pT>=30 2-Jet;H_{T} (GeV)",100,0,1000);
  TH1D *Jet3_hT = new TH1D("Jet3_hT_pp_Data","Data pT>=30 3-Jet;H_{T} (GeV)",100,0,1000);

  TH1D *Jet2_pT = new TH1D("Jet2_pT_pp_Data","Data pT>=30 2-Jet;Leading Jet P_{T} (GeV)",100,0,1000);
  TH1D *Jet3_pT = new TH1D("Jet3_pT_pp_Data","Data pT>=30 3-Jet;Leading Jet P_{T} (GeV)",100,0,1000);

  TH1D * hJTPT_EtaCut = new TH1D("jtpt_pp_EtaCut","Data pp JTPT good eta",1000,0,1000);
  TH1D * hJTPT_NoCut = new TH1D("jtpt_pp_NoEtaCut","Data pp JTPT all eta",1000,0,1000);
 
  //READ FILES====================================================
  for(int ifile=startfile;ifile<endfile;ifile++){
    instr >> filename;
   
    cout<<"ifile: "<<ifile<<"\nFile: "<<filename<<endl;
    //OPEN INPUT FILES======================================
    TFile *fin = TFile::Open(filename.c_str());//data file

    //GET TREES==================================================
    TTree* jetTree = (TTree*)fin->Get(Form("ak%dPFJetAnalyzer/t",radius));
    TTree* skimTree_in = (TTree*)fin->Get("skimanalysis/HltTree");
    TTree* evtTree_in = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
 
    //SET BRANCH ADDRESSES=======================================
    evtTree_in->SetBranchAddress("evt",&evt);
    evtTree_in->SetBranchAddress("run",&run);
    evtTree_in->SetBranchAddress("lumi",&lumi);
    evtTree_in->SetBranchAddress("vz",&vz);

    jetTree->SetBranchAddress("nref",&nref);
    jetTree->SetBranchAddress("jtpt",&jtpt);
    jetTree->SetBranchAddress("jteta",&jteta);

    skimTree_in->SetBranchAddress("pPAcollisionEventSelectionPA",&pcollisionEventSelection);
  


    //ADD FRIENDS================================================
    jetTree->AddFriend(evtTree_in);
    jetTree->AddFriend(skimTree_in);
    
    //LOOP OVER EVENTS============================================

    Long64_t nentries = jetTree->GetEntries();
    if(DEBUG_SHORT)nentries = 10000;
    TotalEntries+=nentries;
    for (Long64_t i = 0; i < nentries; i++){ //start of event loop.
      if(DEBUG){
	cout<<"entry: "<<i<<endl;
	cout<<Form("ak%dPFJetAnalyzer/t",radius)<<endl;
      }
      jetTree->GetEntry(i);
      if(DEBUG) cout<<"jetTree\n";
      skimTree_in->GetEntry(i);
      if(DEBUG) cout<<"SKIM Tree\n";      
      evtTree_in->GetEntry(i);

      
      if(i%1000==0){
	cout<<"ifile: "<<ifile<<"\nFile: "<<filename<<endl;
	cout<<"event = "<<i<<"; Of "<<nentries<<"; run = "<<run<<endl<<endl;
      }
      // SELECTION CUTS--------------------------------------
      if(fabs(vz)>15) continue;
      if(pcollisionEventSelection==0){
	if(DEBUG)	cout<<"pcollision 0\n";
	continue;
      }
      //SET UP FOR FILLING------------------------------------
      hT=0; // Scalar Sum of jet pT
      if(DEBUG)   cout<<"BEFORE VECTOR DEF\n";
      std::vector < float > goodJet;
      if(DEBUG) cout<<"DEFINED VECTOR\n";
      for(int g = 0; g<nref; ++g){
	hJTPT_NoCut->Fill(jtpt[g]);
	if(fabs(jteta[g])>=2.0 || jtpt[g]<30) continue;
	goodJet.push_back(jtpt[g]);
	hT+=jtpt[g];
	hJTPT_EtaCut->Fill(jtpt[g]);
      }
      //FILL HISTOGRAMS----------------------------------
      switch(goodJet.size()){
      case 3:
	Jet3_pT->Fill(goodJet[0]);
	Jet3_hT->Fill(hT);
	break;
      case 2:
	Jet2_pT->Fill(goodJet[0]);
	Jet2_hT->Fill(hT);
	break;
      }
      if(DEBUG) cout<<"PRE CLEAR\n";
      goodJet.clear();
      for(int j=0;j<1000;j++)
	jtpt[j]=0;
      if(DEBUG)  cout<<"POST CLEAR\n";
    }// event loop
    fin->Close();
  }//end of file loop
  cout<<"Total Entries: "<<TotalEntries<<endl;
  f.Write();
  cout<<"Wrote Output File\n";
  f.Close();  
  cout<<"FINISHED!\n";
}
