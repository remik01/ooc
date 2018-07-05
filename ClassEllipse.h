#include <stdbool.h>

typedef struct s_ellipse Ellipse;

struct s_ellipse
{
    int width;
    int height;
    bool is_immutable;
    int UID; // a unique ID of a object
    Ellipse *(*set_width)(Ellipse *self, int width);
    Ellipse *(*set_height)(Ellipse *self, int height);
    Ellipse *(*immute)(Ellipse *self);
    unsigned int (*get_width)(Ellipse *self);
    unsigned int (*get_height)(Ellipse *self);
    unsigned int (*get_area)(Ellipse *self);
    unsigned int (*get_uid)(Ellipse *self);
};

// this simulates static issues of a class
struct s_ellipses
{
    int width;
    int height;
    Ellipse *(*set_width)(Ellipse *self, int width);
    Ellipse *(*set_height)(Ellipse *self, int height);
    Ellipse *(*immute)(Ellipse *self);
    unsigned int (*get_width)(Ellipse *self);
    unsigned int (*get_height)(Ellipse *self);
    unsigned int (*get_area)(Ellipse *self);
    unsigned int (*get_uid)(Ellipse *self);
    Ellipse *(*get_ellipse)(int flag);
    Ellipse *(*uid_lookup)(int UID);
    void (*cleanup)(void);
    int (*compare_area)( const void *a, const void *b);
    // flags for get_ellipse
    int STANDARD;
    int SINGLETON;
};

extern struct s_ellipses Ellipses;
