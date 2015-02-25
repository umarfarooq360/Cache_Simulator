#pragma once
#include <vector>
#include <string>
#include "Set.h"


class Cache
{
public:
	//Construct a cache with given cahe size block size and set associativity
	Cache(int size, int blSize, int setAssoc);
	

	Cache();
	~Cache(); 
	
	//Does some cool stuff
	int findTagInSet(Set s, int tag);
	int findInvalidBlocks(Set s);
	
	//public datafields
	//bad programming?
	//No worries
	std::vector<Set> sets;
	bool access(int address, int accessNum);
	int expontiate(int x);
	void printCache();
	void enableDebug(bool val);


private:
	/*
		This method finds the log base 2 of input x
		It assumes that the number is a power of 2.
	*/
	int findLog(int x);
	
	
	//This is the total capacity of the cache in bytes.Should be power of 2
	int cacheCapacity;
	
	//This is the size of a line in the cache
	int blockSize;
	
	//this is the number of lines in the cache per index
	int setAssociativity;

	
	//This defines which word witin the block
	int blockOffsetBits;

	//This is how many bits of index we will have in our cache
	int indexBits;

	bool DEBUG ;

	std::string getHex(int x);

};

