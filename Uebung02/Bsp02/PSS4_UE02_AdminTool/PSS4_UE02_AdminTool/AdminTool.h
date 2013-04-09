#ifndef ADMINTOOL_H
#define ADMINTOOL_H

#include <string>
#include <Windows.h>

//möglicherweise alles static


class AdminTool
{
public:
	static void StartProgram(std::string const& ProgramName);
	static void ListProcesses();
	static void KillProcess(DWORD const& ProcessId);
	static void PrintSystemInfo();
};

#endif