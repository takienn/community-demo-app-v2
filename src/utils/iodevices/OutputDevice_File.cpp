/****************************************************************************/
/// @file    OutputDevice_File.cpp
/// @author  Daniel Krajzewicz
/// @date    2004
/// @version $Id: OutputDevice_File.cpp 8236 2010-02-10 11:16:41Z behrisch $
///
// An output device that encapsulates an ofstream
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// Copyright 2001-2010 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <iostream>
#include "OutputDevice_File.h"

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// method definitions
// ===========================================================================
OutputDevice_File::OutputDevice_File(const std::string &fullName) throw(IOError)
        : myFileStream(0)
{
#ifdef WIN32
    if (fullName=="/dev/null") {
        myFileStream = new std::ofstream("NUL");
#else
    if (fullName=="nul"||fullName=="NUL") {
        myFileStream = new std::ofstream("/dev/null");
#endif
    } else {
        myFileStream = new std::ofstream(fullName.c_str());
    }
    if (!myFileStream->good()) {
        delete myFileStream;
        throw IOError("Could not build output file '" + fullName + "'.");
    }
}


OutputDevice_File::~OutputDevice_File() throw() {
    myFileStream->close();
    delete myFileStream;
}


std::ostream &
OutputDevice_File::getOStream() throw() {
    return *myFileStream;
}


/****************************************************************************/

