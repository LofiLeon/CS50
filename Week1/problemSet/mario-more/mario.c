#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get height
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h > 8 || h < 1);
    int i = 0;

    // print blocks in a loop
    while (i < h)
    {
        int whiteSpaces = h - i - 1;
        int blocks = h - whiteSpaces;
        int j = 0;

        // print first white spaces
        while (j < whiteSpaces)
        {
            printf(" ");
            j++;
        }
        j = 0;

        // print first blocks
        while (j < blocks)
        {
            printf("#");
            j++;
        }
        j = 0;

        // print gap
        printf(" ");
        printf(" ");

        // print second blocks
        while (j < blocks)
        {
            printf("#");
            j++;
        }
        j = 0;

        // orint new line
        printf("\n");
        i++;
    }
}