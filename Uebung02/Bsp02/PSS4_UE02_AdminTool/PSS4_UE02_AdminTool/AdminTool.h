#ifndef ADMINTOOL_H
#define ADMINTOOL_H

#include <string>
#include <Windows.h>

//m�glicherweise alles static


class AdminTool
{
public:
	void StartProgram(std::string const& ProgramName);
	void ListProcesses();
	void KillProcess(DWORD const& ProcessId);
	void PrintSystemInfo();

private:

};

#endif