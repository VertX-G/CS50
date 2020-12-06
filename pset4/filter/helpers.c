#include "helpers.h"
#include <math.h>
#include <stdio.h>

// cap an integer between a min and max
int capInt(int num, int min, int max)
{
    if (num < min)
    {
        return min;
    }
    else if (num > max)
    {
        return max;
    }
    else
    {
        return num;
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through columns
    for (int i = 0; i < width; i++)
    {
        // iterate through rows
        for (int j = 0; j < height; j++)
        {
            float red = image[j][i].rgbtRed;
            float green = image[j][i].rgbtGreen;
            float blue = image[j][i].rgbtBlue;
            // calculate the average for the red, green, blue properties of each pixel
            float avg = round((red + green + blue) / 3);

            // assign the average back to each of those properties
            image[j][i].rgbtRed = (int)avg;
            image[j][i].rgbtGreen = (int)avg;
            image[j][i].rgbtBlue = (int)avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through columns
    for (int i = 0; i < width; i++)
    {
        // iterate through rows
        for (int j = 0; j < height; j++)
        {
            // get the value for r, g, b for each pixel
            float originalRed = image[j][i].rgbtRed;
            float originalGreen = image[j][i].rgbtGreen;
            float originalBlue = image[j][i].rgbtBlue;

            // run algorithm to calculate the new values for the sepia version
            float sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            float sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            float sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // set pixel to that new value, but capped between 0 and 255
            image[j][i].rgbtRed = capInt(sepiaRed, 0, 255);
            image[j][i].rgbtGreen = capInt(sepiaGreen, 0, 255);
            image[j][i].rgbtBlue = capInt(sepiaBlue, 0, 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create placeholder pixel for swop function
    RGBTRIPLE tmp;

    // iterate through columns of half of image to swop with other half
    for (int i = 0; i < width / 2; i++)
    {
        // iterate through rows of image
        for (int j = 0; j < height; j++)
        {
            // swop pixel of left half with pixel of right half using placeholder pixel
            tmp = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - 1 - i] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image
    // Iterate through each pixel of the original image
    // For each pixel, calculate its new RGBTRIPLE values based on the values of the values of the copied image
    // when complete, delete the copied image
    return;
}
