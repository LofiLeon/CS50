#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

char    to_upper(char c)
{
    if (islower(c))
    {
        c = c - 32;
    }
    return (c);
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    int i = 0;

    while (word[i])
    {
        // only if lower ir upper
        if (islower(word[i]) || isupper(word[i]))
        {
            //make the character uppercase
            char c = to_upper(word[i]);
            // get the value of the character
            int value = POINTS[c - 65];
            // add value to score
            score += value;
        }
        i++;
    }
    return (score);
}

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}


