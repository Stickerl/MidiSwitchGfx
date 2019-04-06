/*
 * touch_event_extension.cpp
 *
 *  Created on: 06.04.2019
 *      Author: Erwin
 */

#include "../widgetExtensions/touch_event_extension.h"

touch_event_extension::touch_event_extension(Drawable& widget) :
    widgetRev(widget)
{
    setPosition(widgetRev.getX(), widgetRev.getY(), widgetRev.getHeight(), widgetRev.getWidth());


}

touch_event_extension::~touch_event_extension() {
    // TODO Auto-generated destructor stub
}

void touch_event_extension::handleClickEvent(const ClickEvent& evt) {
    switch(evt.getType()){
    case ClickEvent::RELEASED:
        if(NULL != releasedCb){
            releasedCb->execute(evt);
        }
        break;
    case ClickEvent::PRESSED:
        if(NULL != pressedCb){
            pressedCb->execute(evt);
        }
        break;
    case ClickEvent::CANCEL:
        if(NULL != cancelCb){
            cancelCb->execute(evt);
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
            gestureCb->execute(evt);
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
            dragCb->execute(evt);
        }
        break;
    default:
        break;
    }
}

void touch_event_extension::handleTickEvent() {

}

void touch_event_extension::setDragCb(touchgfx::GenericCallback<const DragEvent& >& callback) {
    dragCb = &callback;
}

void touch_event_extension::setGestureCb(touchgfx::GenericCallback<const GestureEvent& >& callback) {
    gestureCb = &callback;
}

void touch_event_extension::setPressedCb(touchgfx::GenericCallback<const ClickEvent& >& callback) {
    pressedCb = &callback;
}

void touch_event_extension::setReleasedCb(touchgfx::GenericCallback<const ClickEvent& >& callback) {
    releasedCb = &callback;
}

void touch_event_extension::setCancelCb(touchgfx::GenericCallback<const ClickEvent& >& callback) {
    cancelCb = &callback;
}

Drawable& touch_event_extension::getWidgetRev() {
    return widgetRev;
}






