#ifndef THREADSORT_H
#define THREADSORT_H

#include "ThreadBase.h"

class ThreadSort : public ThreadBase {

public:
	ThreadSort();
	virtual ~ThreadSort();

	virtual void Init(TStringList * const l1, HANDLE hdl);

	virtual int Run();

private:
	bool IsInitialized;
	TStringList * mL1;		// pointer to list that is sorted
	HANDLE mHdl;
};

#endif