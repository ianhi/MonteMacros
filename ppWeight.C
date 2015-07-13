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
  bool DEBUG=false;//Will dramatically increase time if runnign all events
  bool DEBUG_SHORT=true;//if true will run over only 100 events per file
  
  timer.Start();
  TH1::SetDefaultSumw2();
  
  //Variables===================================================
  int nref;//number of jets in an event
  float jtpt[1000];//jet pt array
  float jteta[1000];
  float hT; // scale sum of jet pT
  int evt;
  int run;
  int lumi;
  float vz;

  Double_t pthatweight;
  Float_t varpthat;

  //To Scale Histograms- Can't do GetEntries() as that does not accoutn for weighting
  double Scale_Jet2=0; 
  double Scale_Jet3=0;


  //SET UP FILE LIST==========================================
  std::string infile;
  infile = "TEXTFILES/jetRAA_pp_mc_forest.txt";
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
  TFile f(Form("ROOT/pp_weight_%d.root",endfile),"RECREATE");
 
  //DEFINE HISTOGRAMS=============================================
  TH1D *Jet2_hT = new TH1D("Jet2_hT_pp","pT>=30 2-Jet;H_{T} (GeV)",100,0,500);
  TH1D *Jet3_hT = new TH1D("Jet3_hT_pp","pT>=30 3-Jet;H_{T} (GeV)",100,0,500);

  TH1D *Jet2_pT = new TH1D("Jet2_pT_pp","pT>=30 2-Jet;Leading Jet P_{T} (GeV)",100,0,500);
  TH1D *Jet3_pT = new TH1D("Jet3_pT_pp","pT>=30 3-Jet;Leading Jet P_{T} (GeV)",100,0,500);

  TH1D * hPTHAT = new TH1D("pthat_pp","pp PTHAT weighted",500,0,500);
  TH1D * hJTPT = new TH1D("jtpt_pp","pp JTPT weighted",500,0,500);

  //READ FILES====================================================
  stringstream weightName;//stringstream allows easy concat of str and int
  for(int ifile=startfile;ifile<endfile;ifile++){
    instr >> filename;
    weightName.str(""); weightName<<"weights/weights_pp_"<<ifile+1<<".root";
 
    if(DEBUG) cout<<"ifile: "<<ifile<<"\nFile: "<<filename<<endl<<"weightFile: "<<weightName.str()<<"\n\n";
    //OPEN INPUT FILES======================================
    TFile *fin = TFile::Open(filename.c_str());//data file
    TFile *wFile= TFile::Open(weightName.str().c_str());//corresponding pthat weight
    //GET TREES==================================================
    TTree* jetTree = (TTree*)fin->Get("akPu3PFJetAnalyzer/t");
    TTree* skimTree_in = (TTree*)fin->Get("skimanalysis/HltTree");
    TTree* evtTree_in = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
    TTree* hltTree_in = (TTree*)fin->Get("hltanalysis/HltTree");
    TTree* weights = (TTree*)wFile->Get("weights");

    //ADD FRIENDS================================================
    jetTree->AddFriend(weights);
    jetTree->AddFriend(evtTree_in);


    //SET BRANCH ADDRESSES=======================================
    jetTree->SetBranchAddress("evt",&evt);
    jetTree->SetBranchAddress("run",&run);
    jetTree->SetBranchAddress("lumi",&lumi);
    jetTree->SetBranchAddress("vz",&vz);
    jetTree->SetBranchAddress("nref",&nref);
    jetTree->SetBranchAddress("jtpt",&jtpt);
    jetTree->SetBranchAddress("pthat",&varpthat);
    jetTree->SetBranchAddress("pthatweight",&pthatweight);
    jetTree->SetBranchAddress("jteta",&jteta);



    //LOOP OVER EVENTS============================================

    Long64_t nentries = jetTree->GetEntries();
    if(DEBUG_SHORT)nentries = 100;

    for (int i = 0; i < nentries; i++){ //start of event loop.
      jetTree->GetEntry(i);
      if(i%1000==0)cout<<"event = "<<i<<"; run = "<<run<<endl;
      // SELECTION CUTS--------------------------------------
      if(fabs(vz)>15) continue;

      //SET UP FOR FILLING------------------------------------
      bool skip2=false;//Ensures 3-Jet events aren't also counted as 2-Jet events
      Float_t etaGood[1000]; // ensures that jet 2 isn't outside eta range
      int goodIndex=0;
      hT=0; // Scalar Sum of jet pT
      
      for(int g = 0; g<nref; ++g){
	if(fabs(jteta[g])>=2.0) continue;
	etaGood[goodIndex]=jtpt[g];
	goodIndex++;
	hT+=jtpt[g];
	hJTPT->Fill(jtpt[g],pthatweight);
      }
      //FILL HISTOGRAMS----------------------------------
      hPTHAT->Fill(varpthat,pthatweight);

      if(etaGood[2]>=30 && etaGood[3]<30){ //If a three or more jet Event
	Jet3_pT->Fill(etaGood[0],pthatweight);
	Jet3_hT->Fill(hT,pthatweight);
	Scale_Jet3+=pthatweight;
	skip2=true;
      }
      if(etaGood[1]>=30 && !skip2) {//if a 2-Jet Event
	Jet2_pT->Fill(etaGood[0],pthatweight);
	Jet2_hT->Fill(hT,pthatweight);
	Scale_Jet2+=pthatweight;
      }
    }// event loop
    fin->Close();
  }//end of file loop

  /* //SCALE HISTOGRAMS==========================================
  Jet2_pT->Scale(1./Scale_Jet2);
  Jet3_pT->Scale(1./Scale_Jet3);

  Jet2_hT->Scale(1./Scale_Jet2);
  Jet3_hT->Scale(1./Scale_Jet3);
  */
  //WRITE OUTPUT FILE===========================================
  cout<<"Scale 3: "<<Scale_Jet3<<endl;
  cout<<"Scale 2: "<<Scale_Jet2<<endl;
  f.cd();
  f.Write();
  f.Close();  

}
