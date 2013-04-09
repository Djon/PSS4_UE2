///////////////////////////////////////////////////////////////////////////
// Workfile : ThreadFileToList.h
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Header of ThreadFileToList.cpp
///////////////////////////////////////////////////////////////////////////

#ifndef THREADFILETOLIST_H
#define THREADFILETOLIST_H

#include "ThreadBase.h"

class ThreadFileToList : public ThreadBase {

public:
	ThreadFileToList();
	virtual ~ThreadFileToList();

	virtual void Init(std::string const& filename, TStringList * const l1);

	virtual int Run();

private:
	bool IsInitialized;
	std::string	 mFilename;
	TStringList* mL1;
};

#endif