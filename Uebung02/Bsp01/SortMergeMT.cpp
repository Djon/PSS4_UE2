///////////////////////////////////////////////////////////////////////////
// Workfile : SortMergeMT.cpp
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Multithreaded sort and merge of lists
///////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include "SortMergeMT.h"
#include "ThreadFileToList.h"
#include "ThreadListToFile.h"
#include "ThreadMerge.h"
#include "ThreadSort.h"

void SortMergeMT(std::vector<std::string> const& filenames,
				 std::string const& filenameOutput)
{
	if (filenameOutput.empty())
	{
		std::string error = "Error in SortMergeMT::SortMergeMT: no valid filenameOutput";
		throw (error);
	}

	size_t const numFiles = 4;
	if (filenames.size() != numFiles)
	{
		std::string error = "Error in SortMergeMT::SortMergeMT: no valid vector";
		throw (error);
	}

	for (size_t i = 0; i < filenames.size(); ++i)
	{
		if (filenames[i].empty())
		{
			std::stringstream error;
			error << "Error in SortMergeMT::SortMergeMT: no valid string at index " << i;
			throw (error.str());
		}
	}

	// file to list
	std::vector<TStringList*> StringLists;
	std::vector<HANDLE> ThreadFtLHandles;
	for (size_t i = 0; i < numFiles; ++i)
	{
		TStringList* sl = new TStringList;						// allocate list
		StringLists.push_back(sl);
		ThreadFileToList* tFtL = new ThreadFileToList;			// allocate thread
		tFtL->Init(filenames[i], StringLists[i]);				// init thread
		ThreadFtLHandles.push_back(tFtL->GetDuplicateHdl());	// save handle
		tFtL->Start();
	}

	// sort
	std::vector<HANDLE> ThreadSortHandles;	
	for (size_t i = 0; i < numFiles; ++i)
	{
		ThreadSort* tS = new ThreadSort;						// allocate thread
		tS->Init(StringLists[i], ThreadFtLHandles[i]);			// init thread
		ThreadSortHandles.push_back(tS->GetDuplicateHdl());		// save handle
		tS->Start();
	}

	// merge: first level
	std::vector<HANDLE> ThreadMergeHandles;
	ThreadMerge* tM1 = new ThreadMerge;
	ThreadMerge* tM2 = new ThreadMerge;
	tM1->Init(StringLists[0], StringLists[1], ThreadSortHandles[0], ThreadSortHandles[1]);
	tM2->Init(StringLists[2], StringLists[3], ThreadSortHandles[2], ThreadSortHandles[3]);
	ThreadMergeHandles.push_back(tM1->GetDuplicateHdl());
	ThreadMergeHandles.push_back(tM2->GetDuplicateHdl());
	tM1->Start();
	tM2->Start();
	
	// merge: second level
	ThreadMerge* tM3 = new ThreadMerge;
	tM3->Init(StringLists[0], StringLists[2], ThreadMergeHandles[0], ThreadMergeHandles[1]);
	ThreadMergeHandles.push_back(tM3->GetDuplicateHdl());
	tM3->Start();	
	
	// list to file
	ThreadListToFile* tLtF1 = new ThreadListToFile;
	tLtF1->Init(filenameOutput, StringLists[0], ThreadMergeHandles[2]);
	HANDLE hdlListToFile = tLtF1->GetDuplicateHdl();
	tLtF1->Start();
	
	WaitForSingleObject(hdlListToFile, INFINITE);

	for (size_t i = 0; i < StringLists.size(); ++i)
	{
		delete StringLists[i]; StringLists[i] = 0;
	}
}