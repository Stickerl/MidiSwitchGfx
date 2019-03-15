/*
 * guiMessageDefinitions.hpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#ifndef GUI_MESSAGE_DEFINITIONS_HPP_
#define GUI_MESSAGE_DEFINITIONS_HPP_

#include <cstdint>

// UPDATE_PATCH_CFG
struct updatePatchCfgMsg
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


#endif // GUI_MESSAGE_DEFINITIONS_HPP_
