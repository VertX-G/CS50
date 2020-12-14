#include "helpers.h"
#include <math.h>
#include <stdio.h>

// cap an integer between a min and max number
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
            // get RGB values
            float red = image[j][i].rgbtRed;
            float green = image[j][i].rgbtGreen;
            float blue = image[j][i].rgbtBlue;
            
            // calculate the average for the red, green, blue properties of each pixel
            float avg = round((red + green + blue) / 3);

            // assign the average back to each of those properties
            image[j][i].rgbtRed = round(avg);
            image[j][i].rgbtGreen = round(avg);
            image[j][i].rgbtBlue = round(avg);
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
            // get rgb values
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
    // COPY IMAGE
    // Create placeholder of type 'image'
    RGBTRIPLE temp_copy[height][width];
    // iterate through columns
    for (int i = 0; i < width; i++)
    {
        // iterate through rows
        for (int j = 0; j < height; j++)
        {
            // copy pixel rgb from original image
            temp_copy[j][i].rgbtRed = image[j][i].rgbtRed;
            temp_copy[j][i].rgbtGreen = image[j][i].rgbtGreen;
            temp_copy[j][i].rgbtBlue = image[j][i].rgbtBlue;
        }
    }

    // Calculate new value of each pixel based on values of surrounding pixels

    // Iterate through columns
    for (int i = 0; i < width; i++)
    {
        // Iterate through rows
        for (int j = 0; j < height; j++)
        {
            // Declare variables
            int counter = 0;
            float total_red = 0;
            float total_green = 0;
            float total_blue = 0;
            int blur_level = 1;
            
            // iterate through surrounding pixel columns
            for (int k = (i - blur_level); k <= (i + blur_level); k++)
            {
                // check position is not out of bounds
                if (k >= 0 && k < width)
                {
                    // iterate through surrounding pixel columns
                    for (int l = (j - blur_level); l <= (j + blur_level); l++)
                    {
                        // check position is not out of bounds
                        if (l >= 0 && l < height)
                        {
                            // total rgb values for average calculations
                            total_red += temp_copy[l][k].rgbtRed;
                            total_green += temp_copy[l][k].rgbtGreen;
                            total_blue += temp_copy[l][k].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }
            
            // set new rgb values of pixel
            image[j][i].rgbtRed = round(total_red / counter);
            image[j][i].rgbtGreen = round(total_green / counter);
            image[j][i].rgbtBlue = round(total_blue / counter); 
        }
    }

    return;
}
