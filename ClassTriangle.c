#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AbstractClassShape.h"
#include "ClassTriangle.h"

// flags for get_triangle
#define _STANDARD  0 // in code: Triangles.STANDARD
#define _SINGLETON 1 // in code: Triangles.SINGLETON

// IT WORKS ONLY IN GCC !
// in other compilers it has to be called at the end of main():
// Triangles.cleanup();
static void cleanup (void) __attribute__((destructor));

static Triangle *set_width( Triangle *self, int width)
{
    // inheritance through the call of the respective parent method
    return (Triangle *) Shapes.set_height((Shape *) self, width);
}

static Triangle *set_height( Triangle *self, int height)
{
    // inheritance through the call of the respective parent method
    return (Triangle *) Shapes.set_height((Shape *) self, height);
}

static Triangle *immute( Triangle *self)
{
    self->is_immutable = true;
    return self;
}

static unsigned int get_width( Triangle *self)
{
    return self->width;
}

static unsigned int get_height( Triangle *self)
{
    return self->height;
}

static unsigned int get_area( Triangle *self)
{
    return self->width * self->height * 0.5;
}

static unsigned int get_uid( Triangle *self)
{
    return self->UID;
}

// linked list to keep created triangles
// due to later free allocated memory
typedef struct node node;

struct node
{
    Triangle *rec;
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
        node *tmp = cursor->next;
        free(cursor->rec);
        cursor->rec = NULL;
        free(cursor);
        cursor = tmp;
    }
    head = NULL;
}

// a kind of design pattern "factory"
static Triangle *get_triangle(int flag)
{
    if (head == NULL)
    {
        srand(time(NULL));
    }

    Triangle *myrec;
    if (head == NULL || (flag & _SINGLETON) != _SINGLETON)
    {
        myrec = (Triangle *)calloc(1,sizeof(Triangle));
        if(myrec == NULL)
        {
            printf("Error creating a new Triangle.\n");
            exit(0);
        }
        myrec->set_width = set_width;
        myrec->set_height = set_height;
        myrec->immute = immute;
        myrec->get_width = get_width;
        myrec->get_height = get_height;
        myrec->get_area = get_area;
        myrec->get_uid = get_uid;
        myrec->UID = rand();

        node *new_node = (node *)calloc(1,sizeof(node));
        if(new_node == NULL)
        {
            printf("Error creating a new node.\n");
            exit(0);
        }
        new_node->rec = myrec;
        new_node->next = head;
        head = new_node;
    }

    if((flag & _SINGLETON) == _SINGLETON)
    {
        myrec = head->rec;
    }

    return myrec;
}

// for sorting purposes
static int compare_area( const void *a, const void *b)
{
    Triangle *rec_a =  *((Triangle **) a);
    Triangle *rec_b =  *((Triangle **) b);

    if ( rec_a->get_area(rec_a) == rec_b->get_area(rec_b) ) return 0;
    else if ( rec_a->get_area(rec_a) < rec_b->get_area(rec_b) ) return -1;
    else return 1;
}

// the declaration has to be here
// then Triangles depends on uid_lookup, and uid_lookup depends on Triangles
static Triangle *uid_lookup(int UID);

// this simulates static issues of a class
struct s_triangles Triangles = {0, 0, set_width, set_height,
           immute, get_width, get_height, get_area, get_uid, get_triangle,
           uid_lookup, cleanup, compare_area, _STANDARD, _SINGLETON
};

static Triangle *uid_lookup(int UID)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        if (Triangles.get_uid(cursor->rec))
        {
            return cursor->rec;
        };
    }
    return (Triangle *) NULL;
}
