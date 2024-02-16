#include "construction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include <algorithm>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{

    DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{

  G4NistManager *nist = G4NistManager::Instance();
  G4int ncomponents, natoms;
  G4double massfraction;

  G4double Vdens = 1.e-25*g/cm3;
  G4double Vpres = 1.e-19*pascal;
  G4double Vtemp = 0.1*kelvin;
  
  G4double a, z;
  C = nist->FindOrBuildElement("C");
  N  = new G4Element("Nitrogen","N",7.,14.007*g/mole);
  O  = new G4Element("Oxygen","O",8.,15.999*g/mole);
  F  = new G4Element("Fluorine","F",9.,18.998*g/mole);
  Al = new G4Element("Aluminium", "Al", 13., 26.982*g/mole);
  Si = new G4Element("Silicon","Si",z= 14., a= 28.085*g/mole);
  Fe = new G4Element("Iron","Fe",z= 26., a= 55.85*g/mole);


   // Water
  auto H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
  water = new G4Material("Water",  1.0 * g / cm3,  ncomponents=2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

  // vacuum
  Vacc = new G4Material("Galactic", z=1, a=1.01*g/mole, Vdens, kStateGas, Vtemp, Vpres);
  // air
  G4Element* N = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
  Air = new G4Material("air", 1.290*mg/cm3, ncomponents=2, kStateGas, 293*kelvin, 1*atmosphere);
  Air->AddElement(N, massfraction=70.*perCent);
  Air->AddElement(O, massfraction=30.*perCent);

    // polyethilene
  G4Element* Hpe = new G4Element("TS_H_of_Polyethylene", "H", 1, 1.0079*g/mole);
  G4Element* Cpe = new G4Element("Carbon", "C", 6, 12.01*g/mole);
  polyethylene = new G4Material("polyethylene", 0.93*g/cm3, ncomponents=2, kStateSolid, 293*kelvin, 1*atmosphere);
  polyethylene->AddElement(Hpe, natoms=4);
  polyethylene->AddElement(Cpe, natoms=2);
  
  //rock material. 

   //rock
    rock = new G4Material("rock", 2.8*g/cm3, 5);
    rock->AddElement(O, massfraction=46.1*perCent);
    rock->AddElement(Si, massfraction=28.2*perCent);
    rock->AddElement(Al, massfraction=8.2*perCent);
    rock->AddElement(Fe, massfraction=5.6*perCent);
    rock->AddElement(C, massfraction=11.9*perCent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::ConstructScorer(G4double Pos_PPAC_1)
{

// scores
  G4double ScThick_1 =  0.5*m;

  auto sScore_1 = new G4Box("sScore_1",
                            2.5/2*m,2.5/2*m,ScThick_1/2);

  auto fLScore_1 = new G4LogicalVolume(sScore_1,
                                        polyethylene,
                                      "fLScore_1");

  auto fPScore_r_1 = new G4PVPlacement(0,
                                    G4ThreeVector(0.*mm,0.*mm,Pos_PPAC_1),
                                    fLScore_1,
                                    "fPScore_r_1",
                                    fLBox,
                                    false,
                                    0,true);
  fScoringVolume_1 = fLScore_1;
}



void DetectorConstruction::Rock( G4double position) { 
     G4Box* rockbox = new G4Box("rockbox", 1.5*m/2, 1.5*m/2 , 1.0*m/2);
     G4LogicalVolume* rockVolume = new G4LogicalVolume(rockbox, rock, "Rock");
     G4PVPlacement* rockPlacement  = new G4PVPlacement(0,
                                               G4ThreeVector(0.*mm, 0.*mm, position),
                                               rockVolume,
                                               "Rock",
                                               fLBox,
                                               false,
                                               0,true);
     G4VisAttributes* blue = new G4VisAttributes(G4Colour::Blue());

     blue->SetVisibility(true);
     blue->SetForceAuxEdgeVisible(true);


     rockVolume->SetVisAttributes(blue);


}

void DetectorConstruction::waterwall( G4double position1) { 
     G4Box* waterbox = new G4Box("rockbox", 1.5*m/2, 1.5*m/2 , 0.5*m/2);
     G4LogicalVolume* waterVolume = new G4LogicalVolume(waterbox, water, "Water");
     G4PVPlacement* waterPlacement  = new G4PVPlacement(0,
                                               G4ThreeVector(0.*mm, 0.*mm, position1),
                                               waterVolume,
                                               "Water",
                                               fLBox,
                                               false,
                                               0,true);
     G4VisAttributes* Red = new G4VisAttributes(G4Colour::Red());

     Red->SetVisibility(true);
     Red->SetForceAuxEdgeVisible(true);


     waterVolume->SetVisAttributes(Red);


}



G4VPhysicalVolume *DetectorConstruction::Construct()
{

  fBoxSize = 6*m;


  sBox = new G4Box("world",                             //its name
                   fBoxSize/2,fBoxSize/2,fBoxSize/2);   //its dimensions

  fLBox = new G4LogicalVolume(sBox,                     //its shape
                             Vacc,                      //its material
                             "World");                  //its name

  fPBox = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(),            //at (0,0,0)
                            fLBox,                      //its logical volume
                            "World",                    //its name
                            0,                          //its mother  volume
                            false,                      //no boolean operation
                            0);                         //copy number

  Rock(0.7*m); 
  waterwall(1.45*m);
  ConstructScorer(-0.5*m);

 


  return fPBox;
}

//...ooooooooooooooooo..................................oooooooooooooooooooo......



void DetectorConstruction::ConstructSDandField()
{
 // sensitive detectors -----------------------------------------------------
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->SetVerboseLevel(0);

  //Define Multi-Detector and Register 
  //--------------------------------------------------------------------------------------------
  G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("IonPro");
  SDman->AddNewDetector(det);
//  fLScore->SetSensitiveDetector(det);
}
