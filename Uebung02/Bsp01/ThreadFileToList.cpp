///////////////////////////////////////////////////////////////////////////
// Workfile : ThreadFileToList.cpp
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Thread that writes data from a file into a list
///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <fstream>
#include "ThreadFileToList.h"

ThreadFileToList::ThreadFileToList() {
	assert(ThreadBase::IsThreadCreated());
	IsInitialized = false;
}

ThreadFileToList::~ThreadFileToList() {

}

void ThreadFileToList::Init(std::string const& filename, TStringList * const l1)
{
	mFilename = filename;
	mL1 = l1;
	IsInitialized = true;
}

int ThreadFileToList::Run() {
	assert(IsInitialized);
	if (!IsInitialized) {
		return 0;
	}
	
	std::ifstream fs;
	fs.open(mFilename);

	if (fs == 0)
	{
		std::string error = "Error in ThreadFileToList::Run: could not open stream";
		throw (error);
	}
	
	std::string line;
	
	while(!fs.eof())
	{
		std::getline(fs, line);
		mL1->push_back(line);
	}

	fs.close();

	delete this;

	return 0;
}