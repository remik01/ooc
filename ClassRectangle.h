#include <stdbool.h>

typedef struct s_rectangle Rectangle;

struct s_rectangle
{
    int width;
    int height;
    bool is_immutable;
    Rectangle *(*set_width)(Rectangle *self, int width);
    Rectangle *(*set_height)(Rectangle *self, int height);
    Rectangle *(*immute)(Rectangle *self);
    unsigned int (*get_width)(Rectangle *self);
    unsigned int (*get_height)(Rectangle *self);
    unsigned int (*get_area)(Rectangle *self);
};

// this simulates static issues of a class
struct s_rectangles
{
    int width;
    int height;
    Rectangle *(*set_width)(Rectangle *self, int width);
    Rectangle *(*set_height)(Rectangle *self, int height);
    Rectangle *(*immute)(Rectangle *self);
    unsigned int (*get_width)(Rectangle *self);
    unsigned int (*get_height)(Rectangle *self);
    unsigned int (*get_area)(Rectangle *self);
    Rectangle *(*get_rectangle)(int);
    void (*cleanup)(void);
    int (*compare_area)( const void *a, const void *b);
    // flags for get_rectangle
    int STANDARD;
    int SINGLETON;
};

extern struct s_rectangles Rectangles;
