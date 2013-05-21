void run(const char *infile)
{

  //Create histograms to fill
  TH1D *h1 = new TH1D( "opt1", "MC Pos. Mag. - Fitted Pos. Mag.; MC-Fit(mm); Counts", 200, -200, 200);

 TH1D *h2 = new TH1D( "opt2", "MC Pos. Mag. - Fitted Pos. Mag.; MC-Fit(mm); Counts", 200, -200, 200);

 //Create Gaussian fits to fit to histograms
 TF1 *fit1 = new TF1( "fit" , "gaus" ); 
 TF1 *fit2 = new TF1( "fit" , "gaus" );


 RAT::DSReader reader(infile); //Import File to DS reader
 RAT::DS::Root *rDS = reader.NextEvent();
 
 while(rDS != NULL) //Loop through DS events
    {
      //Get MC event position
      RAT::DS::MC *rMC = rDS->GetMC();
      TVector3 mcpos = rMC->GetMCParticle( 0 )->GetPos();

      //Get fitted event positions
      RAT::DS::EV *rEV = rDS->GetEV( 0 ); //Fitted data in EV
      RAT::DS::FitResult res1 = rEV->GetFitResult( "opt1" );
      TVector3 fitpos1 = res1.GetVertex(0).GetPosition();

      RAT::DS::FitResult res2 = rEV->GetFitResult( "opt2" );
      TVector3 fitpos2 = res2.GetVertex(0).GetPosition();
      
      h1->Fill(mcpos.Mag() - fitpos1.Mag()); //Fill with difference of mag. of position vectors
      h2->Fill(mcpos.Mag() - fitpos2.Mag()); //Same for second fitter


      rDS = reader.NextEvent(); //Loop to next event
    }

      //Assign colors to histograms and fits, and get rid of ugly stats box
      h1->SetLineColor(2);
      h2->SetLineColor(4);
      fit1->SetLineColor(2);
      fit2->SetLineColor(4);
      gStyle->SetOptStat(0);

      
      //Fit the Histograms
      h1->Fit(fit1);
      h2->Fit(fit2);

      //Draw the Histograms
      h1->Draw();
      h2->Draw("same");

}
