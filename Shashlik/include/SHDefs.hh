#ifndef SHDEFS_H
#define SHDEFS_H

#include "globals.hh"
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TApplication.h"
#include "TTree.h"

using namespace std;

/*
 *	Run Parameters
 *
 */
typedef struct RunParams
{
	int iEnergy;
	int numLayers;
	int numModules;
	int isInteractive;
	int verbosity;
	int seed;
	int numEvents;
};

#endif
