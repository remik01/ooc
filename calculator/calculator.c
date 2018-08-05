#include <stdio.h>
#include <stdlib.h>

const unsigned int DISPLAY_SIZE = 20;

char display[20];
long long buffer = 0;

void show_display(void);
void clear_display(void);
void handle(char c);
long long display_to_number(void);
void buffer_to_display(void);

int main ()
{
    FILE *fp;
    int c;

    system("stty raw");
    fp = stdin;

    if(fp == NULL)
    {
        perror("Error in opening file");
        return(-1);
    }

    clear_display();
    show_display();

    do
    {
        c = fgetc(fp);
        if( feof(fp) )
        {
            break;
        }
        handle(c);
    }
    while(c != 'q');

    system("stty sane");

    printf("\n%lld\n", buffer);

    fclose(fp);
    return(0);
}


void show_display(void)
{
    printf("\r");
    for(int i = 0; i < DISPLAY_SIZE; i++)
    {
        printf("%c", display[i]);
    }

};

void clear_display(void)
{
    for(int i = 0; i < DISPLAY_SIZE; i++)
    {
        display[i] = ' ';
    }
};

void handle(char c)
{
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':

        for(int i = 0; i < DISPLAY_SIZE - 1; i++)
        {
            display[i] = display[i + 1];
        }
        display[DISPLAY_SIZE - 1] = c;
        show_display();

        break;

    case '+':

        buffer += display_to_number();
        clear_display();

        break;
    case '=':

        buffer_to_display();

        break;
    default:
        show_display();
        break;

    }
};

long long display_to_number(void)
{
    long long ret = 0;
    long long multi = 1;
    for(int i = DISPLAY_SIZE - 1; i >= 0 ; i--, multi *= 10)
    {
        if( display[i] < '0' || display[i] > '9') continue;
        ret += multi * (display[i] - '0');
    }

    return ret;
};

void buffer_to_display(void)
{
    long long buff = buffer;
    for(int i = DISPLAY_SIZE - 1; i >= 0 ; i--)
    {
        display[i] = buff % 10 + '0';
        buff /= 10;
    }

    // clear the leading zeros
    for(int i = 0; i < DISPLAY_SIZE - 1; i++)
    {
        if(display[i] == '0')
            display[i] = ' ';
        else
            break;
    }

    show_display();
};




















