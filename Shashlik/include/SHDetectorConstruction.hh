#ifndef SHDETECTORCONSTRUCTION_H
#define SHDETECTORCONSTRUCTION_H 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include <vector>

#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4VSolid.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "SHDefs.hh"
#include "SHSDCounter.hh"

using namespace CLHEP;

class SHDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		//	Constructor and Destructor
		SHDetectorConstruction(RunParams, TTree *tree);
		~SHDetectorConstruction(); 

		G4VPhysicalVolume* Construct();
		G4VPhysicalVolume* BuildGeometry();
		void BuildShashlik();
		void UpdateGeometry();

		RunParams runParams;
		TTree *shTree;

		//	List of Materials/Elements
		//	mAl2O3 Index of 0 and mGaInP index of 8
		G4Element *eLu;
		G4Element *eY;
		G4Element *eSi;
		G4Element *eO;
		
		//	Materials
		//
		G4Material *mAir;
		G4Material *mFe;
		G4Material *mVacuum;
		G4Material *mAl2O3;
		G4Material *mBeO;
		G4Material *mMgO;
		G4Material *mTiO;
		G4Material *mCs3Sb;
		G4Material *mGaP;
		G4Material *mGaAsP;
		G4Material *mGaPCs;
		G4Material *mGaInP;
		G4Material *mW;
		G4Material *mLYSO;
		G4Material *mSiO2;

		//
		//	Volumes
		//

		//	World
		//	/
		G4Box *solidWorld;
		G4LogicalVolume *logicWorld;
		G4VPhysicalVolume *physWorld;

		//	Shashlik's Container
		//
		G4Box *solidShashlikContainer;
		G4LogicalVolume *logicShashlikContainer;
		G4VPhysicalVolume *physShashlikContainer;

		//	Shashlik Full Length Module
		//
		G4Box *solidShashlik;
		G4LogicalVolume *logicShashlik;
		G4VPhysicalVolume *physShashlik;

		//	1 Layer: Abs + Act Part
		//
		G4Box *solidLayer;
		G4LogicalVolume *logicLayer;
		G4VPhysicalVolume *physLayer;

		//	Absorber
		//
		G4Box *solidAbs;
		G4LogicalVolume *logicAbs;
		G4VPhysicalVolume *physAbs;

		//	Act
		//
		G4Box *solidAct;
		G4LogicalVolume *logicAct;
		G4VPhysicalVolume *physAct;

		//	Fiber: 2 kinds
		//	1) Abs
		//	2) Act
		//
		G4Tubs *solidAbsFiber;
		G4LogicalVolume *logicAbsFiber;
		G4VPhysicalVolume *physAbsFiber;

		G4Tubs *solidActFiber;
		G4LogicalVolume *logicActFiber;
		G4VPhysicalVolume *physActFiber;
};
#endif











