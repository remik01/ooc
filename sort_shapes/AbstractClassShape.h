#include <stdbool.h>

typedef struct s_shape Shape;

struct s_shape
{
    int width;
    int height;
    bool is_immutable;
    int UID; // a unique ID of a object
    Shape *(*set_width)(Shape *self, int width);
    Shape *(*set_height)(Shape *self, int height);
    Shape *(*immute)(Shape *self);
    unsigned int (*get_width)(Shape *self);
    unsigned int (*get_height)(Shape *self);
    unsigned int (*get_area)(Shape *self);
    unsigned int (*get_uid)(Shape *self);
};

// this simulates static issues of a class
struct s_shapes
{
    int width;
    int height;
    Shape *(*set_width)(Shape *self, int width);
    Shape *(*set_height)(Shape *self, int height);
    Shape *(*immute)(Shape *self);
    unsigned int (*get_width)(Shape *self);
    unsigned int (*get_height)(Shape *self);
    unsigned int (*get_area)(Shape *self);
    unsigned int (*get_uid)(Shape *self);
    Shape *(*get_shape)(int flag);
    Shape *(*uid_lookup)(int UID);
    void (*cleanup)(void);
    int (*compare_area)( const void *a, const void *b);
    // flags for get_shape
    int STANDARD;
    int SINGLETON;
};

extern struct s_shapes Shapes;
