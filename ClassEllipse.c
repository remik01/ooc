#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AbstractClassShape.h"
#include "ClassEllipse.h"

// flags for get_ellipse
#define _STANDARD  0 // in code: Ellipses.STANDARD
#define _SINGLETON 1 // in code: Ellipses.SINGLETON

// IT WORKS ONLY IN GCC !
// in other compilers it has to be called at the end of main():
// Ellipses.cleanup();
static void cleanup (void) __attribute__((destructor));

static Ellipse *set_width( Ellipse *self, int width)
{
    // inheritance through the call of the respective parent method
    return (Ellipse *) Shapes.set_height((Shape *) self, width);
}

static Ellipse *set_height( Ellipse *self, int height)
{
    // inheritance through the call of the respective parent method
    return (Ellipse *) Shapes.set_height((Shape *) self, height);
}

static Ellipse *immute( Ellipse *self)
{
    self->is_immutable = true;
    return self;
}

static unsigned int get_width( Ellipse *self)
{
    return self->width;
}

static unsigned int get_height( Ellipse *self)
{
    return self->height;
}

static unsigned int get_area( Ellipse *self)
{
    return self->width * self->height * 3.141 * 0.25;
}

static unsigned int get_uid( Ellipse *self)
{
    return self->UID;
}

// linked list to keep created ellipses
// due to later free allocated memory
typedef struct node node;

struct node
{
    Ellipse *rec;
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



// a kind of design pattern "factory"
static Ellipse *get_ellipse(int flag)
{
    if (head == NULL)
    {
        srand(time(NULL));
    }

    Ellipse *myrec;
    if (head == NULL || (flag & _SINGLETON) != _SINGLETON)
    {
        myrec = (Ellipse *)malloc(sizeof(Ellipse));
        if(myrec == NULL)
        {
            printf("Error creating a new Ellipse.\n");
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

        node *new_node = (node *)malloc(sizeof(node));
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
    Ellipse *rec_a =  *((Ellipse **) a);
    Ellipse *rec_b =  *((Ellipse **) b);

    if ( rec_a->get_area(rec_a) == rec_b->get_area(rec_b) ) return 0;
    else if ( rec_a->get_area(rec_a) < rec_b->get_area(rec_b) ) return -1;
    else return 1;
}

// the declaration has to be here
// then Ellipses depends on uid_lookup, and uid_lookup depends on Ellipses
static Ellipse *uid_lookup(int UID);

// this simulates static issues of a class
struct s_ellipses Ellipses = {0, 0, set_width, set_height,
           immute, get_width, get_height, get_area, get_uid, get_ellipse,
           uid_lookup, cleanup, compare_area, _STANDARD, _SINGLETON
};

static Ellipse *uid_lookup(int UID)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        if (Ellipses.get_uid(cursor->rec))
        {
            return cursor->rec;
        };
    }
    return (Ellipse *) NULL;
}
