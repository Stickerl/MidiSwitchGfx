/*
 * guiMessageDefinitions.hpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#ifndef GUI_MESSAGE_DEFINITIONS_HPP_
#define GUI_MESSAGE_DEFINITIONS_HPP_

#include <cstdint>

/*********************************************
 * Backend to GUI message definitions
 *********************************************/
// UPDATE_PATCH_CFG
struct patchCfgMsg
{
    std::uint8_t programNr;
    std::uint8_t defaultOut;
    std::uint8_t switch1Name;
    std::uint8_t switch1Value;
    std::uint8_t switch1Output;
    std::uint8_t switch2Name;
    std::uint8_t switch2Value;
    std::uint8_t switch2Output;
};


/*********************************************
 * GUI to Backend message definitions
 *********************************************/
// PROG_NR
struct progNrMsg
{
    std::uint8_t programNr;
};

struct outputCfgMsg
{
    std::uint8_t outputCfgNr;
    std::uint8_t outputVal;
};

struct switchSettingMsg
{
    std::uint8_t switchIndex;
    std::uint8_t switchNumber;
    std::uint8_t switchValue;
};

#endif // GUI_MESSAGE_DEFINITIONS_HPP_
