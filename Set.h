#pragma once
#include <vector>
#include "Line.h"

class Set
{
public:
	Set();
	Set(int setAssoc, int blockSize);
	~Set();
	int findMinLRU(int setAssoc);
	Line getLine(int i);
	int setSize;
	std::vector<Line> lines;
	void modifyLine(int lineIndex, int tag, int lru);

private:
	int blockSize;
	
};

