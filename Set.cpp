#include <vector>
#include "Set.h"
#include "Line.h"

/*
This class implemets a Set which a data structure inside
the cache to hold valid bit, tag, and data.


Author: Omar Farooq
Date: 11/26/14
*/
Set::Set(){

}

Set::Set(int setAssoc, int _blockSize)
:setSize(setAssoc), blockSize(_blockSize)
{
	lines = std::vector<Line>(setAssoc);
	for (int i = 0; i < setAssoc; i++)
	{
		lines[i] = Line(_blockSize);
	}
	
}

int Set::findMinLRU(int setAssoc){
	int minLRUIndex = 0;
	for (int i = 0; i < setAssoc; i++)
	{
		if (lines[i].getLru() < lines[minLRUIndex].getLru()){
			minLRUIndex = i;
		}
	}
	return minLRUIndex;
}

Line Set :: getLine(int i){
	return lines[i];
}

void Set::modifyLine(int lineIndex, int tag, int lru){
	Line tmp = Line(blockSize);
	tmp.setValid();
	tmp.setLru(lru);
	tmp.setTag(tag);
	lines[lineIndex] = tmp;

}

Set::~Set()
{
}
