#include <iostream>
#include <fstream>
#include <TRandom.h>
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
#include <TRandom3.h>
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


using namespace std;



void compareOutputs(){
  TH1::SetDefaultSumw2();
  TFile *a = new TFile("JewelDijet_Ti14_1_numEvent2000.root");//!
  TFile *b = new TFile("JewelDijet_Ti14_2_numEvent2000.root");//!
  TTree *ta = (TTree*)a->Get("dijet/t");
  TTree *tb = (TTree*)b->Get("dijet/t");
  ta->Draw("jtpt");
  tb->Draw("jtpt","","same red");


}
