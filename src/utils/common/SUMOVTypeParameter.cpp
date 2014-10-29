/****************************************************************************/
/// @file    SUMOVTypeParameter.cpp
/// @author  Daniel Krajzewicz
/// @date    10.09.2009
/// @version $Id: SUMOVTypeParameter.cpp 8581 2010-04-10 13:52:27Z dkrajzew $
///
// Structure representing possible vehicle parameter
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

#include <algorithm>
#include <utils/common/SUMOVTypeParameter.h>
#include <utils/common/ToString.h>
#include <utils/common/TplConvert.h>
#include <utils/common/MsgHandler.h>
#include <utils/iodevices/OutputDevice.h>
#include <utils/options/OptionsCont.h>
#include <utils/xml/SUMOXMLDefinitions.h>

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// member method definitions
// ===========================================================================
SUMOVTypeParameter::SUMOVTypeParameter() throw()
        : id(DEFAULT_VTYPE_ID), length(DEFAULT_VEH_LENGTH), maxSpeed(DEFAULT_VEH_MAXSPEED),
        defaultProbability(DEFAULT_VEH_PROB),
        speedFactor(DEFAULT_VEH_SPEEDFACTOR), speedDev(DEFAULT_VEH_SPEEDDEV),
        emissionClass(SVE_UNKNOWN), color(RGBColor::DEFAULT_COLOR),
        vehicleClass(SVC_UNKNOWN), width(DEFAULT_VEH_GUIWIDTH),
        offset(DEFAULT_VEH_GUIOFFSET), shape(DEFAULT_VEH_SHAPE),
        cfModel(-1),
        //cfModel(), lcModel(),
        setParameter(0), saved(false), onlyReferenced(false)
{
}


void
SUMOVTypeParameter::write(OutputDevice &dev) const throw(IOError)
{
    if (onlyReferenced) {
        return;
    }
    dev << "   <vtype id=\"" << id << '"';
    if (wasSet(VTYPEPARS_LENGTH_SET)) {
        dev << " length=\"" << length << '"';
    }
    if (wasSet(VTYPEPARS_MAXSPEED_SET)) {
        dev << " maxspeed=\"" << maxSpeed << '"';
    }
    if (wasSet(VTYPEPARS_PROBABILITY_SET)) {
        dev << " probability=\"" << defaultProbability << '"';
    }
    if (wasSet(VTYPEPARS_SPEEDFACTOR_SET)) {
        dev << " speedFactor=\"" << speedFactor << '"';
    }
    if (wasSet(VTYPEPARS_SPEEDDEVIATION_SET)) {
        dev << " speedDev=\"" << speedDev << '"';
    }
    if (wasSet(VTYPEPARS_VEHICLECLASS_SET)) {
        dev << " vclass=\"" << getVehicleClassName(vehicleClass) << '"';
    }
    if (wasSet(VTYPEPARS_EMISSIONCLASS_SET)) {
        dev << " emissionClass=\"" << getVehicleEmissionTypeName(emissionClass) << '"';
    }
    if (wasSet(VTYPEPARS_SHAPE_SET)) {
        dev << " guiShape=\"" << getVehicleShapeName(shape) << '"';
    }
    if (wasSet(VTYPEPARS_OFFSET_SET)) {
        dev << " guiOffset=\"" << offset << '"';
    }
    if (wasSet(VTYPEPARS_WIDTH_SET)) {
        dev << " guiWidth=\"" << width << '"';
    }
    if (wasSet(VTYPEPARS_COLOR_SET)) {
        dev << " color=\"" << color << '"';
    }

    if (cfParameter.size()!=0) {
        dev << ">\n";
        dev << "      <";
        switch (cfModel) {
        case SUMO_TAG_CF_IDM:
            dev << CF_MODEL_IDM;
            break;
        case SUMO_TAG_CF_KRAUSS_ORIG1:
            dev << CF_MODEL_KRAUSS_ORIG1;
            break;
        case SUMO_TAG_CF_PWAGNER2009:
            dev << CF_MODEL_PWAGNER2009;
            break;
        case SUMO_TAG_CF_BKERNER:
            dev << CF_MODEL_BKERNER;
            break;
        case SUMO_TAG_CF_KRAUSS:
        default:
            dev << CF_MODEL_KRAUSS;
            break;
        }
        std::vector<std::string> names;
        for (std::map<std::string, SUMOReal>::const_iterator i=cfParameter.begin(); i!=cfParameter.end(); ++i) {
            names.push_back((*i).first);
        }
        std::sort(names.begin(), names.end());
        for (std::vector<std::string>::const_iterator i=names.begin(); i!=names.end(); ++i) {
            dev << ' ' << (*i) << "=\"" << cfParameter.find(*i)->second << '"';
        }
        dev << "/>\n";
        dev << "   </vtype>\n";
    } else {
        dev << "/>\n";
    }
}


/****************************************************************************/

