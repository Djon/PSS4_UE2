#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "ThreadListToFile.h"

ThreadListToFile::ThreadListToFile() {
	assert(ThreadBase::IsThreadCreated());
	IsInitialized = false;
}

ThreadListToFile::~ThreadListToFile() {

}

void ThreadListToFile::Init(std::string const& filename, TStringList * const l1, HANDLE hdl)
{
	mFilename = filename;
	mL1 = l1;
	mHdl = hdl;
	IsInitialized = true;
}

int ThreadListToFile::Run() {
	assert(IsInitialized);
	if (!IsInitialized) {
		return 0;
	}
	
	std::ofstream fs;
	fs.open(mFilename);

	if (fs == 0)
	{
		std::string error = "Error in ThreadListToFile::Run: could not open stream";
		throw (error);
	}
		
	WaitForSingleObject(mHdl, INFINITE);
	CloseHandle(mHdl);

	TStringList::const_iterator itor = mL1->begin();
	for(;itor != mL1->end(); ++itor)
	{
		fs << *itor << std::endl;
	}

	fs.close();

	delete this;

	return 0;
}