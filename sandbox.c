#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "ClassRectangle.h"




int main(int argc, char const *argv[])
{
    Rectangle *myrec[100];
    int UID;

    for(int i = 0; i < 100; i++)
    {
        //the last 25 elements are the same,
        // due to an optional singleton featureof the factory
        myrec[i] = Rectangles.get_rectangle(
                       (i < 75 ? Rectangles.STANDARD : Rectangles.SINGLETON)
                   );
        // as the objects are pointers,
        // when a singleton will be changed,
        // then all other will also be changed
        // except we make them immutable
        Rectangles.set_width(myrec[i], (31 * i) % 69)
        ->set_height(myrec[i], (51 * i) % 155 );
        if(i == 75)
        {
            myrec[i]->immute(myrec[i]);
            UID = myrec[i]->get_uid(myrec[i]);
        }
    }

    qsort( myrec, 50, sizeof(Rectangle *), Rectangles.compare_area );
    qsort( myrec + 50, 50, sizeof(Rectangle *), Rectangles.compare_area );

    Rectangle *sorted_rec[100];

    Rectangle **rec_lh, **rec_rh, **rec_lh_end, **rec_rh_end, **sorted_rec_walk;

    rec_lh = myrec;
    rec_lh_end = myrec + 49;
    rec_rh = myrec + 50;
    rec_rh_end = myrec + 99;
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


    for(int i = 0; i < 100; i++)
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
