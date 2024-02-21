#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  if (step->GetTrack()->GetDefinition()->GetParticleName() == "neutron" ) {
     G4AnalysisManager *man = G4AnalysisManager::Instance();

     const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
     G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

     G4LogicalVolume *fScoringVolume_1 = detectorConstruction->GetScoringVolume();
     G4LogicalVolume *fScoringVolume_2 = detectorConstruction->GetScoringVolume_2();

     G4Track* track = step->GetTrack();
     G4double TrackID = step->GetTrack()->GetTrackID();
     G4int stepNumber = track->GetCurrentStepNumber();
     //G4cout << "the track material:" << TrackID << G4endl; 


     G4double edep = step->GetTotalEnergyDeposit();
    
     // If it's the first step in the volume, save the position.
     G4ThreeVector posPhoton; 
     G4StepPoint *preStepPoint; 
     G4StepPoint *postStepPoint ;   
     G4double ekin_1 ;
     std::vector<G4int> theEvntID; 
     G4int Ncol;
     Ncol = 0;
     G4int totalNeutronsInScorer1 = 0;

      G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    // for transmitted events.  
     if (volume == fScoringVolume_1){
        //fEventAction->AddEdep(edep);
        if (step->IsFirstStepInVolume() ){
            preStepPoint = step->GetPreStepPoint();
            postStepPoint = step->GetPostStepPoint();
            G4double ekin_1  = postStepPoint->GetKineticEnergy()/MeV;
            G4double length_1 = step->GetTrack()->GetTrackLength()/m;
            man->FillNtupleDColumn(1, 0, ekin_1);
            man->AddNtupleRow(1);
            man->FillNtupleDColumn(2, 0, length_1);
            man->AddNtupleRow(2);

           totalNeutronsInScorer1++;
 
        }
           
     }
     // for backscattered events
     if (volume == fScoringVolume_2){
        //fEventAction->AddEdep(edep);
        if (step->IsFirstStepInVolume() ){
            preStepPoint = step->GetPreStepPoint();
            postStepPoint = step->GetPostStepPoint();
            G4double ekin_2  = postStepPoint->GetKineticEnergy()/MeV;
            G4double length_2 = step->GetTrack()->GetTrackLength()/m;
            man->FillNtupleDColumn(3, 0, ekin_2);
            man->AddNtupleRow(3);
            man->FillNtupleDColumn(4, 0, length_2);
            man->AddNtupleRow(4);

          
            
        }
            
     }
  }
}
