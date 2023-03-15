#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int s;
    do
    {
        s = get_int("Start: ");
    }
    while (s < 9);


    // TODO: Prompt for end size
    int e;
    do
    {
        e = get_int("End: ");
    }
    while (e < 9 || e < s);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    while (s < e)
    {
        int b = s / 3;
        int d = s / 4;
        s += b;
        s -= d;
        n++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", n);
}
