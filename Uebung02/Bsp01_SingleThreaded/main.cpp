///////////////////////////////////////////////////////////////////////////
// Workfile : main.cpp
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Testdriver for SortMergeST(...)
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "SortMergeST.h"
#include "StopWatch.h"
//#include <vld.h>

using namespace std;

void Test(std::vector<std::string> const& filenames,
				 std::string const& filenameOutput)
{
	try
	{
		SortMergeST(filenames, filenameOutput);
	}
	catch(std::bad_alloc& ex)
	{
		cerr << ex.what() << endl;
	}
	catch(string const& ex)
	{
		cerr << ex << endl;
	}
	catch(...)
	{
		cerr << "Unhandled exception occured";
	}
}

int main() {
	std::cout << "Start timer." << std::endl;
	stw::Start();
	
	vector<string> strVec;
	Test(strVec, "sorted.txt");			// test empty vector

	strVec.push_back("");
	strVec.push_back("");
	strVec.push_back("");
	strVec.push_back("");
	Test(strVec, "sorted.txt");			// test empty strings

	strVec.clear();
	strVec.push_back("dutch.txt");
	strVec.push_back("finnish.txt");
	
	Test(strVec, "sorted.txt");			// test wrong size vector
	
	strVec.push_back("japanese.txt");
	strVec.push_back("polish.txt");		
	
	Test(strVec, "");					// test empty output name	
	
	Test(strVec, "sortedST.txt");		// test normal

	std::cout << "End timer. Time: " << stw::Stop() << std::endl;
	cout << "Press a key..." << endl;	// poor man's sync
	_getch();							// so you can see the output better

	return 0;
}