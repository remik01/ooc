#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AbstractClassShape.h"
#include "ClassRectangle.h"

// flags for get_rectangle
#define _STANDARD  0 // in code: Rectangles.STANDARD
#define _SINGLETON 1 // in code: Rectangles.SINGLETON

// IT WORKS ONLY IN GCC !
// in other compilers it has to be called at the end of main():
// Rectangles.cleanup();
static void cleanup (void) __attribute__((destructor));

static Rectangle *set_width( Rectangle *self, int width)
{
    // inheritance through the call of the respective parent method
    return (Rectangle *) Shapes.set_width((Shape *) self, width);
}

static Rectangle *set_height( Rectangle *self, int height)
{
    // inheritance through the call of the respective parent method
    return (Rectangle *) Shapes.set_height((Shape *) self, height);
}

static Rectangle *immute( Rectangle *self)
{
    self->is_immutable = true;
    return self;
}

static unsigned int get_width( Rectangle *self)
{
    return self->width;
}

static unsigned int get_height( Rectangle *self)
{
    return self->height;
}

static unsigned int get_area( Rectangle *self)
{
    return self->width * self->height;
}

static unsigned int get_uid( Rectangle *self)
{
    return self->UID;
}

// linked list to keep created rectangles
// due to later free allocated memory
typedef struct node node;

struct node
{
    Rectangle *rec;
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
static Rectangle *get_rectangle(int flag)
{
    if (head == NULL)
    {
        srand(time(NULL));
    }

    Rectangle *myrec;
    if (head == NULL || (flag & _SINGLETON) != _SINGLETON)
    {
        myrec = (Rectangle *)calloc(1,sizeof(Rectangle));
        if(myrec == NULL)
        {
            printf("Error creating a new Rectangle.\n");
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
    Rectangle *rec_a =  *((Rectangle **) a);
    Rectangle *rec_b =  *((Rectangle **) b);

    if ( rec_a->get_area(rec_a) == rec_b->get_area(rec_b) ) return 0;
    else if ( rec_a->get_area(rec_a) < rec_b->get_area(rec_b) ) return -1;
    else return 1;
}

// the declaration has to be here
// then Rectangles depends on uid_lookup, and uid_lookup depends on Rectangles
static Rectangle *uid_lookup(int UID);

// this simulates static issues of a class
struct s_rectangles Rectangles = {0, 0, set_width, set_height,
           immute, get_width, get_height, get_area, get_uid, get_rectangle,
           uid_lookup, cleanup, compare_area, _STANDARD, _SINGLETON
};

static Rectangle *uid_lookup(int UID)
{
    node *cursor = head;
    while(cursor != NULL)
    {
        if (Rectangles.get_uid(cursor->rec))
        {
            return cursor->rec;
        };
    }
    return (Rectangle *) NULL;
}
