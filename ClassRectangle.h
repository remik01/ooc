
typedef struct Rectangle Rectangle;

struct Rectangle
{
    int width;
    int height;
    Rectangle *(*set_width)(Rectangle *self, int width);
    Rectangle *(*set_height)(Rectangle *self, int height);
    unsigned int (*get_width)(Rectangle *self);
    unsigned int (*get_height)(Rectangle *self);
    unsigned int (*get_area)(Rectangle *self);
};

struct Rectangles
{
    int width;
    int height;
    Rectangle *(*set_width)(Rectangle *self, int width);
    Rectangle *(*set_height)(Rectangle *self, int height);
    unsigned int (*get_width)(Rectangle *self);
    unsigned int (*get_height)(Rectangle *self);
    unsigned int (*get_area)(Rectangle *self);
    Rectangle *(*get_rectangle)(void);
    void (*cleanup)(void);
    int (*compare_area)( const void *a, const void *b);
};

extern struct Rectangles Rectangles;
