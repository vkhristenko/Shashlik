#include "SHDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4UnitsTable.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"


/*
 *	Volume's dimensions
 */
//	World
//
G4double fullWorldX = 1.*m;
G4double fullWorldY = 1.*m;
G4double fullWorldZ = 1.*m;

//	Shashlik
//
G4double fullShashlikX = 14.*mm;
G4double fullShashlikY = 14.*mm;
G4double fullShashlikZ = 114.*mm;

//	Shashlik's container
//
G4double fullShashlikContainerX;
G4double fullShashlikContainerY;
G4double fullShashlikContainerZ = fullShashlikZ;

//	Absorber
//
G4double fullAbsX = 14.*mm;
G4double fullAbsY = 14.*mm;
G4double fullAbsZ = 2.5*mm;

//	Active Material
//
G4double fullActX = 14.*mm;
G4double fullActY = 14.*mm;
G4double fullActZ = 1.5*mm;

//	1 Layer
//
G4double fullLayerX = 14.*mm;
G4double fullLayerY = 14.*mm;
G4double fullLayerZ = fullAbsZ + fullActZ;

//	Fiber
//
G4double inRFiber = 0.*mm;
G4double outRFiber = 0.5*mm;
G4double fullAbsFiberZ = fullAbsZ;
G4double fullActFiberZ = fullActZ;

//	Gap
//
G4double fullGapX = 0.75*mm;
G4double fullGapY = 0.75*mm;

/*
 *	Member Functions
 */
SHDetectorConstruction::~SHDetectorConstruction()
{

}

