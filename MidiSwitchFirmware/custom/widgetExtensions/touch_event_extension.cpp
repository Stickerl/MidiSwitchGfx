/*
 * touch_event_extension.cpp
 *
 *  Created on: 06.04.2019
 *      Author: Erwin
 */

#include "touch_event_extension.hpp"

using namespace touchgfx;

touch_event_extension::touch_event_extension(Drawable& widget) :
    widgetRev(widget),
    dragCb(NULL),
    gestureCb(NULL),
    pressedCb(NULL),
    releasedCb(NULL),
    cancelCb(NULL),
    tickCb(NULL)
{
    setPosition(widgetRev.getX(), widgetRev.getY(), widgetRev.getWidth(), widgetRev.getHeight());
    setTouchable(true);
}

touch_event_extension::~touch_event_extension() {

}

void touch_event_extension::handleClickEvent(const ClickEvent& evt) {
    switch(evt.getType()){
    case ClickEvent::RELEASED:
        if(NULL != releasedCb){
            releasedCb->execute(getWidgetRev(), evt);
        }
        break;
    case ClickEvent::PRESSED:
        if(NULL != pressedCb){
            pressedCb->execute(getWidgetRev(), evt);
        }
        break;
    case ClickEvent::CANCEL:
        if(NULL != cancelCb){
            cancelCb->execute(getWidgetRev(), evt);
        }
        break;
    default:
        break;
    }
}

void touch_event_extension::handleGestureEvent(const GestureEvent& evt) {
    switch(evt.getType()){
    case ClickEvent::EVENT_GESTURE:
        if(NULL != gestureCb){
            gestureCb->execute(getWidgetRev(), evt);
        }
        break;
    default:
        break;
    }
}

void touch_event_extension::handleDragEvent(const DragEvent& evt) {
    switch(evt.getType()){
    case ClickEvent::EVENT_DRAG:
        if(NULL != dragCb){
            dragCb->execute(getWidgetRev(), evt);
        }
        break;
    default:
        break;
    }
}

void touch_event_extension::handleTickEvent() {

}

void touch_event_extension::setDragCb(touchgfx::GenericCallback<Drawable&, const DragEvent& >& callback) {
    dragCb = &callback;
}

void touch_event_extension::setGestureCb(touchgfx::GenericCallback<Drawable&, const GestureEvent& >& callback) {
    gestureCb = &callback;
}

void touch_event_extension::setPressedCb(touchgfx::GenericCallback<Drawable&, const ClickEvent& >& callback) {
    pressedCb = &callback;
}

void touch_event_extension::setReleasedCb(touchgfx::GenericCallback<Drawable&, const ClickEvent& >& callback) {
    releasedCb = &callback;
}

void touch_event_extension::setCancelCb(touchgfx::GenericCallback<Drawable&, const ClickEvent& >& callback) {
    cancelCb = &callback;
}

void touch_event_extension::setTickCb(touchgfx::GenericCallback<Drawable&, void>& callback) {
    tickCb = &callback;
}

Drawable& touch_event_extension::getWidgetRev() {
    return widgetRev;
}






