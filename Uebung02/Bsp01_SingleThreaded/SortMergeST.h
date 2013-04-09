///////////////////////////////////////////////////////////////////////////
// Workfile : SortMergeST.h
// Author : Reinhard Penn, Bernhard Selymes
// Date : 09.04.2013
// Description : Header of SortMergeST.cpp
///////////////////////////////////////////////////////////////////////////

#ifndef SORTMERGEST_H
#define SORTMERGEST_H

#include <string>
#include <vector>

void SortMergeST(std::vector<std::string> const& filenames,
				 std::string const& filenameOutput);

#endif