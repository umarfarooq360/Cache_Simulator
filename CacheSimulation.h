#pragma once
#include <vector>
#include <string>
#include "Cache.h"

class CacheSimulation
{
public:
	/*
		Default Constructor for the Cache Simulator
	*/	
	CacheSimulation();
	/*
		Main constructor
		Takes input configureation file and constructs a cache.
		Then uses input file to test it
	*/
	CacheSimulation(std::string configfilename, std::string inputfilename, bool debug);
	~CacheSimulation();

	//HELPER METHODS to read file and perform accesses
	void readConfigFile(std::string  &filename);
	void readInputFile(std::string  &filename);
	void processAccess(int accessNumber);

	//the cache used for simulation
	Cache cache;
	
	//vector of access addresses
	std::vector<int> trace;
	
	//the number of hits we got
	int	hits;
	//config parameters
	bool printStatistics;
	bool stepExecution;
	bool printContents;
	bool DEBUG;
	
private:
	
};

