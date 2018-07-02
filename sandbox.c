#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "ClassRectangle.h"

void merge_sorted(Rectangle *myrec[], Rectangle *sorted_rec[]);

void *partial_qsort(void *myrec);

int main(int argc, char const *argv[])
{
    Rectangle *myrec[1000];
    int UID;

    for(int i = 0; i < 1000; i++)
    {
        //the last 25 elements are the same,
        // due to an optional singleton featureof the factory
        myrec[i] = Rectangles.get_rectangle(
                       (i < 975 ? Rectangles.STANDARD : Rectangles.SINGLETON)
                   );
        // as the objects are pointers,
        // when a singleton will be changed,
        // then all other will also be changed
        // except we make them immutable
        Rectangles.set_width(myrec[i], (31 * i) % 69)
        ->set_height(myrec[i], (51 * i) % 155 );
        if(i == 975)
        {
            myrec[i]->immute(myrec[i]);
            UID = myrec[i]->get_uid(myrec[i]);
        }
    }

    pthread_t thread_lh;
    pthread_t thread_rh;

    if(pthread_create(&thread_lh, NULL, partial_qsort, myrec))
    {
        fprintf(stderr, "Error creating thread lh\n");
        return 1;
    }

    if(pthread_create(&thread_rh, NULL, partial_qsort, myrec + 500))
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

    // qsort( myrec, 500, sizeof(Rectangle *), Rectangles.compare_area );
    // qsort( myrec + 500, 500, sizeof(Rectangle *), Rectangles.compare_area );

    Rectangle *sorted_rec[1000];

    merge_sorted(myrec, sorted_rec);

    for(int i = 0; i < 1000; i++)
    {
        printf("%d x %d = %d (%d)\n", Rectangles.get_width(sorted_rec[i]),
               Rectangles.get_height(sorted_rec[i]),
               Rectangles.get_area(sorted_rec[i]), Rectangles.get_uid(sorted_rec[i]));
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


    Rectangles.cleanup();

    return 0;
}

void merge_sorted(Rectangle *myrec[], Rectangle *sorted_rec[])
{
    Rectangle **rec_lh, **rec_rh, **rec_lh_end, **rec_rh_end, **sorted_rec_walk;

    rec_lh = myrec;
    rec_lh_end = myrec + 499;
    rec_rh = myrec + 500;
    rec_rh_end = myrec + 999;
    sorted_rec_walk = sorted_rec;

    while(rec_lh <= rec_lh_end && rec_rh <= rec_rh_end)
    {
        *sorted_rec_walk++ = Rectangles.get_area(*rec_lh) < Rectangles.get_area(*rec_rh) ?
                             *rec_lh++ : *rec_rh++;
    }

    while(rec_lh <= rec_lh_end)
    {
        *sorted_rec_walk++ = *rec_lh++;
    }

    while(rec_rh <= rec_rh_end)
    {
        *sorted_rec_walk++ = *rec_rh++;
    }

    return;
}

void *partial_qsort(void *myrec)
{
    qsort( myrec, 500, sizeof(Rectangle *), Rectangles.compare_area );
    return NULL;
}
