#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassRectangle.h"


int main(int argc, char const *argv[])
{
    Rectangle *myrec[10];

    for(int i = 0; i < 10; i++)
    {
        myrec[i] = Rectangles.get_rectangle();
        Rectangles.set_width(myrec[i], (31 * i) % 69)
        ->set_height(myrec[i], (51 * i) % 155 );
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d x %d = %d\n", myrec[i]->width, myrec[i]->height,
               Rectangles.get_area(myrec[i]));
    }

    Rectangles.cleanup();

    return 0;
}
