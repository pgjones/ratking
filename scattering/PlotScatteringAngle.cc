#include <RAT/DS/Root.hh>
#include <RAT/DS/MC.hh>
#include <RAT/DS/Run.hh>
 
#include <TGraph.h>
#include <TTree.h>
#include <TFile.h>
 
#include <time.h>

using namespace std;
 
int graphPoint = 0;
 
void
FillHistogram( RAT::DS::MC* rMC,
               TGraph* nCer );

void
LoadRootFile( const char* lpFile,
              TTree **tree,
              RAT::DS::Root **rDS,
              RAT::DS::Run **rRun );

void
PlotScatteringAngle()
{
  // Load the root file first (This is the older style method, see the other examples for DSReader use)
  RAT::DS::Root* rDS;
  RAT::DS::Run* rRun;
  TTree *tree;
  LoadRootFile( "scattering.root", &tree, &rDS, &rRun );
  
  time_t codeStart = time( NULL );
  TGraph* scangle = new TGraph();
  
  for( int iEvent = 0; iEvent < tree->GetEntries(); iEvent++ )
    {
      if( iEvent % 100 == 0 )
        cout << iEvent << " finished at " << time( NULL ) - codeStart << endl;
      tree->GetEntry( iEvent );
      FillHistogram( rDS->GetMC(), scangle );
    }
  scangle->Draw("A*");
}
 
void
FillHistogram( RAT::DS::MC* rMC,
TGraph* scangle )
{
  for( int iTrack = 0; iTrack < rMC->GetMCTrackCount(); iTrack++ )
    {
      RAT::DS::MCTrack* rMCTrack = rMC->GetMCTrack( iTrack );
      if( rMCTrack->GetParentID() != 0 ) // Primary track has parent ID 0
        continue;
      TVector3 previousMom = rMCTrack->GetMCTrackStep( 0 )->GetMom(); // initial momentum
      double previousEnergy = rMCTrack->GetMCTrackStep( 0 )->GetKE(); // initial energy
      
      for( int iStep = 1; iStep < rMCTrack->GetMCTrackStepCount(); iStep++ )
        {
          RAT::DS::MCTrackStep* rMCTrackStep = rMCTrack->GetMCTrackStep( iStep );
          double theta = 180 / M_PI * acos( previousMom.Unit().Dot( rMCTrackStep->GetMom().Unit() ) ); // calculates scattering angle
          scangle->SetPoint( graphPoint++, previousEnergy, theta ); // graph scattering angle as function of energy
          previousMom = rMCTrackStep->GetMom();
          previousEnergy = rMCTrackStep->GetKE();
        }
    }
}

void
LoadRootFile( const char* lpFile,
              TTree **tree,
              RAT::DS::Root **rDS,
              RAT::DS::Run **rRun )
{
  TFile *file = new TFile( lpFile );
  (*tree) = (TTree*)file->Get( "T" );
  TTree *runTree = (TTree*)file->Get( "runT" );
  
  *rDS = new RAT::DS::Root();
  
  (*tree)->SetBranchAddress( "ds", &(*rDS) );
  
  *rRun = new RAT::DS::Run();
  
  runTree->SetBranchAddress( "run", &(*rRun) );
  runTree->GetEntry();
}

 
