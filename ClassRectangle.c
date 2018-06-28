
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


const struct rectangle_library Library =
{
    .set_width = set_width,
    .set_height = set_height,
    .get_area = get_area
};
