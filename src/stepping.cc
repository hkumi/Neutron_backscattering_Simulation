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

     G4Track* track = step->GetTrack();
     G4double TrackID = step->GetTrack()->GetTrackID();
     //track->SetTrackStatus(fStopAndKill);
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

     if (volume == fScoringVolume_1){
        //fEventAction->AddEdep(edep);
        if (step->IsFirstStepInVolume() ){
          // preStepPoint = step->GetPreStepPoint();
          // postStepPoint = step->GetPostStepPoint();
           //G4double ekin_1  = postStepPoint->GetKineticEnergy()/MeV;
           //G4ThreeVector p0_1 = postStepPoint->GetMomentumDirection();
           //G4double angle_1 = std::acos(p0_1.z());
           //G4ThreeVector posPhoton1 = postStepPoint->GetPosition()/m;

           //man->FillH2(0, posPhoton1[0], posPhoton1[1]);
           //man->FillH2(0, angle_1/deg, ekin_1);

           //man->FillH1(0,  posPhoton1[0]);
           //theEvntID.push_back(evt);
           //Ncol = theEvntID.size();
           //Ncol++;
           man->FillNtupleDColumn(1, 0, TrackID);
           man->AddNtupleRow(1);
           totalNeutronsInScorer1++;
           // Print out the total number of neutrons in fScoringVolume_1
           //G4cout << "Total number of Neutrons in Scorer_1: " << totalNeutronsInScorer1 << G4endl;


           //man->FillNtupleDColumn(12, 0, angle_1/deg);
           //man->AddNtupleRow(12);

      /*

        if(preStepPoint->GetStepStatus() == fGeomBoundary && ekin_1 >= 1.5 && ekin_1 <= 1.6) {
          G4cout << "Step starts on geometry boundary" << G4endl;
          G4double elos = step->GetTotalEnergyDeposit();
          G4cout << "energy  at 1.5MeV =  "<< ekin_1 << G4endl;
          man->FillNtupleDColumn(12, 0, elos);
          man->AddNtupleRow(12);
 */

        }
           //man->FillNtupleDColumn(12, 0, energy);
           //man->AddNtupleRow(12);
        //}
     }
     
     

    

  
  //else
  //{
    //step->GetTrack()->SetTrackStatus(fStopAndKill);
  //}
  }
}
