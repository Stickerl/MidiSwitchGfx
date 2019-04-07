/*
 * touch_event_extension.h
 *
 *  Created on: 06.04.2019
 *      Author: Erwin
 */

#ifndef WIDGETEXTENSIONS_TOUCH_EVENT_EXTENSION_H_
#define WIDGETEXTENSIONS_TOUCH_EVENT_EXTENSION_H_

#include <touchgfx/Drawable.hpp>
#include <touchgfx/containers/Container.hpp>
using namespace touchgfx;

class touch_event_extension : public Container
{
public:
    touch_event_extension(Drawable& widget);
    virtual ~touch_event_extension();


    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleGestureEvent(const GestureEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleTickEvent();

    virtual void setDragCb(touchgfx::GenericCallback<Drawable&, const DragEvent& >& callback);
    virtual void setGestureCb(touchgfx::GenericCallback<Drawable&, const GestureEvent& >& callback);
    virtual void setPressedCb(touchgfx::GenericCallback<Drawable&, const ClickEvent& >& callback);
    virtual void setReleasedCb(touchgfx::GenericCallback<Drawable&, const ClickEvent& >& callback);
    virtual void setCancelCb(touchgfx::GenericCallback<Drawable&, const ClickEvent& >& callback);
    virtual void setTickCb(touchgfx::GenericCallback<Drawable&, void>& callback);
    Drawable& getWidgetRev();

protected:
    Drawable& widgetRev;
    touchgfx::GenericCallback<Drawable&, const DragEvent& >* dragCb;
    touchgfx::GenericCallback<Drawable&, const GestureEvent& >* gestureCb;
    touchgfx::GenericCallback<Drawable&, const ClickEvent& >* pressedCb;
    touchgfx::GenericCallback<Drawable&, const ClickEvent& >* releasedCb;
    touchgfx::GenericCallback<Drawable&, const ClickEvent& >* cancelCb;
    touchgfx::GenericCallback<Drawable&, void>* tickCb;

};

#endif /* WIDGETEXTENSIONS_TOUCH_EVENT_EXTENSION_H_ */