// Constructor
//
SHDetectorConstruction::SHDetectorConstruction(RunParams params, 
		TTree *tree) :
	runParams(params),
	shTree(tree)
{
	//	Set the Shashlik's Container Dimensions
	//
	fullShashlikContainerX = runParams.numModules*fullShashlikX + 
		(runParams.numModules-1)*fullGapX;
	fullShashlikContainerY = runParams.numModules*fullShashlikY + 
		(runParams.numModules-1)*fullGapY;

	//	Let's build materials
	//
	G4double a; G4double z; G4double density;
	G4double weightRatio; G4String name; G4String symbol;
	G4int nElem; G4int natoms;

	//	Elements go first
	//
	G4Element *eC = new G4Element(name="Carbon", symbol="C", z=6., 
			a=12.01*g/mole);
	G4Element *eN = new G4Element(name="Nitrogen", symbol="N", z=7.,
			a=14.01*g/mole);
	eO = new G4Element(name="Oxygen", symbol="O", z=8,
			a=16.00*g/mole);
	G4Element *eFe = new G4Element(name="Iron", symbol="Fe", z=26.,
			a=55.845*g/mole);

	eLu = new G4Element(name="Lutetium", symbol="Lu", z=71.,
			a=174.97*g/mole);
	eSi = new G4Element(name="Silicium", symbol="Si", z=14.,
			a=28.09*g/mole);
	eY = new G4Element(name="Yttrium", symbol="Y", z=39.,
			a=88.91*g/mole);

	density = 2.700*g/cm3;
	a = 26.98*g/mole;
	G4Element *eAl = new G4Element(name="Aluminum", symbol="Al", z=13.,
			a);
	G4Element *eBe = new G4Element(name="Beryllium", symbol="Be", z=4, 
			a=9.012*g/mole);
	G4Element *eMg = new G4Element(name="Magnesium", symbol="Mg", z=12., 
			a=24.305*g/mole);
	G4Element *eTi = new G4Element(name="Titanium", symbol="Ti",  z=22., 
			a=47.867*g/mole);
	G4Element *eCs = new G4Element(name="Cesium", symbol="Cs", z=55., 
			a=132.90546*g/mole);
	G4Element *eSb = new G4Element(name="Antimony", symbol="Sb", z=51., 
			a=121.76*g/mole);
	G4Element *eGa = new G4Element(name="Gallium", symbol="Ga", z=31., 
			a=69.723*g/mole);
	G4Element *eP = new G4Element(name="Phosphorus", symbol="P", z=15., 
			a=30.97376*g/mole);
	G4Element *eAs = new G4Element(name="Arsenic", symbol="As", z=33., 
			a=74.9216*g/mole);
	G4Element *eIn = new G4Element(name="Indium", symbol="In", z=49., 
			a=114.818*g/mole);

	// Build the final compositions -> TODO
	//
	mAl2O3 = new G4Material(name="AluminumOxide", density=3.95*g/cm3, 
			nElem=2);
	mAl2O3->AddElement(eAl, natoms=2);
	mAl2O3->AddElement(eO, natoms=3);

	//mBeO = new G4Material(name="BerylliumOxide", density=3.02*g/cm3,
	//		nElem=2);
	mBeO = G4NistManager::Instance()->FindOrBuildMaterial("G4_BERYLLIUM_OXIDE");
//	mBeO->AddElement(eBe, natoms=1);
//	mBeO->AddElement(eO, natoms=1);
	
	mMgO = new G4Material(name="MagnesiumOxide", density=3.58*g/cm3,
			nElem=2);
	mMgO->AddElement(eMg, natoms=1);
	mMgO->AddElement(eO, natoms=1);

	mTiO = new G4Material(name="TitaniumOxide", density=4.23*g/cm3,
			nElem=2);
	mTiO->AddElement(eTi, natoms=1);
	mTiO->AddElement(eO, natoms=1);

	mCs3Sb = new G4Material(name="AntimonyTriCesium", density=3.076*g/cm3,
			nElem=2);
	mCs3Sb->AddElement(eCs, natoms=3);
	mCs3Sb->AddElement(eSb, natoms=1);
	
	mGaP = new G4Material(name="GalliumPhosphide", density=4.138*g/cm3,
			nElem=2);
	mGaP->AddElement(eGa, natoms=1);
	mGaP->AddElement(eP, natoms=1);

	mGaAsP = new G4Material(name="GalliumArsenicPhosphide", 
			density=4.482*g/cm3, nElem=3);
	mGaAsP->AddElement(eGa, natoms=1);
	mGaAsP->AddElement(eAs, natoms=1);
	mGaAsP->AddElement(eP, natoms=1);

	mGaPCs = new G4Material(name="GalliumCesiumPhosphide", 
			density=3.2*g/cm3, nElem=3);
	mGaPCs->AddElement(eGa, natoms=1);
	mGaPCs->AddElement(eP, natoms=1);
	mGaPCs->AddElement(eCs, natoms=1);

	mGaInP = new G4Material(name="GalliumIndiumPhosphide", 
			density=5.012*g/cm3, nElem=3);
	mGaInP->AddElement(eGa, natoms=1);
	mGaInP->AddElement(eIn, natoms=1);
	mGaInP->AddElement(eP, natoms=1);

	//mVacuum = new G4Material("Vacuum", z=1., a=1.008*g/mole, density=1.3-25*g/cm3, kStateGas, 2.73*kelvin, 3.e-18*pascal);	
//	mVacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
	
	density = universe_mean_density;
	G4double pressure = 1.e-19*pascal;
	G4double temperature = 0.1*kelvin;
	mVacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,
		kStateGas, temperature, pressure);

	//	Tungsten
	//
	mW = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

	//	SiO2 or Quartz
	//
	density = 2.648*g/cm3;
	mSiO2 = new G4Material(name="SiO2", density, nElem=2);
	mSiO2->AddElement(eSi, natoms=1);
	mSiO2->AddElement(eO, natoms=2);

	//	LYSO
	//
	mLYSO = new G4Material(name="LYSO", density=7.1*g/cm3, nElem=4);
	mLYSO->AddElement(eLu, 0.31101534);
	mLYSO->AddElement(eY, 0.368765605);
	mLYSO->AddElement(eSi, 0.083209699);
	mLYSO->AddElement(eO, 0.237009356);

	//
	//	Now, we have to build the Material's Properties Table
	//
	
	//	LYSO MPT
	//
	G4MaterialPropertiesTable *mptLYSO = new G4MaterialPropertiesTable();

	//	More realistic Emission Spectrum
	//
	const G4int NENTRIES = 27;
	G4double PHOTONENERGY_LYSO[NENTRIES] = {2.066333*eV, 2.101356*eV,
		2.137586*eV, 2.175088*eV, 2.213929*eV, 2.254182*eV, 2.295926*eV,
		2.339245*eV, 2.384231*eV, 2.43098*eV, 2.4796*eV, 2.530204*eV,
		2.582917*eV, 2.637872*eV, 2.695217*eV, 2.755111*eV, 2.817727*eV,
		2.883256*eV, 2.917176*eV, 2.951905*eV, 3.023902*eV, 3.0995*eV,
		3.178974*eV, 3.262632*eV, 3.350811*eV, 3.443889*eV, 3.542286*eV};
	G4double RINDEX_LYSO[NENTRIES] = {
		1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82,
		1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82, 1.82,
		1.82, 1.82, 1.82, 1.82, 1.82};
	G4double SLOW_LYSO[NENTRIES] = {
		0.000313, 0.000938, 0.003125, 0.00625, 0.009375, 0.01875, 0.025, 0.03125,
		0.046875, 0.0625, 0.0875, 0.125, 0.1875, 0.21875, 0.3125, 0.515625,
		0.6875, 0.84375, 0.94375, 0.9375, 0.9375, 1, 0.75, 0.5625, 0.0625,
		0.00625, 0.000313};
	//	For Debugging...
	//
	for (int i=0; i<NENTRIES; i++)
		cout << i << "  " << PHOTONENERGY_LYSO[i]/eV 
			<< "  " << SLOW_LYSO[i] << endl;

	mptLYSO->AddProperty("RINDEX", PHOTONENERGY_LYSO, RINDEX_LYSO, NENTRIES);
	mptLYSO->AddProperty("SLOWCOMPONENT", PHOTONENERGY_LYSO, SLOW_LYSO, NENTRIES);
	mptLYSO->AddConstProperty("SCINTILLATIONYIELD", 32000/MeV);
	mptLYSO->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptLYSO->AddConstProperty("SLOWTIMECONSTANT", 41.*ns);

