#include "style.C+"
#include "draw.C+"

Double_t Perp(Double_t *x, Double_t *par)
{
  double y = x[0] + par[2];
  double m = par[0];
  double eta = par[1];
  double a = TMath::CosH(y);
  double b = TMath::CosH(eta);
  return m*TMath::Sqrt((a*a-1)/(b*b-a*a));
}

void accept(const Int_t ip = 0)
{
  style();
  const Double_t T_lab[2] = {11, 2.85};  // kinetic energy region
  const Double_t m = 0.9315;  // u
  const Double_t mp[6] = {0.93827, 0.13957, 0.49367, 1.019, 2.992, 3.923};
  const Char_t *name[6] = {"Proton", "Pion", "Kaon", "Phi", "H3L", "H4L"};
  TLorentzVector targ(0,0,0,m);

  Double_t E[2], E_cms[2];
  Double_t y0[2];
  for(int i=0;i<2;i++) {
    E[i] = T_lab[i]+m;
    double p = sqrt(E[i]*E[i]-m*m);
    TLorentzVector proj(0,0,p,E[i]);
    TLorentzVector s = targ + proj;
    E_cms[i] = s.Mag();
    y0[i] = s.Rapidity();
    cout << "proj E = " << E[i] << "\t sqrt(s) = " << E_cms[i] << "\t y0 = " << y0[i] << endl;
  }

  const Double_t theta[2] = {2.5, 25.};  // tracking acceptance 2.5 - 25 deg.
  Double_t eta_ref[2];
  for(int i=0;i<2;i++) {
    TVector3 a(TMath::Sin(theta[i]/180.*TMath::Pi()), 0, TMath::Cos(theta[i]/180.*TMath::Pi()));
    eta_ref[i] = a.Eta();
    cout << "eta_ref = " << eta_ref[i] << endl;    
  }


  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
  c1->SetLeftMargin(0.13);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->Draw();
  
   double x1 = -2.5;
   double x2 = 3.0;
   double y1 = 0.0;
   double y2 = 3.0;
   
   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->CenterTitle();
   d0->GetXaxis()->SetTitle("Proton Rapidity y");
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetYaxis()->SetTitle("p_{T} (GeV/c)");
   d0->GetYaxis()->SetTitleOffset(0.8);
   d0->Draw();

   TF1 *fun[2][2];
   for(int i=0;i<2;i++) {
     for(int j=0;j<2;j++) {
       fun[i][j] = new TF1(Form("fun_%d",i),Perp,x1,x2,3);
       fun[i][j]->SetParameters(mp[ip],eta_ref[j],y0[i]);
       fun[i][j]->SetRange(eta_ref[j]-y0[i], -y0[i]);
       fun[i][j]->SetLineStyle(i+1);
       fun[i][j]->SetLineColor(i+1);
       fun[i][j]->Draw("same");

       drawText(eta_ref[j]-y0[i]-0.15, 2.4, Form("#theta = %3.1f^{o}",theta[j]), 32, 0.045, 90, i+1);
     }
   }
   
   for(int i=0;i<2;i++) {
     drawLine(-y0[i], y1, -y0[i], y1+0.3, 2, i+1, i+1);
     drawText(-y0[i]-0.05, y1+0.35, Form("%3.1f",E_cms[i]), 32, 0.045, 0, i+1);
   }
   drawText(-2.3, 0.35, "#sqrt{s_{NN}}", 32, 0.05);

   drawLine(-0.5, 0.4, 0.5, 0.4, 2, 2, 4);
   drawLine(-0.5, 2.0, 0.5, 2.0, 2, 2, 4);
   drawLine(-0.5, 0.4, -0.5, 2.0, 2, 2, 4);
   drawLine(0.5, 0.4, 0.5, 2.0, 2, 2, 4);

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   c1->SaveAs(Form("accept%s.pdf",name[ip]));
   c1->SaveAs(Form("accept%s.png",name[ip]));
}
