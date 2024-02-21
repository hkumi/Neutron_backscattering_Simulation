#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetNtupleMerging(true);
    man->SetVerboseLevel( 1 );
    man->CreateNtuple("Photons", "Photons");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple(0);

    // Set axis titles

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleDColumn("BackscatteredEnergy");
    man->FinishNtuple(1);
    man->CreateNtuple("backscatteredtracklength", "backscatteredtracklength");
    man->CreateNtupleDColumn("BackscatteringTracklength");
    man->FinishNtuple(2);

    man->CreateNtuple("Scoring_1", "Scoring_1");
    man->CreateNtupleDColumn("TransmittedEnergy");
    man->FinishNtuple(3);
    man->CreateNtuple("transmittedtracklength", "transmittedtracklength");
    man->CreateNtupleDColumn("TransmittedTracklength");
    man->FinishNtuple(4);


    //man->CreateH2("xy1 ","xy1", 100, -3, 3, 100, -3, 3.0);

    //man->CreateH2("a1 ","angle vs energy_1", 100, 0, 100, 100, 0, 100.0);

    //man->CreateH1("z1 ","z1", 100,-100 , 100);





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
