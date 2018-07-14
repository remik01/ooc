#include <stdbool.h>

typedef struct s_triangle Triangle;

struct s_triangle
{
    int width;
    int height;
    bool is_immutable;
    int UID; // a unique ID of a object
    Triangle *(*set_width)(Triangle *self, int width);
    Triangle *(*set_height)(Triangle *self, int height);
    Triangle *(*immute)(Triangle *self);
    unsigned int (*get_width)(Triangle *self);
    unsigned int (*get_height)(Triangle *self);
    unsigned int (*get_area)(Triangle *self);
    unsigned int (*get_uid)(Triangle *self);
};

// this simulates static issues of a class
struct s_triangles
{
    int width;
    int height;
    Triangle *(*set_width)(Triangle *self, int width);
    Triangle *(*set_height)(Triangle *self, int height);
    Triangle *(*immute)(Triangle *self);
    unsigned int (*get_width)(Triangle *self);
    unsigned int (*get_height)(Triangle *self);
    unsigned int (*get_area)(Triangle *self);
    unsigned int (*get_uid)(Triangle *self);
    Triangle *(*get_triangle)(int flag);
    Triangle *(*uid_lookup)(int UID);
    void (*cleanup)(void);
    int (*compare_area)( const void *a, const void *b);
    // flags for get_triangle
    int STANDARD;
    int SINGLETON;
};

extern struct s_triangles Triangles;
