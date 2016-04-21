#include "SHPrimaryGeneratorAction.hh"

#include <iostream>

#include "G4HEPEvtInterface.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "CLHEP/Random/RandFlat.h"
#include "G4RunManager.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"

using namespace CLHEP;
using namespace std;

const int numEnergies = 8;
G4double primEnergies[numEnergies] = {
	1.*GeV, 2.*GeV, 4.*GeV, 8.*GeV, 16.*GeV, 32.*GeV, 50.*GeV, 60.*GeV
};

//	Constructor
//
SHPrimaryGeneratorAction::SHPrimaryGeneratorAction(RunParams params, TTree *tree)
	: runParams(params),
	shTree(tree)
{
	//	Define a generator
	//
	primEnergy = primEnergies[runParams.iEnergy];
	primName = "e-";
	particleGun = new G4ParticleGun(1);
	particleGun->SetParticleEnergy(primEnergy);
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle(primName);
	particleGun->SetParticleDefinition(particle);

	primPos = G4ThreeVector(0, 0, -0.49*m);
	primDir = G4ThreeVector(0.*m, 0.*m, 1.0*m);
	particleGun->SetParticlePosition(primPos);
	particleGun->SetParticleMomentumDirection(primDir);
	particleGun->SetParticleEnergy(primEnergy);
}

//	Destructor
//
SHPrimaryGeneratorAction::~SHPrimaryGeneratorAction()
{
	delete particleGun;
}

//	Generate Primary Event
//
void SHPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	//	All gun's settings have been set up in Constructor
	//
	//particleGun->SetParticleEnergy(10.*keV);
	cout << particleGun->GetParticleEnergy()/GeV << endl; 
	particleGun->GeneratePrimaryVertex(anEvent);
}
