#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    char str[600];
    int cnt = 0;
    char chr;
    signed char control = -1;
    if( fgets (str, 600, stdin) != NULL )
    {
        /* writing content to stdout */
        puts(str);
        while ((chr = str[cnt++]))
        {
            control += chr;
        }
    }

    printf("%d\n", control);


    return 0;
}