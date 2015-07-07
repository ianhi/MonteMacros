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

Float_t jtpt[1000];//jet pt taken from dijet/t
Int_t nref; //believe this to be the number of jets per event - variable in dijet/nt
Float_t varpthat; // pthat variable to be set with SetBranchAddress


void jtptWeight(){
  cout<<"\n\n\n\n\n";
  bool DEBUG=true;
  bool DEBUGLONG=false;//true -> much longer runtime OR lots of output
  bool DRAW=true;

  double pthatBinning[] = {15,30,50,80,120,170,220,280,330,400,460,540};
  //                0           1           2      3       4           5            6        7        8        9          10
  double xsSUM[] = {4878812.4,4218696.2,4659866.4,4049616.0,2934218.1,1695768.4,1302251.3,718081.6,578537.1,291444.26,168207.79}; //-1 is for run six
  double xsQCD[] = {286240.0,444780.0,  494830.0,514200.0,554520.0,482280.0,    309090.0,304490.0,173850.0,173850.0,114700.0};

  double * xsQ=xsQCD;
  int i=0;
  while(i<11 && DEBUG){
    cout<<"xsQ["<<i<<"]: "<<xsQ[i]<<endl;
    
    i++;
  }
  double * xsS=xsSUM;
  double *pthats = pthatBinning;

  TChain* tChain;
  TChain* ntChain;
  TFile* outf;
  std::string numEvents;
  numEvents="all";
  std::string infile;
  infile = numEvents+"_fileList.txt";

  
  //get number of lines in file
  std::ifstream fi(infile.c_str());
  std::string line;
  int number_of_lines=0;
  while (std::getline(fi, line))
    {
      ++number_of_lines;
    }
  cout<<"Number of line: "<<number_of_lines<<endl;

  std::ifstream instr(infile.c_str(), std::ifstream::in);
  std::string filename;
  tChain = new TChain("dijet/t");
  ntChain = new TChain("dijet/nt");
  // Order of files matters a lot!  
  for(int i=0;i<number_of_lines;i++){
    instr >> filename;
    tChain->AddFile(filename.c_str());
    ntChain->AddFile(filename.c_str());
    if(DEBUG) cout<<"Iteration: "<<i<<"\nFileName: "<<filename<<"\nTChain Events: "<<tChain->GetEntries()<<"\n\n";
    
  }
  if(DEBUG) cout<<"total number of events = "<<ntChain->GetEntries()<<endl;
  
  tChain->AddFriend(ntChain);
 
  
  outf = new TFile(Form("weights.root"),"recreate");
  std::string title;
  title=numEvents+" QCD cross Section - jtpt;jtpt";
  TH1D * Qjtpt = new TH1D("Qjtpt",title.c_str(),20,0,460);
  title=numEvents+" SUM cross Section - jtpt;jtpt";
  TH1D * Sjtpt = new TH1D("Sjtpt",title.c_str(),20,0,460);
  title=numEvents+" QCD cross Section - PTHAT; pthat";
  TH1D * hQpthat = new TH1D("hQpthat",title.c_str(),500,0,500);
    title=numEvents+" SUM cross Section-PTHAT; pthat";
  TH1D * hSpthat = new TH1D("hSpthat",title.c_str(),500,0,500);
  title=numEvents+" UnWeighted counts - PTHAT; pthat";
  TH1D * hpthat = new TH1D("hpthat",title.c_str(),500,0,500);
 
  TH1D * Jet2 = new TH1D("Jet2","2-Jet;Leading Jet pt",100,0,500);
  TH1D * Jet3 = new TH1D("Jet3","3-Jet;Leading Jet pt",100,0,500);  

  TH1D * nJet2 = new TH1D("nJet2","2-Jet;Leading Jet pt",100,0,500);
  TH1D * nJet3 = new TH1D("nJet3","3-Jet;Leading Jet pt",100,0,500);  
  TH1D * Hnref = new TH1D("Hnref","nref",20,0,20);  

  double pthatweightQ = 0;//weight for just QCD xs
  double pthatweightS = 0;//weight for just SUM xs
  int n[20];//events in a given pthat range
  int Npt = 11;//number of pthat bins - 11 to account for missing run 6

  int sumN=0;
  for(int i = 0; i < Npt; ++i){//fill n[i] loop
    if(xsSUM[i]==-1){n[i]=0;continue;}//without this n[6] will return things like -825280132 or  1796752684
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
  ntChain->SetBranchAddress("pthat",&varpthat);
  tChain->SetBranchAddress("jtpt",jtpt);
  tChain->SetBranchAddress("nref",&nref);
  
  for(int ie = 0; ie < tChain->GetEntries(); ++ie){
    tChain->GetEntry(ie);
    if(varpthat<15){
      while(true)
	cout<<"AAAAAAAAAAAAAH\n\n";
    }
    for(int i = 0; i < Npt; ++i){
      if(n[i] > 0 && varpthat >= pthats[i]) {
	pthatweightQ = xsQ[i]/n[i];
	pthatweightS = xsS[i]/n[i];
      }
    }
    
    if(DEBUGLONG && ie%100==0){
      cout<<"event num:  "<<ie<<endl;
      cout<<"pthat:  "<<varpthat<<endl;
      cout<<"Q weight:  "<<pthatweightQ<<endl;
      cout<<"S weight:  "<<pthatweightS<<endl<<endl;
    }
    
    hQpthat->Fill(varpthat,pthatweightQ);
    hSpthat->Fill(varpthat,pthatweightS);
    hpthat->Fill(varpthat);
    Hnref->Fill(nref);
    bool skip2 =false;
    //Histograms for jet ratio
    //skip2 is so 3 jet events aren't also counted in the 2-jet events
    if(jtpt[2]>=30){ Jet3->Fill(jtpt[0],pthatweightS);skip2=true;}
    if(jtpt[1]>=30 && !skip2) Jet2->Fill(jtpt[0],pthatweightS);

    if(nref==3){ nJet3->Fill(jtpt[0],pthatweightS); skip2=true;}
    if(nref==2 && !skip2) nJet2->Fill(jtpt[0],pthatweightS);


    //jet pt histograms
    for(int i = 0; i < nref; ++i){///DO CHECK IF SHOULD BE < or <= //loop through the events in a jet
      Qjtpt->Fill(jtpt[i],pthatweightQ);
      Sjtpt->Fill(jtpt[i],pthatweightS); 
    }
    for(int i=0;i<1000;i++)
      jtpt[i]=0;
 
  }
  outf->cd();
  outf->Write();
  outf->Close();
  
  
}
