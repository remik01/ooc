#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AbstractClassShape.h"

// flags for get_shape
#define _STANDARD  0 // in code: Shapes.STANDARD
#define _SINGLETON 1 // in code: Shapes.SINGLETON

static Shape *set_width( Shape *self, int width)
{
    if(!self->is_immutable)
    {
        self->width = width;
    }
    return self;
}

static Shape *set_height( Shape *self, int height)
{
    if(!self->is_immutable)
    {
        self->height = height;
    }
    return self;
}

static Shape *immute( Shape *self)
{
    self->is_immutable = true;
    return self;
}

static unsigned int get_width( Shape *self)
{
    return self->width;
}

static unsigned int get_height( Shape *self)
{
    return self->height;
}

// this method shall be overwritten,
// therefore it dies when called
static unsigned int get_area( Shape *self)
{
    printf("ERROR: abstract method called!\n");
    exit(1);
}

static unsigned int get_uid( Shape *self)
{
    return self->UID;
}

// linked list to keep created shapes
// due to later free allocated memory
typedef struct node node;

struct node
{
    Shape *rec;
    struct node *next;
};

// the variable is not visible outside of the file
// so it is a kind of private static
static node *head = NULL;

static void cleanup(void)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        node *tmp = cursor;
        free(cursor->rec);
        cursor->rec = NULL;
        free(cursor);
        cursor = tmp->next;
    }
    head = NULL;
}



// this is an abstract class and shall not have instances
// therefore, the method producing objects is set to NULL
#define get_shape NULL


// for sorting purposes
static int compare_area( const void *a, const void *b)
{
    Shape *rec_a =  *((Shape **) a);
    Shape *rec_b =  *((Shape **) b);

    if ( rec_a->get_area(rec_a) == rec_b->get_area(rec_b) ) return 0;
    else if ( rec_a->get_area(rec_a) < rec_b->get_area(rec_b) ) return -1;
    else return 1;
}

// the declaration has to be here
// then Shapes depends on uid_lookup, and uid_lookup depends on Shapes
static Shape *uid_lookup(int UID);

// this simulates static issues of a class
struct s_shapes Shapes = {0, 0, set_width, set_height,
           immute, get_width, get_height, get_area, get_uid, get_shape,
           uid_lookup, cleanup, compare_area, _STANDARD, _SINGLETON
};

static Shape *uid_lookup(int UID)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        if (Shapes.get_uid(cursor->rec))
        {
            return cursor->rec;
        };
    }
    return (Shape *) NULL;
}
