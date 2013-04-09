///////////////////////////////////////////////////////////////////////////
// Workfile : ThreadListToFile.h
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Header of ThreadListToFile.cpp
///////////////////////////////////////////////////////////////////////////

#ifndef THREADLISTTOFILE_H
#define THREADLISTTOFILE_H

#include "ThreadBase.h"

class ThreadListToFile : public ThreadBase {

public:
	ThreadListToFile();
	virtual ~ThreadListToFile();

	virtual void Init(std::string const& filename, TStringList * const l1, HANDLE hdl);

	virtual int Run();

private:
	bool IsInitialized;
	std::string	 mFilename;
	TStringList* mL1;
	HANDLE mHdl;
};

#endif