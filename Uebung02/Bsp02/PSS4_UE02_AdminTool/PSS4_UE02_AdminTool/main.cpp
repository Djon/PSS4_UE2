#include <iostream>
#include <vld.h>
#include "AdminTool.h"

using namespace std;


int main(int argc, char **argv)
{
	char command = 0;
	string ProgramName = " ";
	DWORD ProcessId = -1;

	while(command != 'e')
	{

		cout << "Enter command: ";
		cin >> command;
		try
		{		
			switch (command) 
			{
			case '?':
				cout << "StartProgram: 0" << endl;
				cout << "ListProcesses: 1" << endl;
				cout << "Remove: 2" << endl;
				cout << "KillProcess: 3" << endl;
				cout << "PrintSystemInfo: 4" << endl;
				cout << "Exit: e" << endl;
				cout << endl;
				break;

			case '0': 
				cout << "Enter program name: ";
				cin >> ProgramName;
				AdminTool::StartProgram(ProgramName);
				cout << endl;
				break;

			case '1':
				AdminTool::ListProcesses();
				cout << endl;
				break;

			case '2':
				cout << "Enter process Id of process to kill: ";
				cin >> ProcessId;
				AdminTool::KillProcess(ProcessId);
				cout << endl;
				break;

			case '3':
				AdminTool::PrintSystemInfo();
				cout << endl;
				break;
			}
		}
		catch(std::bad_alloc& ex)
		{
			cerr << ex.what() << endl;
		}
		catch (std::string const& error)
		{
			std::cerr << error << std::endl;
		}
		catch(...)
		{
			cerr << "Unknown exception caught.";
		}
	}
	return 0;
}