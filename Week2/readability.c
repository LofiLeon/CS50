#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // get text from user
    string text = get_string("Text: ");

    int letters = count_letters(text);
    //printf("Letters: %i\n", letters);
    int words = count_words(text);
    //printf("Words: %i\n", words);
    int sentences = count_sentences(text);
    //printf("Sentences: %i\n", sentences);

    // average no of letters per 100 words
    float averageLetters = letters * 100.0 / words;
    //printf("Average: %f\n", averageLetters);

    // average number of sentences per 100 words
    float averageSentences = sentences * 100.0 / words;
    //printf("Average: %f\n", averageSentences);

    // calculate index
    int index = round(0.0588 * averageLetters - 0.296 * averageSentences - 15.8);

    // print grade "Grade 16+" & "Before Grade 1".
    //printf("Index: %i\n", index);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// count letters a-z & A-Z
int count_letters(string text)
{
    int i = 0;
    int count = 0;

    while (text[i])
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            count++;
        }
        i++;
    }
    return (count);
}

// count words everything seperated with ' '
int count_words(string text)
{
    int i = 0;
    int count = 1;

    while (text[i])
    {
        if (text[i] == ' ')
        {
            count++;
        }
        i++;
    }
    return (count);
}

// count sentences everything ending with . ? or !
int count_sentences(string text)
{
    int i = 0;
    int count = 0;

    while (text[i])
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
        i++;
    }
    return (count);
}