/*	
	const G4int nEntries = 2;
	G4double photonEnergy[nEntries] = {1.5*eV, 6.2*eV};
	G4double refractiveIndex[nEntries] = {1.82, 1.82};
	G4double fast[nEntries] = {1, 1};
	G4double slow[nEntries] = {1, 1};
	mptLYSO->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);
	mptLYSO->AddProperty("FASTCOMPONENT", photonEnergy, fast, nEntries);
	mptLYSO->AddProperty("SLOWCOMPONENT", photonEnergy, slow, nEntries);

	mptLYSO->AddConstProperty("SCINTILLATIONYIELD", 32000/MeV);
	mptLYSO->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptLYSO->AddConstProperty("FASTTIMECONSTANT", 41.*ns);
	mptLYSO->AddConstProperty("SLOWTIMECONSTANT", 41.*ns);
	mptLYSO->AddConstProperty("YIELDRATIO", 0.5);
*/

	mLYSO->SetMaterialPropertiesTable(mptLYSO);
}

//	G4 Method
//
G4VPhysicalVolume* SHDetectorConstruction::Construct()
{
	return this->BuildGeometry();
}


//	Build all the Geometry
//	Include The EM Field, 
//
G4VPhysicalVolume* SHDetectorConstruction::BuildGeometry()
{
	//	Define World Dimensions
	//
//	G4double fullWorldZ = 1*m;
//	G4double fullWorldX = 1*m;
//	G4double fullWorldY = 1*m;

	//	Create the World iteself first
	//
	solidWorld = new G4Box("solidWorld", fullWorldX/2.0, fullWorldY/2.0, 
			fullWorldZ/2.0);
	logicWorld = new G4LogicalVolume(solidWorld, mVacuum, "logicWorld",
			0,0,0);
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld",
			0, 0, 0, false);

	//	Build the Shashlik Set of Modules
	//
	BuildShashlik();

	//	Return pointer to the WOrld
	//
	return physWorld;
}

