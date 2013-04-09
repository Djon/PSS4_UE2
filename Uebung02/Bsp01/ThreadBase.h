///////////////////////////////////////////////////////////////////////////
// Workfile : ThreadBase.h
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Header of ThreadBase.cpp
///////////////////////////////////////////////////////////////////////////

#ifndef ThreadBase_INCLUDED
#define ThreadBase_INCLUDED

#include <Windows.h>
#include <list>
#include <string>

typedef std::list<std::string> TStringList;

class ThreadBase {
public:
	ThreadBase();
	virtual ~ThreadBase();

	// THE thread function
	virtual int Run() = 0;
	// control thread behaviour
	virtual void Start() const;
	virtual void Stop() const;

	// state check:
	virtual bool IsThreadCreated() const;

	// this handle is even valid after destroying this thread object
	// call CloseHanlde() after usage!
	virtual HANDLE GetDuplicateHdl() const;

protected:
	// internal thread handle => derived classes only
	virtual HANDLE GetThreadHdl() const;

	ThreadBase(ThreadBase const&);
	ThreadBase & operator = (ThreadBase const &);

private:
	static unsigned long WINAPI ThreadFunc(void * Param);

	HANDLE ThreadHdl;
	unsigned long ThreadId;

};

#endif