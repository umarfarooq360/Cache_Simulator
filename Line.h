#pragma once
#include <vector>
class Line
{
public:
	Line();
	Line(int blockSize);
	~Line();
	int getTag();
	void setTag(int newtag);
	int getLru();
	void setLru(int newlru);
	void incLru();
	void setValid();
	bool isValid();
	std::vector<int> data ;

private:
	
	bool valid;
	int tag;
	int lru;
	


};

