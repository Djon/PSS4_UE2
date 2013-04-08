#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <TlHelp32.h>
#include "Hlp.h"
#include "AdminTool.h"

void AdminTool::StartProgram(std::string const& ProgramName)
{
	STARTUPINFO si; //specifies how the main window of the new process should appear
	PROCESS_INFORMATION pi; //filled by CreateProcess (IDs and so on)

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	memset(&pi, 0, sizeof(pi));

	//start new process
	if (!CreateProcess(ProgramName.c_str(),0,0,0,false,0,0,0,&si,&pi))
	{
		throw("CreateProcess failed: " + Hlp::ErrMsg(GetLastError()));
	}
	else
	{
		//close process handle and thread handle (decoupling)
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

void AdminTool::ListProcesses()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	int const ProcessNameWidth	= 25;
	int const PIDWidth			= 10;
	int const PriorityWidth		= 20;
	int const ThreadCountWidth	= 15;
	char const FillSign			= ' ';
	char const LineDivider		= '-';

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		throw("CreateToolhelp32Snapshot failed: " + Hlp::ErrMsg(GetLastError()));
	}

	// Set the size of the process structure.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		CloseHandle( hProcessSnap );          // clean the snapshot object
		throw("Process32First failed: " + Hlp::ErrMsg(GetLastError()));
	}

	//Print header info
	std::cout << std::setw(ProcessNameWidth)	<< std::setfill(FillSign)	<< std::left << "Process";
	std::cout << std::setw(PIDWidth)			<< std::setfill(FillSign)	<< std::left << "PID";
	std::cout << std::setw(PriorityWidth)		<< std::setfill(FillSign)	<< std::left << "BasePriority";
	std::cout << std::setw(ThreadCountWidth)	<< std::setfill(FillSign)	<< std::left << "Thread Count";
	std::cout << std::endl;
	std::cout << std::setw(ProcessNameWidth+PIDWidth+PriorityWidth+ThreadCountWidth) << std::setfill(FillSign) << std::left;
	std::cout << std::endl;

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{	
		//Print process info
		std::cout << std::setw(ProcessNameWidth)	<< std::setfill(FillSign)	<< std::left << pe32.szExeFile;
		std::cout << std::setw(PIDWidth)			<< std::setfill(FillSign)	<< std::left << pe32.th32ProcessID;
		std::cout << std::setw(PriorityWidth)		<< std::setfill(FillSign)	<< std::left << pe32.pcPriClassBase;
		std::cout << std::setw(ThreadCountWidth)	<< std::setfill(FillSign)	<< std::left << pe32.cntThreads;
		std::cout << std::endl;
	} while(Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
}

void AdminTool::KillProcess(DWORD const& ProcessId)
{
	DWORD DesiredAccess = PROCESS_TERMINATE;
	BOOL  InheritHandle  = FALSE;

	HANDLE hProcess = OpenProcess(DesiredAccess, InheritHandle, ProcessId);
	if (hProcess == NULL)
	{
		throw("OpenProcess failed: " + Hlp::ErrMsg(GetLastError()));
	}

	if (!TerminateProcess(hProcess, 0))
	{
		throw("TerminateProcess failed: " + Hlp::ErrMsg(GetLastError()));
	}
	CloseHandle(hProcess);
}

void AdminTool::PrintSystemInfo()
{

}