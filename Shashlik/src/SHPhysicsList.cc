#include "globals.hh"
#include "SHPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4ProcessManager.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

//	factory
//
#include "G4PhysicsConstructorFactory.hh"
G4_DECLARE_PHYSCONSTR_FACTORY(SHPhysicsList);

using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SHPhysicsList::SHPhysicsList() 
 : G4VPhysicsConstructor("Optical"),
   fCerenkovProcess(NULL),
	fScintillationProcess(NULL)
{
//  fMessenger = new OpNovicePhysicsListMessenger(this);
	SetVerboseLevel(0);
	SetPhysicsType(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SHPhysicsList::~SHPhysicsList() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SHPhysicsList::ConstructParticle()
{

  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  G4BosonConstructor bConstructor;
  bConstructor.ConstructParticle();

  /*
  G4LeptonConstructor lConstructor;
  lConstructor.ConstructParticle();

  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();

  G4BaryonConstructor rConstructor;
  rConstructor.ConstructParticle();

  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle(); 
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SHPhysicsList::ConstructProcess()
{
//  AddTransportation();
//  ConstructDecay();
//  ConstructEM();
  ConstructOp();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void SHPhysicsList::ConstructDecay()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) {
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void SHPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {
    // gamma
      // Construct processes for gamma
      pmanager->AddDiscreteProcess(new G4GammaConversion());
      pmanager->AddDiscreteProcess(new G4ComptonScattering());
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());

    } else if (particleName == "e-") {
    //electron
      // Construct processes for electron
      pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);

    } else if (particleName == "e+") {
    //positron
      // Construct processes for positron
      pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation(),  0,-1, 4);

    } else if( particleName == "mu+" ||
               particleName == "mu-"    ) {
    //muon
     // Construct processes for muon
     pmanager->AddProcess(new G4MuMultipleScattering(),-1, 1, 1);
     pmanager->AddProcess(new G4MuIonisation(),      -1, 2, 2);
     pmanager->AddProcess(new G4MuBremsstrahlung(),  -1, 3, 3);
     pmanager->AddProcess(new G4MuPairProduction(),  -1, 4, 4);

    } else {
      if ((particle->GetPDGCharge() != 0.0) &&
          (particle->GetParticleName() != "chargedgeantino") &&
          !particle->IsShortLived()) {
       // all others charged particles except geantino
       pmanager->AddProcess(new G4hMultipleScattering(),-1,1,1);
       pmanager->AddProcess(new G4hIonisation(),       -1,2,2);
     }
    }
  }
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SHPhysicsList::ConstructOp()
{
//	fCerenkovProcess           = new G4Cerenkov("Cerenkov");
	fScintillationProcess      = new G4Scintillation("Scintillation");
//	fAbsorptionProcess         = new G4OpAbsorption();
//	fRayleighScatteringProcess = new G4OpRayleigh();
//	fMieHGScatteringProcess    = new G4OpMieHG();
//	fBoundaryProcess           = new G4OpBoundaryProcess();

//  fCerenkovProcess->DumpPhysicsTable();
	fScintillationProcess->DumpPhysicsTable();
//  fRayleighScatteringProcess->DumpPhysicsTable();


//  SetVerbose(1);
  
  //fCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  //fCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  //fCerenkovProcess->SetTrackSecondariesFirst(true);
  
	G4double yieldLYSO = 32/MeV;
	fScintillationProcess->SetScintillationYieldFactor(1);
//	fScintillationProcess->SetResolutionScale(1.0);
//	fScintillationProcess->SetScintillationTime(41*ns);
	fScintillationProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process
  //

//  G4EmSaturation* emSaturation =
  //                             G4LossTableManager::Instance()->EmSaturation();
//  fScintillationProcess->AddSaturation(emSaturation);

	//	From User's Guide: 
	//	To enable just Cerenkov Process - NOTHING ELSE
	//
/*	theParticleIterator->reset();
	while ((*theParticleIterator)())
	{
		G4ParticleDefinition *particle = theParticleIterator->value();
		G4ProcessManager *pManager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		if (fScintillationProcess->IsApplicable(*particle))
		{
			pManager->AddProcess(fScintillationProcess);
			pManager->SetProcessOrderingToLast(fScintillationProcess, idxAtRest);
			pManager->SetProcessOrderingToLast(fScintillationProcess, 
					idxPostStep);
		}
	}
*/
  /*
   *	Code below came from OpNovice Example
   *	Code just above had been found from User's Guide
   */



  aParticleIterator->reset();
  while( (*aParticleIterator)() ){
    G4ParticleDefinition* particle = aParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
//    if (fCerenkovProcess->IsApplicable(*particle)) {
//      pmanager->AddProcess(fCerenkovProcess);
//      pmanager->SetProcessOrdering(fCerenkovProcess,idxPostStep);
//    }
    if (fScintillationProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(fScintillationProcess);
      pmanager->SetProcessOrderingToLast(fScintillationProcess, idxAtRest);
      pmanager->SetProcessOrderingToLast(fScintillationProcess, idxPostStep);
    }
/*    if (particleName == "opticalphoton") {
      G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
    //  pmanager->AddDiscreteProcess(fAbsorptionProcess);
    //  pmanager->AddDiscreteProcess(fRayleighScatteringProcess);
    //  pmanager->AddDiscreteProcess(fMieHGScatteringProcess);
      pmanager->AddDiscreteProcess(fBoundaryProcess);
    }
	*/
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SHPhysicsList::SetVerbose(G4int verbose)
{
//  fCerenkovProcess->SetVerboseLevel(verbose);
/*  
  fScintillationProcess->SetVerboseLevel(verbose);
  fAbsorptionProcess->SetVerboseLevel(verbose);
  fRayleighScatteringProcess->SetVerboseLevel(verbose);
  fMieHGScatteringProcess->SetVerboseLevel(verbose);
  fBoundaryProcess->SetVerboseLevel(verbose);
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void OpNovicePhysicsList::SetNbOfPhotonsCerenkov(G4int MaxNumber)
{
  fCerenkovProcess->SetMaxNumPhotonsPerStep(MaxNumber);
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void SHPhysicsList::SetCuts()
{
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types
  //
  SetCutsWithDefault();

  //if (verboseLevel>0) DumpCutValuesTable();
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
