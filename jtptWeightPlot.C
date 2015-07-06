
#include <TFile.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
void jtptWeightPlot(){
  bool bQjtpt=true;
  bool bSjtpt=true;
  bool bhQpthat=true;
  bool bhSpthat=true;
  bool bhpthat=true;
{
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  cout << "TDR Style initialized" << endl;

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //Position on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);

  tdrStyle->SetEndErrorSize(2);
  //tdrStyle->SetErrorMarker(20);
  tdrStyle->SetErrorX(0.);

  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.15);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.13);
  tdrStyle->SetPadRightMargin(0.15);

// For the Global title:

//  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
// The inconsistency is great!
  tdrStyle->SetTitleXOffset(1.0);
  tdrStyle->SetTitleOffset(1.5, "Y"); 

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  tdrStyle->SetPalette(1,0);
  tdrStyle->cd();
}
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  TFile *f = TFile::Open(Form("weights.root"));
  if(bQjtpt){
    TH1D * Qjtpt = (TH1D*)f->Get("Qjtpt");
    TCanvas * cQj = new TCanvas("cQj","",600,600);
    cQj->cd();
    cQj->SetLogy();
    Qjtpt->Draw();
    cQj->SaveAs("QCD_Weight_jtpt.png","RECREATE");
  }
  if(bSjtpt){
    TH1D * Sjtpt = (TH1D*)f->Get("Sjtpt");
    TCanvas * cSj = new TCanvas("cSj","",600,600);
    cSj->cd();
    cSj->SetLogy();
    Sjtpt->Draw();    
    cSj->SaveAs("SUM_Weight_jtpt.png","RECREATE");
  }
  if(bhQpthat){
    TH1D * hQpthat = (TH1D*)f->Get("hQpthat");
    TCanvas * cQp = new TCanvas("cQp","",600,600);
    cQp->cd();
    cQp->SetLogy();
    hQpthat->Draw();
    cQp->SaveAs("pthat_QCD_Weight.png","RECREATE");
  }
  if(bhSpthat){
    TH1D * hSpthat = (TH1D*)f->Get("hSpthat");
    TCanvas * cSp = new TCanvas("cSp","",600,600);
    cSp->cd();
    cSp->SetLogy();
    hSpthat->Draw();
    cSp->SaveAs("pthat_SUM_Weight.png","RECREATE");
  }
  if(bhpthat){
    TH1D * hpthat = (TH1D*)f->Get("hpthat");
    TCanvas * cp = new TCanvas("cp","",600,600);
    cp->cd();
    cp->SetLogy();
    hpthat->Draw();
    cp->SaveAs("pthat_NO_Weight.png","RECREATE");
  }


}
