#include "SHSDCounter.hh"
#include "G4UnitsTable.hh"
#include "G4TrackStatus.hh"
#include "G4VProcess.hh"

#include <iostream>

using namespace std;
using namespace CLHEP;

//	Constructor
//
SHSDCounter::SHSDCounter(G4String name, RunParams inData, TTree *tree)
	: G4VSensitiveDetector(name),
	runParams(inData)
{
	shTree = tree;
	shTree->Branch("numPhotons", &numPhotons, "numPhotons/D");
	shTree->Branch("eneDep", &eneDep, "eneDep/D");
	shTree->Branch("myNumPhotons", &myNumPhotons, "myNumPhotons/D");
	//opTree->Branch("op_pe", pe, "pe[10]/D");
	//
	rand.SetSeed(runParams.seed);	
	
}

//	Destructor
//
SHSDCounter::~SHSDCounter()
{

}

//	Initialize
//
void SHSDCounter::Initialize(G4HCofThisEvent*)
{
	//	Clear
	//
	numPhotons = 0;
	eneDep = 0;
	myNumPhotons = 0;
}

//	Process Hits
//
G4bool SHSDCounter::ProcessHits(G4Step *aStep, G4TouchableHistory*)
{
	//	Process
	//
	
	//cout << "Inside the Counter..." << endl;
	//cout << "PName: " << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << endl;
	if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == 
			"opticalphoton")
	{
/*		if (runParams.verbosity>1)
		{
			G4cout << "### SD: Optical Photon..." << G4endl;
			G4cout << "### Creator Process Name: " 
				<< aStep->GetTrack()->GetCreatorProcess()->GetProcessName() 
				<< "  "
				<< aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()
				<< G4endl;
		}
*/
		numPhotons++;
//		aStep->GetTrack()->SetTrackStatus(fStopAndKill);
	}

	if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() != "opticalphoton")
	{
		double thisDep = aStep->GetTotalEnergyDeposit()/MeV;
		eneDep += thisDep;
		int gen = ComputeOPH(thisDep, 32000);
		myNumPhotons += gen;
		if (runParams.verbosity>1)
		{
			G4cout << "### " << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << "  " << aStep->GetTrack()->GetKineticEnergy()/MeV << G4endl;
			G4cout << "### " << aStep->GetTotalEnergyDeposit() << "  "
				<< aStep->GetNonIonizingEnergyDeposit() << G4endl;
			G4cout << "### Photons Generated= " << gen << G4endl;
	//		if (aStep->GetSecondary()!=NULL)
	//			G4cout << 
//			G4cout << "### Creator Process Name: "
//				<< aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()
		}
	}

	return true;
}

//	Get the PMT ID by name
//
int SHSDCounter::GetPMT(G4String name)
{
	int pos_ = name.find("_");
	string strID = name.substr(pos_+1, name.length());
	return atoi(strID.c_str());
}

//	Get the Number of Photoelectrons
//
double SHSDCounter::GetPENum(G4double lyambda)
{
/*	//	For wavelength ourside of our range...
	//
	if ((lyambda > QPE[numBins-1][0]*nm) or (lyambda < QPE[0][0]*nm))
		return 0;

	//	If lyambda is equal to lower edge of our spectrum
	//
	if (lyambda == QPE[0][0]*nm)
		return QPE[0][1];

	//	If lyamda is equal to the upper edge of our spectrum
	//
	if (lyambda == QPE[numBins-1][0]*nm)
		return QPE[numBins - 1][1];

	//	Proceed... Find the right bin for interpolation
	//
	int l2pos = 0;
	while (lyambda > QPE[l2pos][0]*nm)
		l2pos++;
	double pes = ComputePE(l2pos-1, l2pos, lyambda/nm);

	return pes;
	*/
	return 0;
}

//	Interpolate/Compute QPE
//
double SHSDCounter::ComputePE(int b1, int b2, double x)
{
/*	double x1 = QPE[b1][0];
	double x2 = QPE[b2][0];
	double y1 = QPE[b1][1];
	double y2 = QPE[b2][1];
	double y = y1 + (y2 - y1)*(x - x1)/(x2 - x1);
	return y;
	*/
}

//
//	COmpute # Optical Photons
//
int SHSDCounter::ComputeOPH(double ene, double opPerMeV)
{
	int genPhotons = 0;
	double mean = ene*opPerMeV;
	double sigma = sqrt(mean);
	genPhotons = floor(rand.Gaus(mean, sigma));
		

	return genPhotons;
}

//	Finalize the event
//
void SHSDCounter::EndOfEvent(G4HCofThisEvent*)
{ 
	cout << "### ______________________________________________" << endl;
	cout << "### photons = " << numPhotons << endl;
	cout << "### eneDep = "  << eneDep << endl;
	cout << "### myPhotons = " << myNumPhotons << endl;
	shTree->Fill();

	//	Print the pe array for the event
	//
/*	if (runParams.verbosity)
	{
		for (int i=0; i < numPMTs; i++)
			cout << "### PMT#" << i+1 << " PEs: " << pe[i] << endl;
	}
	*/
}
