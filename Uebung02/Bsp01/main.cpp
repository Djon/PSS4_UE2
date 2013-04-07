#include <iostream>
#include <vector>

#include "SortMergeMT.h"

using namespace std;

int main() {

	try
	{
		vector<string> strVec;
		//SortMergeMT(strVec, "sorted.txt");	//exception: no valid vector
		
		strVec.push_back("");
		strVec.push_back("");
		strVec.push_back("");
		strVec.push_back("");
		//SortMergeMT(strVec, "sorted.txt");	//exception: no valid string
		
		strVec.clear();

		strVec.push_back("dutch.txt");
		strVec.push_back("finnish.txt");
		strVec.push_back("japanese.txt");
		strVec.push_back("polish.txt");
		
		//SortMergeMT(strVec, "");				//exception: no valid outputFilename
		
		SortMergeMT(strVec, "sorted.txt");
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