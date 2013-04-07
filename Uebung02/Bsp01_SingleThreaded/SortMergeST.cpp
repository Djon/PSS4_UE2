#include <sstream>
#include <list>
#include <fstream>
#include "SortMergeST.h"

typedef std::list<std::string> TStringList;

void SortMergeST(std::vector<std::string> const& filenames,
				 std::string const& filenameOutput)
{
	if (filenameOutput.empty())
	{
		std::string error = "Error in SortMergeST::SortMergeMT: no valid filenameOutput";
		throw (error);
	}

	size_t const numFiles = 4;
	if (filenames.size() != numFiles)
	{
		std::string error = "Error in SortMergeST::SortMergeMT: no valid vector";
		throw (error);
	}

	for (size_t i = 0; i < filenames.size(); ++i)
	{
		if (filenames[i].empty())
		{
			std::stringstream error;
			error << "Error in SortMergeMT::SortMergeST: no valid string at index " << i;
			throw (error.str());
		}
	}

	// file to list
	TStringList strList;
	for (size_t i = 0; i < numFiles; ++i)
	{
		std::ifstream fs;
		fs.open(filenames[i]);

		if (fs == 0)
		{
			std::string error = "Error in SortMergeST::SortMergeST: could not open input stream";
			throw (error);
		}

		std::string line;

		while(!fs.eof())
		{
			std::getline(fs, line);
			strList.push_back(line);
		}

		fs.close();
	}

	// sort
	strList.sort();
	
	// list to file
	std::ofstream fs;
	fs.open(filenameOutput);

	if (fs == 0)
	{
		std::string error = "Error in SortMergeST::SortMergeST: could not open output stream";
		throw (error);
	}
	
	TStringList::const_iterator itor = strList.begin();
	for(;itor != strList.end(); ++itor)
	{
		fs << *itor << std::endl;
	}

	fs.close();
}