/*
 *	Building the Shashlik itself
 */
void SHDetectorConstruction::BuildShashlik()
{
	//	SD
	//
	G4SDManager *SDManager = G4SDManager::GetSDMpointer();
	SHSDCounter *SD = new SHSDCounter("data", runParams, shTree);
	SDManager->AddNewDetector(SD);

	//	Place the Container first
	//
//	solidShashlikContainer = new G4Box("solidShashlikContainer",
//			fullShashlikContainerX/2., fullShashlikContainerY/2.,
//			fullShashlikContainerZ/2.);
//	logicShashlikContainer = new G4LogicalVolume(solidShashlikContainer,
//			mVacuum, "logicShashlikContainer", 0, 0, 0); 
//	physShashlikContainer = new G4PVPlacement(0, G4ThreeVector(),
//			logicShashlikContainer, "physShashlikContainer", logicWorld,
//			0, 0, true);

	//	Place the Shashlik Module
	//
//	solidShashlik = new G4Box("solidShashlik", fullShashlikX/2.0, 
//			fullShashlikY/2., fullShashlikZ/2.);
//	logicShashlik = new G4LogicalVolume(solidShashlik, mVacuum, "logicShashlik",
//			0, 0, 0);
//	for (int iModuleX=0; iModuleX<runParams.numModules; iModuleX++)
/*	{
		G4double xpos = -fullShashlikContainerX/2. + 
			fullShashlikX*(iModuleX + 0.5) + iModuleX*fullGapX;
		for (int iModuleY=0; iModuleY<runParams.numModules; iModuleY++)
		{
			G4double ypos = -fullShashlikContainerY/2. + 
				fullShashlikY*(iModuleY + 0.5) + iModuleY*fullGapY;
			physShashlik = new G4PVPlacement(0, G4ThreeVector(xpos, ypos, 0),
					logicShashlik, "physShashlik", logicShashlikContainer,
					0, 2*iModuleX + iModuleY, true);
		}
	}

*/
/*	//	Build the Layer Up without placing it...
	//
	solidLayer = new G4Box("solidLayer", fullLayerX/2., fullLayerY/2.,
			fullLayerZ/2);
	logicLayer = new G4LogicalVolume(solidLayer, mVacuum,
			"logicLayer", 0, 0, 0);

	//	Build the Abs Part and place it inside the Layer
	//
	solidAbs = new G4Box("solidAbs", fullAbsX/2., fullAbsY/2.,
			fullAbsZ/2.);
	logicAbs = new G4LogicalVolume(solidAbs, mW, "logicAbs", 0, 0, 0);
	physAbs = new G4PVPlacement(0, G4ThreeVector(0, 0, 
				-fullLayerZ/2. + fullAbsZ/2), logicAbs, "physAbs", logicLayer, 
			0, 0, true);


	//	Build and place AbsFibers inside the Abs
	//	4 Placements
	//
	solidAbsFiber = new G4Tubs("solidAbsFiber", inRFiber, outRFiber, 
			fullAbsFiberZ/2., 0, 360*deg);
	logicAbsFiber = new G4LogicalVolume(solidAbsFiber, mSiO2,
			"logicAbsFiber", 0, SD, 0);
	for (int i=0; i<=1; i++)
	{
		G4double xpos = -0.5*fullAbsX + 0.25*fullAbsX + i*0.5*fullAbsX;
		for (int j=0; j<=1; j++)
		{
			G4double ypos = -0.5*fullAbsY + 0.25*fullAbsY + j*0.5*fullAbsY;
			physAbsFiber = new G4PVPlacement(0, G4ThreeVector(xpos, ypos, 0),
					logicAbsFiber, "physAbsFiber", logicAbs, 0, 2*i+j, true);
		}
	}
*/
	//
	//	Layer of vacuum right in front of Act
	//
	G4Box *sLayer = new G4Box("sLayer", fullActX/2., fullActY/2., 1*mm);
	G4LogicalVolume *lLayer = new G4LogicalVolume(sLayer, mVacuum, "lLayer");
	new G4PVPlacement(0, G4ThreeVector(0, 0, -fullActZ/2. -1*mm),
			lLayer, "pLayer", logicWorld, 0, 0, true);

	//	Build the Act Part and place it inside the Layer
	//
	solidAct = new G4Box("solidAct", fullActX/2., fullActY/2., fullActZ/2.);
	logicAct = new G4LogicalVolume(solidAct, mLYSO,
			"logicAct", 0, SD, 0);
	physAct = new G4PVPlacement(0, G4ThreeVector(0, 0, 0),
			logicAct, "physAct", logicWorld, 0, 0, true);

	sLayer = new G4Box("sLayer", fullActX/2., fullActY/2., 1*mm);
	lLayer = new G4LogicalVolume(sLayer, mVacuum, "lLayer");
	new G4PVPlacement(0, G4ThreeVector(0, 0, fullActZ/2. + 1*mm),
			lLayer, "pLayer", logicWorld, 0, 0, true);


/*
	//	Build and place ActFibers inside the Act
	//	4 Placements
	//
	solidActFiber = new G4Tubs("solidActFiber", inRFiber, outRFiber,
			fullActFiberZ/2., 0, 360*deg);
	logicActFiber = new G4LogicalVolume(solidActFiber, mSiO2,
			"logicActFiber", 0, SD, 0);
	for (int i=0; i<=1; i++)
	{
		G4double xpos = -0.5*fullActX + 0.25*fullActX + i*0.5*fullActX;
		for (int j=0; j<=1; j++)
		{
			G4double ypos = -0.5*fullActY + 0.25*fullActY + j*0.5*fullActY;
			physActFiber = new G4PVPlacement(0, G4ThreeVector(xpos, ypos,0),
					logicActFiber, "physActFiber", logicAct, 0, 2*i+j, true);
		}
	}

	//	A single Layer has been Built, but NOT Placed!!!
	//	Place all of them
	//
	for (int iLayer=0; iLayer<runParams.numLayers; iLayer++)
	{
		G4double zpos = -fullShashlikZ/2.+ fullActZ + fullLayerZ*(iLayer + 0.5);
		physLayer = new G4PVPlacement(0, G4ThreeVector(0,0,zpos),
				logicLayer, "physLayer", logicShashlik, 0, iLayer, true);
	}

	//	Note: We put Abs first into the module, but the number of LYSO plates 
	//	should be more by 1 ===>>> place a LYSO just inside the Shashlik.
	//	NOTE: We arrange a spot for that just above
	//
	physAct = new G4PVPlacement(0, G4ThreeVector(0,0,
				-fullShashlikZ/2. + fullActZ/2.), logicAct, "physAct", 
			logicShashlik, 0, runParams.numLayers, true);	

*/

	//	Optical Surgace for the Shashlik's LYSO
	//
/*	G4OpticalSurface *opShashlikSurface = new G4OpticalSurface("ShashlikSurface");
	opShashlikSurface->SetType(dielectric_metal);
	opShashlikSurface->SetFinish(polishedtyvekair);
	opShashlikSurface->SetModel(glisur);
	G4MaterialPropertiesTable *mptSurface = new G4MaterialPropertiesTable();
	G4double reflectivity[2] = {1.0, 1.0};
	G4double photonEnergy[2] = {1.5*eV, 6.2*eV};
	mptSurface->AddProperty("REFLECTIVITY", photonEnergy, reflectivity, 2);
	opShashlikSurface->SetMaterialPropertiesTable(mptSurface);

	G4LogicalSkinSurface *skinSurface = new G4LogicalSkinSurface("Skin",
			logicAct, opShashlikSurface);
*/
	return;
}











