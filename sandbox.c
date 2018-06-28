#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassRectangle.h"


int main(int argc, char const *argv[])
{
    Rectangle *myrec = malloc(sizeof(Rectangle));

    Library.set_width(myrec, 5);
    Library.set_height(myrec, 21);

    printf("area: %d\n", Library.get_area(myrec));

    free(myrec);

    return 0;
}
