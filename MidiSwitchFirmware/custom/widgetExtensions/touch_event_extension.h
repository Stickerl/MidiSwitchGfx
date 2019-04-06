/*
 * touch_event_extension.h
 *
 *  Created on: 06.04.2019
 *      Author: Erwin
 */

#ifndef WIDGETEXTENSIONS_TOUCH_EVENT_EXTENSION_H_
#define WIDGETEXTENSIONS_TOUCH_EVENT_EXTENSION_H_

#include <touchgfx/Drawable.hpp>
using namespace touchgfx;

class touch_event_extension : public Drawable
{
public:
    touch_event_extension(Drawable& widget);
    virtual ~touch_event_extension();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleTickEvent();

    void setDragCb(touchgfx::GenericCallback<const DragEvent& >& callback);
    void setGestureCb(touchgfx::GenericCallback<const GestureEvent& >& callback);
    void setPressedCb(touchgfx::GenericCallback<const ClickEvent& >& callback);
    void setReleasedCb(touchgfx::GenericCallback<const ClickEvent& >& callback);
    void setCancelCb(touchgfx::GenericCallback<const ClickEvent& >& callback);
    Drawable& getWidgetRev();

protected:
    Drawable& widgetRev;
    touchgfx::GenericCallback<const DragEvent& >* dragCb;
    touchgfx::GenericCallback<const GestureEvent& >* gestureCb;
    touchgfx::GenericCallback<const ClickEvent& >* pressedCb;
    touchgfx::GenericCallback<const ClickEvent& >* releasedCb;
    touchgfx::GenericCallback<const ClickEvent& >* cancelCb;

};

#endif /* WIDGETEXTENSIONS_TOUCH_EVENT_EXTENSION_H_ */
