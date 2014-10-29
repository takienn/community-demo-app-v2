/****************************************************************************/
/// @file    OutputDevice_COUT.cpp
/// @author  Daniel Krajzewicz
/// @date    2004
/// @version $Id: OutputDevice_COUT.cpp 8459 2010-03-17 22:02:19Z behrisch $
///
// An output device that encapsulates cout
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
#include "OutputDevice_COUT.h"

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// method definitions
// ===========================================================================
OutputDevice_COUT::OutputDevice_COUT() throw(IOError) {}


OutputDevice_COUT::~OutputDevice_COUT() throw() {}


std::ostream &
OutputDevice_COUT::getOStream() throw()
{
    return std::cout;
}


/****************************************************************************/
