#include <iostream>
#include "AdminTool.h"

using namespace std;


int main(int argc, char **argv)
{
	try
	{
		AdminTool tool;

		if (argc > 1)
		{
			tool.StartProgram(argv[1]);
		}
		else
		{
			cerr << "No arguments." << endl;
		}

		tool.ListProcesses();

		return 0;
	}
	catch (std::string const& error)
	{
		std::cerr << error << std::endl;
		return 1;
	}
	catch(...)
	{
		cerr << "Unknown exception caught.";
		return 1;
	}
}