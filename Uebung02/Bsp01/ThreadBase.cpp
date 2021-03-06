///////////////////////////////////////////////////////////////////////////
// Workfile : ThreadBase.cpp
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Threadbase
///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "ThreadBase.h"

ThreadBase::ThreadBase() {
	ThreadHdl = CreateThread(0, 0, ThreadFunc, this, CREATE_SUSPENDED, &ThreadId);

	assert(ThreadHdl != 0);
}

ThreadBase::~ThreadBase() {
	CloseHandle(ThreadHdl);
}

unsigned long WINAPI ThreadBase::ThreadFunc(void * Param) {
	assert(Param != 0);
	
	ThreadBase * pObj = static_cast <ThreadBase *> (Param);
	pObj->Run();
	
	return 0;
}

void ThreadBase::Start() const {
	ResumeThread(ThreadHdl);
}

void ThreadBase::Stop() const {
	SuspendThread(ThreadHdl);
}

bool ThreadBase::IsThreadCreated() const {
	return ThreadHdl != 0;
}

// internal handle
HANDLE ThreadBase::GetThreadHdl() const {
	return ThreadHdl;
}

// duplicate handle
// closehandle!!!
HANDLE ThreadBase::GetDuplicateHdl() const {
	HANDLE hdlDup = 0;
	BOOL res = DuplicateHandle(GetCurrentProcess(), ThreadHdl, GetCurrentProcess(),
								&hdlDup, 0, FALSE, DUPLICATE_SAME_ACCESS);
	assert(res != 0);
	return hdlDup;
}
