#include <stdio.h>
#include <stdlib.h>
#include "ClassRectangle.h"

Rectangle *set_width( Rectangle *self, int width)
{
    self->width = width;
    return self;
}

Rectangle *set_height( Rectangle *self, int height)
{
    self->height = height;
    return self;
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

void cleanup_rectangles(void)
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
Rectangle *get_rectangle()
{
    Rectangle *myrec = (Rectangle *)malloc(sizeof(Rectangle));
    if(myrec == NULL)
    {
        printf("Error creating a new Rectangle.\n");
        exit(0);
    }
    myrec->set_width = set_width;
    myrec->set_height = set_height;
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

    return myrec;
}
