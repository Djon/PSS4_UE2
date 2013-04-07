#include <iostream>
#include <vector>
#include <string>

#include "SortMergeST.h"

using namespace std;

int main() {

	try
	{
		vector<string> strVec;
		strVec.push_back("dutch.txt");
		strVec.push_back("finnish.txt");
		strVec.push_back("japanese.txt");
		strVec.push_back("polish.txt");
		SortMergeST(strVec, "sorted.txt");
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
	return 0;
}