#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "AbstractClassShape.h"
#include "ClassTriangle.h"
#include "ClassEllipse.h"
#include "ClassRectangle.h"

void merge_sorted(Shape *my_shape[], Shape *sorted_shape[]);

void *partial_qsort(void *my_shape);

int main(int argc, char const *argv[])
{
    // the classes have destructors which work only in GCC
    // in the case of another compiler, they have to be set explicitely:
    // atexit(Rectangles.cleanup);
    // atexit(Triangles.cleanup);
    // atexit(Ellipses.cleanup);

    extern const char _binary_random_data_dat_start;
    extern const char _binary_random_data_dat_end;
    extern const int _binary_random_data_dat_size;

    printf("_binary_random_data_dat_size %d %c %c\n",
        _binary_random_data_dat_size,
        _binary_random_data_dat_end,
        _binary_random_data_dat_start);

    Shape *my_shape[1000];
    int UID;

    for(int i = 0; i < 1000; i++)
    {
        if(i < 300)
        {
            // Triangles
            my_shape[i] = (Shape *) Triangles.get_triangle(Triangles.STANDARD);
        }
        else if(i < 600)
        {
            // Ellipses
            my_shape[i] = (Shape *) Ellipses.get_ellipse(Ellipses.STANDARD);
        }
        else
        {
            // Rectangles
            //the last 25 elements are the same,
            // due to an optional singleton featureof the factory
            my_shape[i] = (Shape *) Rectangles.get_rectangle(
                              (i < 975 ? Rectangles.STANDARD : Rectangles.SINGLETON)
                          );
        }


        // as the objects are pointers,
        // when a singleton will be changed,
        // then all other will also be changed
        // except we make them immutable
        Shapes.set_width(my_shape[i], (31 * i) % 69)
        ->set_height(my_shape[i], (51 * i) % 155 );
        if(i == 975)
        {
            my_shape[i]->immute(my_shape[i]);
            UID = my_shape[i]->get_uid(my_shape[i]);
        }



    }

    pthread_t thread_lh;
    pthread_t thread_rh;

    if(pthread_create(&thread_lh, NULL, partial_qsort, my_shape))
    {
        fprintf(stderr, "Error creating thread lh\n");
        return 1;
    }

    if(pthread_create(&thread_rh, NULL, partial_qsort, my_shape + 500))
    {
        fprintf(stderr, "Error creating thread rh\n");
        return 1;
    }

    if(pthread_join(thread_lh, NULL))
    {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    if(pthread_join(thread_rh, NULL))
    {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    // qsort( my_shape, 500, sizeof(Rectangle *), Rectangles.compare_area );
    // qsort( my_shape + 500, 500, sizeof(Rectangle *), Rectangles.compare_area );

    Shape *sorted_shape[1000];

    merge_sorted(my_shape, sorted_shape);

    for(int i = 0; i < 1000; i++)
    {
        printf("%d x %d = %d (%d)\n", sorted_shape[i]->get_width(sorted_shape[i]),
               sorted_shape[i]->get_height(sorted_shape[i]),
               sorted_shape[i]->get_area(sorted_shape[i]), sorted_shape[i]->get_uid(sorted_shape[i]));
    }

    Rectangle *singleton = Rectangles.uid_lookup(UID);
    if(singleton != NULL)
    {
        printf("the singleton is: %d x %d = %d (%d)\n",
               Rectangles.get_width(singleton),
               Rectangles.get_height(singleton),
               Rectangles.get_area(singleton),
               Rectangles.get_uid(singleton));
    }

    return 0;
}

void merge_sorted(Shape *my_shape[], Shape *sorted_shape[])
{
    Shape **rec_lh, **rec_rh, **rec_lh_end, **rec_rh_end, **sorted_shape_walk;

    rec_lh = my_shape;
    rec_lh_end = my_shape + 499;
    rec_rh = my_shape + 500;
    rec_rh_end = my_shape + 999;
    sorted_shape_walk = sorted_shape;

    while(rec_lh <= rec_lh_end && rec_rh <= rec_rh_end)
    {
        *sorted_shape_walk++ = (*rec_lh)->get_area(*rec_lh) < (*rec_rh)->get_area(*rec_rh) ?
                               *rec_lh++ : *rec_rh++;
    }

    while(rec_lh <= rec_lh_end)
    {
        *sorted_shape_walk++ = *rec_lh++;
    }

    while(rec_rh <= rec_rh_end)
    {
        *sorted_shape_walk++ = *rec_rh++;
    }

    return;
}

void *partial_qsort(void *my_shape)
{
    qsort( my_shape, 500, sizeof(Shape *), Shapes.compare_area );
    return NULL;
}
