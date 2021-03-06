/////////////////////////////////////////////////
// Fast MC for pointing resolution calculation
//    MCS + single hit resolution
//    First two active layers considered
////////////////////////////////////////////////

/*
void FreeStreaming(TVector3 pos_0, TVector3 mom_0, float s_z, TVector3 pos_1, TVector3 mom_1)
{
}
*/
double theta0(double p, double m, double dx)
{
  double beta = p/TMath::Sqrt(p*p+m*m);
  return 0.0136/beta/p*TMath::Sqrt(dx)*(1.+0.038*TMath::Log(dx/beta/beta));
}

void FastMC()
{
  const Int_t Nevt = 100000.;
  const Int_t N_STS = 3;
  const Double_t M_Pi = 0.13957;
  const Double_t z_STS[N_STS] = {0., 2.8, 8.};   // z location in cm
  const Double_t thick_STS[N_STS] = {0., 0.4, 0.4};  // thickness in %X0
  const Double_t a_STS[N_STS] = {0., 20., 20.};     // pitch size in micron
  const Double_t theta_STS[2] = {2.5, 25};    // theta angle acceptance (min, max)

  TRandom3 *gRandom = new TRandom3();

  //
  TH2D *hImpact = new TH2D("impact","",100,0.,5.0,1000,-0.1,0.1);
  TH2D *hDcaP = new TH2D("dcaP","",100,0.,5.0,1000,-0.1,0.1);
  TH2D *hDcaPt = new TH2D("dcaPt","",100,0.,1.0,1000,-0.1,0.1);
  
  for(int i=0;i<Nevt; i++) {
    //   double theta = (gRandom->Rndm()*(theta_STS[1]-theta_STS[0]) + theta_STS[0])*TMath::Pi()/180.;
    double theta = 10./180.*TMath::Pi();
    double p = gRandom->Rndm()*5.0;
    double pt = p*TMath::Sin(theta);

    double x_mc[N_STS], y_mc[N_STS];
    double x_rec[N_STS], y_rec[N_STS];
    x_mc[0] = 0.;
    y_mc[0] = 0.;
    double theta_in[N_STS], theta_out[N_STS];
    theta_in[0] = theta;
    theta_out[0] = theta_in[0];
    for(int il=1; il<=N_STS;il++) {
      x_mc[il] = x_mc[il-1] + (z_STS[il] - z_STS[il-1]) * TMath::Tan(theta_out[il-1]);
      x_rec[il] = x_mc[il] + gRandom->Gaus(0, a_STS[il]/sqrt(12.)) * 1.e-4;
      //      x_rec[il] = x_mc[il] + gRandom->Gaus(0, a_STS[il]) * 1.e-4;

      theta_in[il] = theta_out[il-1];
      theta_out[il] = theta_in[il] + gRandom->Gaus(0, theta0(p, M_Pi, thick_STS[il]/TMath::Cos(theta_in[il])/100.));
      //            theta_out[il] = theta_in[il];      
    }

    double k_rec = (x_rec[2] - x_rec[1])/(z_STS[2]-z_STS[1]);
    double b_rec = x_rec[1] - k_rec * z_STS[1];
    double theta_rec = TMath::ATan(k_rec);
    double dca_rec = b_rec * TMath::Cos(theta_rec);
    hDcaP->Fill(p, dca_rec*sqrt(2.));
    hDcaPt->Fill(pt, dca_rec*sqrt(2.));
    hImpact->Fill(p, b_rec*sqrt(2.));
    
  }

  TFile *fout = new TFile("test.root","recreate");
  hDcaP->Write();
  hDcaPt->Write();
  hImpact->Write();
  fout->Close();
  
}
