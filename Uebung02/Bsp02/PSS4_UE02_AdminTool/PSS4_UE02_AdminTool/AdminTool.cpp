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

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

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
	std::cout << std::string(ProcessNameWidth+PIDWidth+PriorityWidth+ThreadCountWidth, LineDivider) << std::endl;

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
	_SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	int const HeaderWidth		= 30;
	int const HardwareWidth		= 25;
	int const SoftwareWidth		= 13;
	char const FillSign			= ' ';
	char const LineDivider		= '-';


	//Hardware
	std::cout << "System Information <HARDWARE>:" << std::endl;
	std::cout << std::string(HeaderWidth, LineDivider) << std::endl;

	std::cout << std::setw(HardwareWidth) << std::setfill(FillSign) << std::left << "Processor Type";
	std::cout << ": " << sysInfo.dwProcessorType << std::endl;

	std::cout << std::setw(HardwareWidth) << "Architecture";
	if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
	{		
		std::cout << ": " << "Intel CPU or compatibles" << std::endl;

		std::cout << std::setw(HardwareWidth) << "Processor Level (Family)";
		std::cout << ": " << sysInfo.wProcessorLevel << std::endl;

		std::cout << std::setw(HardwareWidth) << "Model and Stepping MMSS";
		std::cout << ": 0x" << std::hex << sysInfo.wProcessorRevision << std::dec << std::endl;
	}
	else
	{
		std::cout << ": " << "Unknown architecture" << std::endl;
	}

	std::cout << std::setw(HardwareWidth) << "Number of Processors";
	std::cout << ": " << sysInfo.dwNumberOfProcessors << std::endl;
	std::cout << std::endl;

	
	//TODO Features:
	std::cout << std::endl;


	//Software
	std::cout << "System Information <SOFTWARE>:" << std::endl;
	std::cout << std::string(HeaderWidth, LineDivider) << std::endl;

	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);

	if (!GetComputerName(computerName, &size))
	{
		throw("GetComputerName failed: " + Hlp::ErrMsg(GetLastError()));
	}
	std::cout << std::setw(SoftwareWidth) << "Computer Name";
	std::cout << ": " << computerName << std::endl;

	OSVERSIONINFO osVersionInfo;
	ZeroMemory(&osVersionInfo, sizeof(osVersionInfo));
	osVersionInfo.dwOSVersionInfoSize = sizeof(osVersionInfo);

	if (!GetVersionEx(&osVersionInfo))
	{
		throw("GetVersionEx failed: " + Hlp::ErrMsg(GetLastError()));
	}
	std::cout << std::setw(SoftwareWidth) << "OS Version";
	std::cout << ": " << "Major: " << osVersionInfo.dwMajorVersion 
		<< "  Minor: " << osVersionInfo.dwMinorVersion << std::endl;

	std::cout << std::setw(SoftwareWidth) << "OS Revision";
	std::cout << ": " << osVersionInfo.szCSDVersion << std::endl;
}