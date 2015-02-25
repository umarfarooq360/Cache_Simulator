#include <fstream>
#include <vector>
#include <iostream>
#include "CacheSimulation.h"
#include "Cache.h"
#include <cstdlib>

/*
This class implemets a runs a Cache Simulation after reading input file with byte 
addresses and configuration file to get adjustable size, block size and set associativity.


Author: Omar Farooq
Date: 11/26/14
*/

using namespace std;

CacheSimulation::CacheSimulation(){

}

CacheSimulation::CacheSimulation(string configfilename, string inputfilename, bool debug)
:DEBUG(debug)
{
	cache = Cache();
	cache.enableDebug(debug);
	trace =  vector<int>();
	hits = 0;
	
	if (DEBUG){ cout << "Contucting CacheSim" << endl; cache.enableDebug(true); }

	readConfigFile(configfilename);
	readInputFile(inputfilename);
	
}


CacheSimulation::~CacheSimulation()
{
}

void CacheSimulation::readConfigFile(string  &filename){
	if (DEBUG){ cout << "Reading configfile" << endl; }
	//input stream to read file
	ifstream file(filename.c_str());
	if (!file){
		cerr << "ERROR: reading the config file" << endl;
		exit(1);
	}
	//temp variables to store 6 config file parameters
	int tmp1, tmp2, tmp3, tmp4;
	
	//debug stuff
	if (DEBUG){ cout << "printing read config file " << endl; }

	//read the file and initialize data fields
	int i = 0;
	while ( file >> tmp4 ){
		if (DEBUG){ cout << tmp4 << endl; }
		if (i == 0){ tmp1 = tmp4; }
		else if (i == 1){ tmp2 = tmp4; }
		else if (i == 2){ tmp3 = tmp4; cache = Cache(tmp1, tmp2, tmp3); }
		else if (i == 3){ printStatistics = (bool) tmp4; }
		else if (i == 4){ stepExecution = (bool)tmp4; }
		else if (i == 5){ printContents =(bool) tmp4; }
		else { break; }
		i++;
	}

	cout << "Cache size (bytes) - > " << tmp1 << "\nBLock Size (bytes) -> " << tmp2
		<< "\nSet Associativity -> " << tmp3 << "\nPrint Statistics -> " << printStatistics
		<< "\nStep Execution -> " << stepExecution << "\nPrint contents -> " << printContents << "\n\n" << endl;
	
	if (DEBUG){ cout << "Ending reading configfile" << endl; }
}

void CacheSimulation::readInputFile(string  &filename){
	if (DEBUG){ cout << "Reading Input file" << endl; }
	//input stream to read file
	ifstream file(filename.c_str());
	if (!file){
		cerr << "ERROR: reading the input file" << endl;
		exit(1);
	}

	//temp variable to store stuff
	int tmp1;
	
	//read all the memort traces and add to a vector
	while (file >> tmp1 ){
		trace.push_back(tmp1);
		if (this->DEBUG){ std::cout << tmp1 << endl; }
	}
	if (DEBUG){ cout << "Ending reading input file" << endl; }
}

//Performs a single access from the array trace, depending on the access number
void CacheSimulation::processAccess(int accessNumber){
	
	if (DEBUG){
		cout << "Performing access# " << accessNumber
			<< " at address  " << trace[accessNumber] << endl;
	}
	
	bool result = cache.access(trace.at(accessNumber), accessNumber);
	if (result){ hits++; }
	if (printContents && stepExecution) { cache.printCache(); }
}

int main(int argc, char* argv[]){
	CacheSimulation sim;
	
	//check for arguments and proceed accordingly
	if (argc < 3){
		cerr << "ERROR: No input parameters." << endl << "\t Usage: <Input filename> <Config filename> " << endl;
		return 1;
	}
	if (argc == 3){
		sim = CacheSimulation( string(argv[2]), string(argv[1]), false);
	}
	else{
		sim = CacheSimulation( string(argv[2]), string(argv[1]), (bool)atoi(argv[3]) );
	}

	//check for stepwise exectution
	if (sim.stepExecution){
		cout << "Performing step-wise execution. Press Return to step!" << endl;	
		for (size_t i = 0; i < sim.trace.size() ; i++)
		{
			
			cin.get();
			cout << "Performing Access at address : " << sim.trace[i] << endl;
			sim.processAccess(i);

		}
	}
	else{
		for (size_t i = 0; i < sim.trace.size(); i++)
		{
			sim.processAccess(i);

		}
		if (sim.printContents){ sim.cache.printCache(); }
	}

	//Print statistics if required
	if (sim.printStatistics){
		double hitRate = (double)sim.hits / (double)sim.trace.size();
		cout << "\n\n---------------\nOVERALL STATISTICS\n---------------" << endl;
		cout << "ACCESSES " << sim.trace.size() << "\nHITS " << sim.hits << "\nMISSES "
			<< (sim.trace.size() - sim.hits) <<endl;
		printf("HIT RATE %.4f\n", hitRate);
	}

	return 0;
}