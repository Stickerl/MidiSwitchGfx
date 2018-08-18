// -alpha_dither yes -dither 2 -non_opaque_image_format ARGB8888 -opaque_image_format RGB565 0xbaef6aa2
// Generated by imageconverter. Please, do not edit!

#include <touchgfx/Bitmap.hpp>
#include <BitmapDatabase.hpp>

#ifndef NO_USING_NAMESPACE_TOUCHGFX
using namespace touchgfx;
#endif

extern const unsigned char _MidiSwitchBG[]; 
extern const unsigned char _MidiSwitchBGNoShip[]; 
extern const unsigned char _Round_very_small[]; 
extern const unsigned char _Round_very_small_pressed[]; 
extern const unsigned char _Teach_round_small[]; 
extern const unsigned char _Teach_round_small_pressed[]; 
extern const unsigned char _dark_icons_go_back_32[]; 
extern const unsigned char _dark_icons_go_next_32[]; 
extern const unsigned char _dark_icons_inbox_48[]; 
extern const unsigned char _dark_icons_settings_48[]; 
extern const unsigned char _dark_radio_buttons_radio_round_button_active[]; 
extern const unsigned char _dark_radio_buttons_radio_round_button_inactive[]; 

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { _MidiSwitchBG, 0, 800, 480, 0, 0, 800, 480, touchgfx::Bitmap::RGB565 },
    { _MidiSwitchBGNoShip, 0, 800, 480, 0, 0, 800, 480, touchgfx::Bitmap::RGB565 },
    { _Round_very_small, 0, 113, 40, 12, 5, 89, 29, touchgfx::Bitmap::ARGB8888 },
    { _Round_very_small_pressed, 0, 113, 40, 14, 5, 85, 31, touchgfx::Bitmap::ARGB8888 },
    { _Teach_round_small, 0, 113, 40, 12, 5, 89, 29, touchgfx::Bitmap::ARGB8888 },
    { _Teach_round_small_pressed, 0, 113, 40, 14, 5, 85, 31, touchgfx::Bitmap::ARGB8888 },
    { _dark_icons_go_back_32, 0, 32, 30, 1, 2, 8, 24, touchgfx::Bitmap::ARGB8888 },
    { _dark_icons_go_next_32, 0, 32, 30, 23, 2, 8, 24, touchgfx::Bitmap::ARGB8888 },
    { _dark_icons_inbox_48, 0, 48, 41, 6, 34, 36, 5, touchgfx::Bitmap::ARGB8888 },
    { _dark_icons_settings_48, 0, 48, 48, 44, 19, 2, 8, touchgfx::Bitmap::ARGB8888 },
    { _dark_radio_buttons_radio_round_button_active, 0, 44, 44, 9, 8, 26, 28, touchgfx::Bitmap::ARGB8888 },
    { _dark_radio_buttons_radio_round_button_inactive, 0, 44, 44, 9, 8, 26, 28, touchgfx::Bitmap::ARGB8888 }
};

namespace BitmapDatabase
{
  const touchgfx::Bitmap::BitmapData* getInstance()
  {
    return bitmap_database;
  }
  uint16_t getInstanceSize()
  {
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
  }
}
