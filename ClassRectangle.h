
typedef struct Rectangle Rectangle;

struct Rectangle
{
    int width;
    int height;
    Rectangle *(*set_width)(Rectangle *self, int width);
    Rectangle *(*set_height)(Rectangle *self, int height);
    unsigned int (*get_area)(Rectangle *self);
};

Rectangle *get_rectangle();

void cleanup_rectangles(void);
