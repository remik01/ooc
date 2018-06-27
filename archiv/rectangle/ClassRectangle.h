
typedef struct
{
    int width;
    int height;
} Rectangle;

unsigned int set_width(Rectangle *self, int width);

unsigned int set_height(Rectangle *self, int height);

unsigned int get_area(Rectangle *self);
