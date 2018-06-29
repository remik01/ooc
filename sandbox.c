#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassRectangle.h"


int main(int argc, char const *argv[])
{
    Rectangle *myrec = get_rectangle();

    myrec->set_width(myrec, 17)->set_height(myrec, 21);

    printf("area: %d\n", myrec->get_area(myrec));

    free(myrec);
    myrec = NULL;

    return 0;
}
