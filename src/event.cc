#include "event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
  


}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
   
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
       G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
       G4int numberOfEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();

       G4AnalysisManager *man = G4AnalysisManager::Instance();
       //theCollID.push_back(evt);
       //G4int Ncol = theCollID.size();
       //G4cout << "total number of Neutrons in Scorer_1:"<< Ncol << G4endl;


       /*if (fEdep > 0.0) {
          //G4cout << "Number of events: " << evt << G4endl;
          //G4cout << "Energy deposition: " << fEdep*MeV << G4endl;
          man->FillNtupleDColumn(1, 0, fEdep);
          man->AddNtupleRow(1);
          //theCollID.push_back(evt);
          //G4int Ncol = theCollID.size();
          //G4cout << "total number of Neutrons in Scorer_1:"<< Ncol << G4endl;


       }*/

       

   

}
