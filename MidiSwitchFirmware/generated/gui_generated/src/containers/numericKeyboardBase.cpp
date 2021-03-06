/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/numericKeyboardBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

numericKeyboardBase::numericKeyboardBase()
{
    setWidth(318);
    setHeight(110);

    box1.setPosition(0, 0, 318, 110);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    box1.setAlpha(130);

    key_0.setXY(4, 4);
    key_0.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_0.setLabelText(TypedText(T_SINGLEUSEID20));
    key_0.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_0.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_1.setXY(56, 4);
    key_1.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_1.setLabelText(TypedText(T_SINGLEUSEID21));
    key_1.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_1.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_2.setXY(108, 4);
    key_2.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_2.setLabelText(TypedText(T_SINGLEUSEID22));
    key_2.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_2.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_3.setXY(160, 4);
    key_3.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_3.setLabelText(TypedText(T_SINGLEUSEID23));
    key_3.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_3.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_4.setXY(212, 4);
    key_4.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_4.setLabelText(TypedText(T_SINGLEUSEID24));
    key_4.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_4.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_5.setXY(4, 56);
    key_5.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_5.setLabelText(TypedText(T_SINGLEUSEID25));
    key_5.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_5.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_6.setXY(56, 56);
    key_6.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_6.setLabelText(TypedText(T_SINGLEUSEID26));
    key_6.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_6.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_7.setXY(108, 56);
    key_7.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_7.setLabelText(TypedText(T_SINGLEUSEID27));
    key_7.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_7.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_8.setXY(160, 56);
    key_8.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_8.setLabelText(TypedText(T_SINGLEUSEID28));
    key_8.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_8.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    key_9.setXY(212, 56);
    key_9.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONPRESSED_ID));
    key_9.setLabelText(TypedText(T_SINGLEUSEID29));
    key_9.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(90, 90, 90));
    key_9.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(100, 100, 100));

    returnButton.setXY(264, 4);
    returnButton.setBitmaps(Bitmap(BITMAP_KEYBOARDRETURNBUTTONRELEASED_ID), Bitmap(BITMAP_KEYBOARDRETURNBUTTONPRESSED_ID));

    cancel.setXY(264, 56);
    cancel.setBitmaps(Bitmap(BITMAP_KEYBOARDBUTTONCANCELRELEASED_ID), Bitmap(BITMAP_KEYBOARDBUTTONCANCELPRESSED_ID));

    add(box1);
    add(key_0);
    add(key_1);
    add(key_2);
    add(key_3);
    add(key_4);
    add(key_5);
    add(key_6);
    add(key_7);
    add(key_8);
    add(key_9);
    add(returnButton);
    add(cancel);
}

void numericKeyboardBase::initialize()
{
	
}
