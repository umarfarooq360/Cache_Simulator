#include <vector>
#include "Line.h"

//Construct a block with block is size of one int, and valid and tag set to zero
Line::Line()
:valid(0), tag(0), lru(-1)
{
	
}

//Contruct a line/block with the given block size, and valid and tag set to zero
Line::Line(int blockSize )
:valid(0), tag(0), lru(-1)
{
	data = std::vector<int> (blockSize/32) ;
	for (int i = 0; i < blockSize/32; i++)
	{
		data[i] = 0;
	}
}

int Line::getTag(){
	return tag;
}

void Line::setTag(int newtag){
	tag = newtag;
}

bool Line::isValid(){
	return valid;
}

void Line::setValid(){
	valid = true;
}

int Line::getLru(){
	return lru;
}

void Line::setLru(int newlru){
	lru = newlru;
}

void Line::incLru(){
	lru++;
}

Line::~Line()
{
}
