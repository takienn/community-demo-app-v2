/****************************************************************************/
/// @file    OutputDevice_String.cpp
/// @author  Michael Behrisch
/// @date    2009
/// @version $Id: OutputDevice_String.cpp 8236 2010-02-10 11:16:41Z behrisch $
///
// An output device that encapsulates a stringstream
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

#include <sstream>
#include <string>
#include "OutputDevice_String.h"

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// method definitions
// ===========================================================================
OutputDevice_String::OutputDevice_String() throw(IOError)
{
}


OutputDevice_String::~OutputDevice_String() throw()
{
}


std::string
OutputDevice_String::getString() throw()
{
    return myStream.str();
}


std::ostream &
OutputDevice_String::getOStream() throw()
{
    return myStream;
}


/****************************************************************************/
