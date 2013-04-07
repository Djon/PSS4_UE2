#ifndef THREADMERGE_H
#define THREADMERGE_H

#include <vector>
#include "ThreadBase.h"

class ThreadMerge : public ThreadBase {

public:
	ThreadMerge();
	virtual ~ThreadMerge();

	virtual void Init(TStringList * const l1, TStringList * const l2, HANDLE h1, HANDLE h2);

	virtual int Run();

private:
	bool IsInitialized;
	TStringList	 * mL1;	// two lists get merged into this one
	TStringList  * mL2;
	std::vector<HANDLE> mHandles;	// threads to wait for
};

#endif