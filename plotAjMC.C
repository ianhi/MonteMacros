void plotAjMC(){
  
  TFile * file0 = TFile::Open(".root");
  
  hQ_JR ->SetLineColor(kRed);
  hZ_JR ->SetLineColor(kGreen);
  

  TLegend *legend_JR = new TLegend(.75,.70,.95,.85);
  //cRat -> cd()->SetLogy();
  
  legend_JR->AddEntry(hQ_JR, "PYQUEN", "p");
  legend_JR->AddEntry(hZ_JR, "PYTHIA Z2*", "p");
  legend_JR->AddEntry(hW_JR, "PYQUEN WIDE", "p");
 
  hQ_JR ->SetOption("PE");
  hZ_JR ->SetOption("PE");
  hW_JR ->SetOption("pE");

  hQ_JR->GetXaxis()->SetTitle("Leading Jet P_{T} (GeV/c)");
  hQ_JR->GetYaxis()->SetTitle("3-Jet/2-Jet Ratio");
  hQ_JR->GetYaxis()->SetTitleOffset(1.4);
  
  gStyle->SetOptStat(0);

  hQ_JR ->Draw("P");
  hZ_JR ->Draw("same p");
  hW_JR ->Draw("same p");

  
  hQ_JR->SetMarkerStyle(20); hQ_JR->SetMarkerColor(kBlue); hQ_JR->SetMarkerSize(.8);
  hZ_JR->SetMarkerStyle(20); hZ_JR->SetMarkerColor(kBlack); hZ_JR->SetMarkerSize(.8);
  hW_JR->SetMarkerStyle(20); hW_JR->SetMarkerColor(kGreen); hW_JR->SetMarkerSize(.8);

  /* hsA ->Add(hQ_A);
     hsA ->Add(hZ_A);
     hsA ->Add(hW_A);
     hsA ->Draw("nostack");
  */
  legend_JR->Draw("SAME");
  cRat->SaveAs("JetRatio.pdf","RECREATE");
}
