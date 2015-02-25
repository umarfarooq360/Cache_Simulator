#include <iostream>
#include <sstream>
#include <string>
#include "Cache.h"
#include "Set.h"
/*
	This class implemets a Cache with adjustable size, block size and set associativity.


	Author: Omar Farooq
	Date: 11/26/14
*/


using namespace std;

Cache::Cache(){

}


Cache::Cache(int size , int blSize , int setAssoc )
:cacheCapacity(size),blockSize(blSize),setAssociativity(setAssoc)
{
	DEBUG = false;
	if (DEBUG){ cout << "Contructing Cache" << endl; }
	//each word is 4 bytes for 32 bit address. 
	//To get the block offset we multiply the number of bytes per block
	//by the set associativity 
	//CHECK IF SHOULD MUL BY SET ASSOC
	blockOffsetBits = findLog(blSize / 4);
	if (DEBUG){ cout << "blockOffsetBits = " << blockOffsetBits << endl; }

	//to find the how many bits represent the index we divide  the size by
	//product the number of bytes per block and the set associativity.
	//We take the log of this to find the number of bits
	indexBits = findLog((size / blockSize)/setAssoc);
	if (DEBUG){ cout << "indexBits = " << indexBits << endl; }

	//initialize all the sets
	sets = vector<Set>((size / blockSize) / setAssoc, Set(setAssoc, blSize));
	if (DEBUG){ cout << "number fo sets in cache = " << sets.size() << endl; }

	
	if (DEBUG){ cout << "Done constructing Cache" << endl; }
}

Cache::~Cache()
{

}

/*
	This method performs one access on the cache.
	It takes in the addess and the access number
	The access number is just how recent the the current access to allow
	us to use the lru strategy
*/
bool Cache::access(int address , int accessNum){
	
	int copy = address;
	//int byteOffset = address & 3;//get the last two bits
	
	copy >>= 2;  //shift copy by two to the right
	int blockOffset = copy & (expontiate(blockOffsetBits) - 1);
	copy >>= blockOffsetBits; //shift to remove the block offset bits

	int index = copy & (expontiate(indexBits) - 1); //get the index
	copy >>= indexBits; //take away the index bits so we're left with tag

	int tag = copy;

	if (DEBUG){ cout << "BlockOffS: " << blockOffset << " index: " <<index
		<<" tag "<<tag << endl; }

	//Did we find the entry with the tag in the Cache?
	int hitOrMiss = findTagInSet(sets[index] , tag);
	//if we did then increment least recently used and return true
	if (DEBUG){	cout <<" hitOrMiss: "<< hitOrMiss << endl;	}

	if (hitOrMiss >= 0){ //if we have a hit
		sets[index].getLine(hitOrMiss).setLru(accessNum);
		return true;
	}
	else{ //if we have a miss

		//find an empty block in the set
		int whichLineInSet = findInvalidBlocks(sets[index]);
		if (whichLineInSet >= 0){ //we have an empty block in the set
			if (DEBUG){ cout << " Found empty block" << endl; }
			sets[index].modifyLine(whichLineInSet, tag, accessNum);

			//ADDD CODE TO REPLACE OLD DATA WITH NEW DATA
		}
		else //if there is no empty block replace the least recently used
		{
			whichLineInSet = sets[index].findMinLRU(setAssociativity);
			sets[index].modifyLine(whichLineInSet, tag , accessNum);
			
		}
		return false;

	}
}

int Cache::findTagInSet(Set s, int tag){
	if (DEBUG){ cout << "finding the tag inside set " << endl; }
	for (int i = 0; i < s.setSize; i++)
	{
		if (!s.getLine(i).isValid()) { continue; }
		if (s.getLine(i).getTag() == tag) { return i; }
	}
	return -1;
}

int Cache::findInvalidBlocks(Set s){
	if (DEBUG){ cout << " finding invalid blocks" << endl; }
	for (int i = 0; i < s.setSize ; i++)
	{
		if (!s.getLine(i).isValid()) { return i; }
	}
	return -1;
}

int Cache::findLog(int x){
	int i = 0;
	while (x > 1){
		x = x >> 1;
		i++;
	}
	return i;
}

int Cache::expontiate(int x){
	int y = 1;
	for (int i = 0; i < x; i++)
	{
		y *= 2;
	}
	return y;
}

/*
Returns the hex representation of an int
*/
string Cache::getHex(int x){
	std::stringstream ss;
	ss << std::hex << x; // int decimal value
	return ss.str();

}

/*
	This method prints the contents of the cache
*/
void Cache::printCache(){
	for (int i = 0; i < ((cacheCapacity / blockSize) / setAssociativity); i++)
	{
		cout << "******* SET " << i << " ******" << endl;
		for (int j = 0; j < setAssociativity; j++)
		{
			cout << "Index " << j << " : tag " << getHex(sets[i].getLine(j).getTag()) << " valid "
				<< (int)sets[i].getLine(j).isValid() << " lru " << sets[i].getLine(j).getLru() << endl;
		}
		cout << endl;
	}

}

void Cache::enableDebug(bool val){
	DEBUG = val;

}


