/****************************************************************************/
/// @file    StringUtils.cpp
/// @author  Daniel Krajzewicz
/// @date    unknown
/// @version $Id: StringUtils.cpp 9117 2010-09-22 13:38:55Z behrisch $
///
// Some static methods for string processing
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

#include <string>
#include <iostream>
#include <cstdio>
#include <utils/common/UtilExceptions.h>
#include <utils/common/TplConvert.h>
#include <utils/common/ToString.h>
#include "StringUtils.h"

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// static member definitions
// ===========================================================================
std::string StringUtils::emptyString;


// ===========================================================================
// method definitions
// ===========================================================================
std::string
StringUtils::prune(std::string str)
{
    if (str.length() == 0) {
        return str;
    }
    size_t idx = 0;
    while (idx<str.length()&&str[idx]<=32) ++idx;
    if (idx<str.length()&&idx!=0) {
        str = str.substr(idx);
    }
    idx = str.length() - 1;
    while (idx>=0&&str[idx]<=32) --idx;
    if (idx!=str.length() - 1) {
        str = str.substr(0, idx+1);
    }
    return str;
}


std::string
StringUtils::to_lower_case(std::string str)
{
    for (size_t i=0; i<str.length(); i++) {
        if (str[i]>='A'&&str[i]<='Z') {
            str[i] = str[i] + 'a' - 'A';
        }
    }
    return str;
}


std::string
StringUtils::convertUmlaute(std::string str)
{
    str = replace(str, "�", "ae");
    str = replace(str, "�", "Ae");
    str = replace(str, "�", "oe");
    str = replace(str, "�", "Oe");
    str = replace(str, "�", "ue");
    str = replace(str, "�", "Ue");
    str = replace(str, "�", "ss");
    str = replace(str, "�", "E");
    str = replace(str, "�", "e");
    str = replace(str, "�", "E");
    str = replace(str, "�", "e");
    return str;
}



std::string
StringUtils::replace(std::string str, const char *what,
                     const char *by)
{
    const std::string what_tmp(what);
    const std::string by_tmp(by);
    size_t idx = str.find(what);
    const size_t what_len = what_tmp.length();
    if (what_len > 0) {
        const size_t by_len = by_tmp.length();
        while (idx != std::string::npos) {
            str = str.replace(idx, what_len, by);
            idx = str.find(what, idx + by_len);
        }
    }
    return str;
}


void
StringUtils::upper(std::string &str)
{
    for (size_t i=0; i<str.length(); i++) {
        if (str[i]>='a'&&str[i]<='z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}


std::string
StringUtils::toTimeString(int time)
{
    std::ostringstream oss;
    if (time < 0) {
        oss << "-";
        time = -time;
    }
    char buffer[10];
    sprintf(buffer, "%02i:",(time/3600));
    oss << buffer;
    time=time%3600;
    sprintf(buffer, "%02i:",(time/60));
    oss << buffer;
    time=time%60;
    sprintf(buffer, "%02i", time);
    oss << buffer;
    return oss.str();
}


std::string
StringUtils::escapeXML(const std::string &orig) throw()
{
    std::string result = replace(orig, "&", "&amp;");
    result = replace(result, ">", "&gt;");
    result = replace(result, "<", "&lt;");
    result = replace(result, "\"", "&quot;");
    for (char invalid = '\1'; invalid < ' '; invalid++) {
        result = replace(result, std::string(1, invalid).c_str(), "");
    }
    return replace(result, "'", "&apos;");
}



/****************************************************************************/

