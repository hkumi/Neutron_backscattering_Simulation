#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetNtupleMerging(true);
    man->SetVerboseLevel( 1 );
    man->CreateNtuple("Photons", "Photons");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
   // man->CreateNtupleDColumn("fT");

    man->FinishNtuple(0);

    // Set axis titles
    

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(1);

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleDColumn("Edep");
    man->FinishNtuple(2);

    man->CreateNtuple("Scoring_1", "Scoring_1");
    man->CreateNtupleDColumn("E_silicon");
    man->FinishNtuple(3);

    man->CreateH1("Energy spectrum","Energy Spectrum",100,0.0,1.0*MeV);
    man->SetH1XAxisTitle(0, "Energy [MeV]");
    man->SetH1YAxisTitle(0, "Number of counts");

    man->CreateH2("dE-E","dE-E", 100, 0., 1.0*MeV, 100, 0., 1.0*MeV);
    man->SetH2XAxisTitle(0, "Energy [MeV]");
    man->SetH2YAxisTitle(0, "Number of counts");
    

}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{

     
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output"+strRunID.str()+".root");
}
void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
