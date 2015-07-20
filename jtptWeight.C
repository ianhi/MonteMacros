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
#include <cmath>

Float_t jtpt[1000];//jet pt taken from dijet/t
Float_t jteta[1000];
Float_t vz;
Int_t nref; //believe this to be the number of jets per event - variable in dijet/nt
Float_t varpthat; // pthat variable to be set with SetBranchAddress
float hT;

void jtptWeight(){
  cout<<"\n\n\n";
  bool DEBUG=true;
  bool DEBUGLONG=false;//true -> much longer runtime OR lots of output
  TH1::SetDefaultSumw2();


  TChain* tChain;
  TChain* ntChain;
  TChain* nt2Chain;
  double pthatweightQ = 0;//weight for just QCD xs
  double pthatweightS = 0;//weight for just SUM xs

  std::string prefix;
  prefix="med1";
  std::string infile;
  infile = "TEXTFILES/"+prefix+"_fileList.txt";
  if(DEBUG) cout<<"infile: "<<infile<<endl;

  //GET NUMBER OF LINES IN FILE==================================
  std::ifstream fi(infile.c_str());
  std::string line;
  int number_of_lines=0;
  while (std::getline(fi, line)) ++number_of_lines;
  cout<<"Number of line: "<<number_of_lines<<endl;

  //TCHAIN FILES TOGETHER=======================================
  std::ifstream instr(infile.c_str(), std::ifstream::in);
  std::string filename;
  tChain = new TChain("dijet/t");
  ntChain = new TChain("dijet/nt"); 
  nt2Chain = new TChain("ana/hi");
  for(int i=0;i<number_of_lines;i++){
    instr >> filename;
    tChain->AddFile(filename.c_str());
    ntChain->AddFile(filename.c_str());
    if(DEBUG) cout<<"Iteration: "<<i<<"\nFileName: "<<filename<<"\nTChain Events: "<<tChain->GetEntries()<<"\n\n";
  }
  if(DEBUG) cout<<"total number of events = "<<ntChain->GetEntries()<<endl;
  
  //ADD FRIEND------------------------
  tChain->AddFriend(ntChain);
  // tChain->AddFriend(nt2Chain);  
  if (DEBUG) cout<<"FRIENDS ADDED\n";

  //SET BRANCH ADDRESSES-------------------------------
  ntChain->SetBranchAddress("pthat",&varpthat);
  nt2Chain->SetBranchAddress("vz",&vz);
  tChain->SetBranchAddress("jtpt",&jtpt);
  tChain->SetBranchAddress("jteta",&jteta);
  tChain->SetBranchAddress("nref",&nref);
  if(DEBUG) cout<<"BRANCH ADDRESSES SET"<<endl;
  
  //PTHAT WEIGHTING SETUP======================================================
  double pthatBinning[] = {15,30,50,80,120,170,220,280,330,400,460,540};
  //                0           1           2      3       4           5            6        7        8        9          10
  double xsSUM[] = {4878812.4,4218696.2,4659866.4,4049616.0,2934218.1,1695768.4,1302251.3,718081.6,578537.1,291444.26,168207.79};
  double xsQCD[] = {286240.0,444780.0,  494830.0,514200.0,554520.0,482280.0,    309090.0,304490.0,173850.0,173850.0,114700.0};

  double * xsQ=xsQCD;
  double * xsS=xsSUM;
  double *pthats = pthatBinning;
 
  int Npt = 11;//number of pthat bins - 11 to account for missing run 6
  int n[Npt];//events in a given pthat range 
  int sumN=0;

  for(int i = 0; i < Npt; ++i){//fill n[i] loop
    TCut pthatCut(Form("pthat >= %f && pthat < %f",pthats[i],pthats[i+1]));
    n[i] = tChain->GetEntries(pthatCut);
    sumN+=n[i];
    if(DEBUG){
      cout<<"In fill n[i] loop iteration: "<<i<<"\n";
      cout<<"pthat low/high:  "<<pthats[i]<<"  "<<pthats[i+1]<<endl;
      cout<<"n["<<i<<"]  :"<<n[i]<<"\n\n";
    }
  }

  if (DEBUG) cout<<"\nsumN: "<<sumN<<endl;

  
  //DEFINE OUTPUT FILE===========================================
  std::string outName="ROOT/Jewel/"+prefix+"_weights.root";
  TFile * outf = new TFile(outName.c_str(),"RECREATE");
  outf->cd();
  if (DEBUG) cout<<"Output file: "<<outName<<endl;
  //DEFINE HISTOGRAMS=============================================
  //------Weighting jtpt and pthat histograms----------------
 
  std::string title;
  std::string name;
  title=prefix+" QCD cross Section - jtpt;jtpt";
  name=prefix+"_Qjtpt";
  TH1D * Qjtpt = new TH1D(name.c_str(),title.c_str(),20,0,460);
  title=prefix+" SUM cross Section - jtpt;jtpt";
  name=prefix+"_Sjtpt";
  TH1D * Sjtpt = new TH1D(name.c_str(),title.c_str(),20,0,460);
  title=prefix+" QCD cross Section - PTHAT; pthat";
  name=prefix+"_hQpthat";
  TH1D * hQpthat = new TH1D(name.c_str(),title.c_str(),500,0,500);
  title=prefix+" SUM cross Section-PTHAT; pthat";
  name=prefix+"_hSpthat";
  TH1D * hSpthat = new TH1D(name.c_str(),title.c_str(),500,0,500);
  title=prefix+" UnWeighted counts - PTHAT; pthat";
  name=prefix+"_hpthat"; 
  TH1D * hpthat = new TH1D(name.c_str(),title.c_str(),500,0,500);
  //------Jet Ratio Histograms--------------------------------

  title=prefix+" 2-Jet;Leading Jet P_{T} (GeV)";
  name=prefix+"_Jet2_pT_HI";
  TH1D *Jet2_pT = new TH1D(name.c_str(),title.c_str(),100,0,500);
  title=prefix+" 3-Jet;Leading Jet P_{T} (GeV)";
  name=prefix+"_Jet3_pT_HI";
  TH1D *Jet3_pT = new TH1D(name.c_str(),title.c_str(),100,0,500);
  title=prefix+" 2-Jet;H_{T} (GeV)";
  name=prefix+"_Jet2_hT_HI";
  TH1D *Jet2_hT = new TH1D(name.c_str(),title.c_str(),100,0,500);
  title=prefix+" 3-Jet;H_{T} (GeV)";
  name=prefix+"_Jet3_hT_HI";
  TH1D *Jet3_hT = new TH1D(name.c_str(),title.c_str(),100,0,500); 



  //LOOP OVER EVENTS IN TCHAIN===============================
  for(int ie = 0; ie < tChain->GetEntries(); ++ie){//Event loop
    tChain->GetEntry(ie);
    nt2Chain->GetEntry(ie);
    //cout<<"vz: "<<vz<<endl;


    //Selection Cuts=======================
    if(TMath::Abs(vz) > 15) continue;
    
    //Calculate Weights====================
    for(int i = 0; i < Npt; ++i){
      if(n[i] > 0 && varpthat >= pthats[i]) {
	pthatweightQ = xsQ[i]/n[i];
	pthatweightS = xsS[i]/n[i];
      }
      if(n[i]==0&&varpthat>=pthats[i]){
	  pthatweightQ = 0;
	  pthatweightS = 0;
	}
    }
    
    if(DEBUGLONG && ie%100==0){
      cout<<"event num:  "<<ie<<endl;
      cout<<"pthat:  "<<varpthat<<endl;
      cout<<"Q weight:  "<<pthatweightQ<<endl;
      cout<<"S weight:  "<<pthatweightS<<endl<<endl;
    }
    //PTHAT HISTOGRAMS=============================
    hQpthat->Fill(varpthat,pthatweightQ);
    hSpthat->Fill(varpthat,pthatweightS);
    hpthat->Fill(varpthat);
    hT=0; // Scalar Sum of jet pT
    if(DEBUGLONG)   cout<<"BEFORE VECTOR DEF\n";
    std::vector < float > goodJet;
    if(DEBUGLONG) cout<<"DEFINED VECTOR\n";
    for(int g = 0; g<nref; ++g){
      if(fabs(jteta[g])>=2.0 || jtpt[g]<30) continue;
      goodJet.push_back(jtpt[g]);
      hT+=jtpt[g];
      Qjtpt->Fill(jtpt[g],pthatweightQ);
      Sjtpt->Fill(jtpt[g],pthatweightS); 
    }
    //FILL HISTOGRAMS----------------------------------
    switch(goodJet.size()){
    case 3:
      Jet3_pT->Fill(goodJet[0],pthatweightS);
      Jet3_hT->Fill(hT,pthatweightS);
      break;
    case 2:
      Jet2_pT->Fill(goodJet[0],pthatweightS);
      Jet2_hT->Fill(hT,pthatweightS);
      break;
    }
    if(DEBUGLONG) cout<<"PRE CLEAR\n";
    goodJet.clear();
    if(DEBUGLONG)  cout<<"POST CLEAR\n";

    for(int i=0;i<1000;i++) //make sure jtpt array is all 0 for next event
      jtpt[i]=0;
 
  }//end event loop
 

  
  //WRITE OUTPUT FILE============================
  outf->Write();
  outf->Close();
}
