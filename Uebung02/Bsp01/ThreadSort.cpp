#include <cassert>
#include <algorithm>
#include "ThreadSort.h"

ThreadSort::ThreadSort() {
	assert(ThreadBase::IsThreadCreated());
	IsInitialized = false;
}

ThreadSort::~ThreadSort() {

}

void ThreadSort::Init(TStringList * const l1, HANDLE hdl)
{
	mL1 = l1;
	mHdl = hdl;
	IsInitialized = true;
}

int ThreadSort::Run() {
	assert(IsInitialized);
	if (!IsInitialized) {
		return 0;
	}

	WaitForSingleObject(mHdl, INFINITE);
	CloseHandle(mHdl);
	mL1->sort();

	delete this;

	return 0;
}