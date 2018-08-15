/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/ListLayout.hpp>

namespace touchgfx
{

class AdjustElements
{
public:
    AdjustElements(Drawable* d, Direction dir) : insertedCoord(0),
        newElementPassed(false),
        newElement(d),
        direction(dir) {}

    void handleInsert(Drawable& d)
    {
        if (!newElementPassed)
        {
            if (newElement == &d)
            {
                newElementPassed = true;
            }
            else
            {
                if (direction == SOUTH)
                {
                    insertedCoord = d.getY() + d.getHeight();
                }
                else if (direction == EAST)
                {
                    insertedCoord = d.getX() + d.getWidth();
                }
            }
        }
        else
        {
            if (direction == SOUTH)
            {
                d.setY(d.getY() + newElement->getHeight());
            }
            else if (direction == EAST)
            {
                d.setX(d.getX() + newElement->getWidth());
            }

        }
    }
    void handleRemove(Drawable& d)
    {
        if (!newElementPassed)
        {
            if (newElement == &d)
            {
                newElementPassed = true;
            }
        }
        else
        {
            if (direction == SOUTH)
            {
                d.setY(d.getY() - newElement->getHeight());
            }
            else if (direction == EAST)
            {
                d.setX(d.getX() - newElement->getWidth());
            }

        }
        if (newElement != &d)
        {
            if (direction == SOUTH)
            {
                if (d.getWidth() > insertedCoord)
                {
                    insertedCoord = d.getWidth();
                }
            }
            else if (direction == EAST)
            {
                if (d.getHeight() > insertedCoord)
                {
                    insertedCoord = d.getHeight();
                }
            }
        }
    }

    int16_t insertedCoord;
    bool newElementPassed;
private:
    Drawable* newElement;
    Direction direction;
}; //lint !e1712

void ListLayout::internalAddElement(Drawable& d, int16_t coord)
{
    switch (direction)
    {
    case SOUTH:
        if (rect.width < d.getWidth())
        {
            rect.width = d.getWidth();
        }
        rect.height += d.getHeight();
        d.setX(0);
        d.setY(coord);
        yOffset += d.getHeight();
        break;
    case EAST:
        if (rect.height < d.getHeight())
        {
            rect.height = d.getHeight();
        }
        rect.width += d.getWidth();
        d.setX(coord);
        d.setY(0);
        xOffset += d.getWidth();
        break;
    case NORTH:
    case WEST:
    default:
        break;
    }
}

void ListLayout::internalRemoveElement(Drawable& d, int16_t coord)
{
    switch (direction)
    {
    case SOUTH:
        if (rect.width > coord)
        {
            rect.width = coord;
        }
        rect.height -= d.getHeight();
        d.setX(0);
        d.setY(0);
        yOffset -= d.getHeight();
        break;
    case EAST:
        if (rect.height > coord)
        {
            rect.height = coord;
        }
        rect.width -= d.getWidth();
        d.setX(0);
        d.setY(0);
        xOffset -= d.getWidth();
        break;
    case NORTH:
    case WEST:
    default:
        break;
    }
}

void ListLayout::add(Drawable& d)
{
    internalAddElement(d, (direction == SOUTH) ? yOffset : xOffset);
    Container::add(d);
    if (parent)
    {
        parent->childGeometryChanged();
    }
}

void ListLayout::removeAll()
{
    xOffset = 0;
    yOffset = 0;
    setWidth(0);
    setHeight(0);
    Container::removeAll();
    if (parent)
    {
        parent->childGeometryChanged();
    }
}

void ListLayout::insert(Drawable* previousElement, Drawable& d)
{
    if (!firstChild)
    {
        // List is empty, just add the new entry
        add(d);
        return;
    }
    Container::insert(previousElement, d);
    AdjustElements tmp(&d, direction);
    Callback<AdjustElements, Drawable&> function(&tmp, &AdjustElements::handleInsert);
    forEachChild(&function);
    internalAddElement(d, tmp.insertedCoord);
    if (parent)
    {
        parent->childGeometryChanged();
    }
}

void ListLayout::remove(Drawable& d)
{
    AdjustElements tmp(&d, direction);
    Callback<AdjustElements, Drawable&> function(&tmp, &AdjustElements::handleRemove);
    forEachChild(&function);
    if (tmp.newElementPassed)
    {
        internalRemoveElement(d, tmp.insertedCoord);
        Container::remove(d);
    }
    if (parent)
    {
        parent->childGeometryChanged();
    }
}

} // namespace touchgfx
