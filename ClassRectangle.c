#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ClassRectangle.h"

// flags for get_rectangle
#define _STANDARD  0 // in code: Rectangles.STANDARD
#define _SINGLETON 1 // in code: Rectangles.SINGLETON

Rectangle *set_width( Rectangle *self, int width)
{
    if(!self->is_immutable)
    {
        self->width = width;
    }
    return self;
}

Rectangle *set_height( Rectangle *self, int height)
{
    if(!self->is_immutable)
    {
        self->height = height;
    }
    return self;
}

Rectangle *immute( Rectangle *self)
{
    self->is_immutable = true;
    return self;
}


unsigned int get_width( Rectangle *self)
{
    return self->width;
}

unsigned int get_height( Rectangle *self)
{
    return self->height;
}

unsigned int get_area( Rectangle *self)
{
    return self->width * self->height;
}


// linked list to keep created rectangles
// due to later free allocated memory
typedef struct node node;

struct node
{
    Rectangle *rec;
    struct node *next;
};

node *head = NULL;

void cleanup(void)
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
Rectangle *get_rectangle(int flag)
{
    Rectangle *myrec;
    if (head == NULL || (flag & _SINGLETON) != _SINGLETON)
    {
        myrec = (Rectangle *)malloc(sizeof(Rectangle));
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
int compare_area( const void *a, const void *b)
{
    Rectangle *rec_a =  *((Rectangle **) a);
    Rectangle *rec_b =  *((Rectangle **) b);

    if ( rec_a->get_area(rec_a) == rec_b->get_area(rec_b) ) return 0;
    else if ( rec_a->get_area(rec_a) < rec_b->get_area(rec_b) ) return -1;
    else return 1;
}

// this simulates static issues of a class
struct s_rectangles Rectangles = {0, 0, set_width, set_height,
           immute, get_width, get_height, get_area, get_rectangle,
           cleanup, compare_area, _STANDARD, _SINGLETON
};
