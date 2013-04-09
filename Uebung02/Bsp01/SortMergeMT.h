///////////////////////////////////////////////////////////////////////////
// Workfile : SortMergeMT.h
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Header of SortMergeMT.cpp
///////////////////////////////////////////////////////////////////////////

#ifndef SORTMERGEMT_H
#define SORTMERGEMT_H

#include <string>

void SortMergeMT(std::vector<std::string> const& filenames,
				 std::string const& filenameOutput);

#endif