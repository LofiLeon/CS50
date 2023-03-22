#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get the average of all rgb values
            int sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int average = round(sum / 3.0);

            // assign the average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia

// Give min between value and 255
int max255(int i)
{
    if (i > 255)
    {
        return 255;
    }
    else
    {
        return i;
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int newRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int newGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int newBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            image[i][j].rgbtRed = max255(newRed);
            image[i][j].rgbtBlue = max255(newBlue);
            image[i][j].rgbtGreen = max255(newGreen);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create empty copy of image of same size
    RGBTRIPLE tmpi[height][width];

    // copy image into copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmpi[i][j] = image[i][j];
        }
    }

    // copy copy reversed into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmpi[i][width - j - 1];
        }
    }

    return;
}

int inGrid(int i, int lenght)
{
    if (i < lenght)
    {
        return 0;
    }
    else if (i > lenght)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create empty copy of image of same size
    RGBTRIPLE tmpi[height][width];

    // copy image into copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmpi[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get the sum of 3x3 grid around pixel [i][j]
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float count = 0.0;

            for (int k = i - 1; k <= (i + 1); k++)
            {
                for (int l = j - 1; l <= (j + 1); l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        sumRed += tmpi[k][l].rgbtRed;
                        sumGreen += tmpi[k][l].rgbtGreen;
                        sumBlue += tmpi[k][l].rgbtBlue;
                        count++;
                    }
                }
            }

            // get the averages
            if (count > 0)
            {
                int averageRed = round(sumRed / count);
                int averageGreen = round(sumGreen / count);
                int averageBlue = round(sumBlue / count);

                // assign the averages
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }

        }
    }
    return;
}
