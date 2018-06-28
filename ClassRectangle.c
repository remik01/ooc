#include <stdlib.h>
#include "ClassRectangle.h"

Rectangle *set_width( Rectangle *self, int width)
{
    self->width = width;
    return self;
}

Rectangle *set_height( Rectangle *self, int height)
{
    self->height = height;
    return self;
}

unsigned int get_area( Rectangle *self)
{
    return self->width * self->height;
}

// a kind of design pattern "factory"
Rectangle *get_rectangle()
{
    Rectangle *myrec = malloc(sizeof(Rectangle));
    myrec->set_width = set_width;
    myrec->set_height = set_height;
    myrec->get_area = get_area;

    return myrec;
}
