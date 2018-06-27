
#include "ClassRectangle.h"

unsigned int set_width( Rectangle *self, int width)
{
    self->width = width;
    return self->width;
}

unsigned int set_height( Rectangle *self, int height)
{
    self->height = height;
    return self->height;
}

unsigned int get_area( Rectangle *self)
{
    return self->width * self->height;
}