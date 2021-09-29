#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int averageGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = averageGray;
            image[i][j].rgbtRed = averageGray;
            image[i][j].rgbtGreen = averageGray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Algorithm for Sepia requires operations on original values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // If result is more than 8 bits worth of color cap at 255
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaRed > 255)
                sepiaRed = 255;

            // Change pixel color values to Sepia
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int swapRed, swapGreen, swapBlue, center;
    int position;
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            position = width - 1;
            center = width / 2;
            for (int j = 0; j < center; j++)
            {
                swapRed = image[i][position].rgbtRed;
                swapGreen = image[i][position].rgbtGreen;
                swapBlue = image[i][position].rgbtBlue;
                image[i][position].rgbtRed = image[i][j].rgbtRed;
                image[i][position].rgbtGreen = image[i][j].rgbtGreen;
                image[i][position].rgbtBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = swapRed;
                image[i][j].rgbtGreen = swapGreen;
                image[i][j].rgbtBlue = swapBlue;
                position--;
            }
        }

        else
        {
            position = width - 1;
            center = ceil(width / 2);
            for (int j = 0; j <= center; j++)
            {
                swapRed = image[i][position].rgbtRed;
                swapGreen = image[i][position].rgbtGreen;
                swapBlue = image[i][position].rgbtBlue;
                image[i][position].rgbtRed = image[i][j].rgbtRed;
                image[i][position].rgbtGreen = image[i][j].rgbtGreen;
                image[i][position].rgbtBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = swapRed;
                image[i][j].rgbtGreen = swapGreen;
                image[i][j].rgbtBlue = swapBlue;
                position--;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
