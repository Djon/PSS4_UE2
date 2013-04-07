#include <cassert>
#include <algorithm>
#include "ThreadMerge.h"

ThreadMerge::ThreadMerge() {
	assert(ThreadBase::IsThreadCreated());
	IsInitialized = false;
}

ThreadMerge::~ThreadMerge() {

}

void ThreadMerge::Init(TStringList * const l1, TStringList * const l2, HANDLE h1, HANDLE h2)
{
	mL1 = l1;
	mL2 = l2;
	mHandles.push_back(h1);
	mHandles.push_back(h2);
	IsInitialized = true;
}

int ThreadMerge::Run() {
	assert(IsInitialized);
	if (!IsInitialized) {
		return 0;
	}

	WaitForMultipleObjects(mHandles.size(), mHandles.data(), true, INFINITE);
	std::for_each(mHandles.begin(), mHandles.end(), CloseHandle);	
	mL1->merge(*mL2);
	
	delete this;

	return 0;
}