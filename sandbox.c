#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassRectangle.h"


int main(int argc, char const *argv[])
{
    Rectangle *myrec = malloc(sizeof(Rectangle));

    set_width(myrec, 2);
    set_height(myrec, 11);

    printf("area: %d\n", get_area(myrec));

    free(myrec);

    return 0;
}