//#include <stdio.h>
//#include "iomanip.h"

void makeCharmRAA()
{
  gROOT->Reset();

  TGraphAsymmErrors *gr_D = new TGraphAsymmErrors("/Users/starsdong/work/datapoints/HeavyQuark/UrQMD_CBM_D_RAA.txt","%lg %lg %lg %lg");
  TGraphAsymmErrors *gr_Dbar = new TGraphAsymmErrors("/Users/starsdong/work/datapoints/HeavyQuark/UrQMD_CBM_Dbar_RAA.txt","%lg %lg %lg %lg");

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.15);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.03);

   double x1 = 0;
   double x2 = 2.0;
   double y1 = 0.00;
   double y2 = 4.5;
   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->CenterTitle();;   
   d0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
   d0->GetXaxis()->SetTitleOffset(1.1);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle("R_{AA}^{PYTHIA}");
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw("c");

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   TLine *l0 = new TLine(x1,0,x2,0);
   l0->SetLineStyle(4);
   l0->SetLineWidth(2);
   l0->Draw("same");

   gr_D->SetFillColorAlpha(5,0.3);
   gr_D->SetLineColor(5);
   gr_D->Draw("e3");
   
   gr_Dbar->SetFillColorAlpha(kGreen,0.3);
   gr_Dbar->SetLineColor(kGreen);
   gr_Dbar->Draw("e3");

   TLatex *tex = new TLatex(0.15, 4.0, "Au+Au @ 25A GeV, b = 3fm");
   tex->SetTextFont(42);
   tex->SetTextSize(0.05);
   tex->Draw("same");
   
   TLatex *tex2 = new TLatex(1.4, 0.2, "UrQMD/hybrid");
   tex2->SetTextFont(42);
   tex2->SetTextSize(0.05);
   tex2->Draw("same");

   TLegend *leg = new TLegend(0.2, 0.72, 0.4, 0.84);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(32);
   leg->SetTextSize(0.045);
   leg->AddEntry(gr_Dbar, "#bar{D}", "f");
   leg->AddEntry(gr_D, "D", "f");
   leg->Draw("same");

   c1->Update();
   c1->SaveAs("figs/CBM_charm_RAA.pdf");
   c1->SaveAs("figs/CBM_charm_RAA.png");
}
