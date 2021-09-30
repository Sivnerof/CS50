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
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

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
    // Declare swap variables, and position setter, and find center
    int swapRed, swapGreen, swapBlue, center, position;

    for (int i = 0; i < height; i++)
    {
        // i, j match evenly to their respective partners
        if (width % 2 == 0)
        {
            // Set position to last pixel
            position = width - 1;

            // Set center for even pixels
            center = width / 2;

            // Loop until halfway
            for (int j = 0; j < center; j++)
            {
                // Containers for swap
                swapRed = image[i][position].rgbtRed;
                swapGreen = image[i][position].rgbtGreen;
                swapBlue = image[i][position].rgbtBlue;

                // Start pixels pushed to end
                image[i][position].rgbtRed = image[i][j].rgbtRed;
                image[i][position].rgbtGreen = image[i][j].rgbtGreen;
                image[i][position].rgbtBlue = image[i][j].rgbtBlue;

                // Container dump into start
                image[i][j].rgbtRed = swapRed;
                image[i][j].rgbtGreen = swapGreen;
                image[i][j].rgbtBlue = swapBlue;

                // Next position up
                position--;
            }
        }

        else
        {

            // Same as above
            position = width - 1;

            // Except this time we refocus center for odd pixel count in row
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
    // Empty struct to be populated with blurred pixels
    RGBTRIPLE blurredImage[height][width];

    // Sums of RGB values in a pixel
    float sumRed, sumGreen, sumBlue;

    // Count to keep track of times to divide sums by
    int count;

    // Loop through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset sums and count
            count = 0;
            sumRed = sumGreen = sumBlue = 0;

            // Loop through surrounding pixels on x
            for (int x = -1; x < 2; x++)
            {
                // Loop through surrounding pixels on y
                for (int y = -1; y < 2; y++)
                {
                    // Set positions
                    int xPosition = i + x;
                    int yPosition = j + y;

                    // Exclude and move to next position
                    if (xPosition < 0 || xPosition > (height - 1) || yPosition < 0 || yPosition > (width - 1))
                    {
                        continue;
                    }

                    // Add up sums of individual RGB values
                    sumRed += image[xPosition][yPosition].rgbtRed;
                    sumGreen += image[xPosition][yPosition].rgbtGreen;
                    sumBlue += image[xPosition][yPosition].rgbtBlue;

                    // Track of times needed to divide by
                    count++;
                }

                // Drop values into dummy struct pixel location
                blurredImage[i][j].rgbtRed = round(sumRed / count);
                blurredImage[i][j].rgbtGreen = round(sumGreen / count);
                blurredImage[i][j].rgbtBlue = round(sumBlue / count);
            }
        }
    }

    // Blurred pixels looped into originals positions
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurredImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurredImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurredImage[i][j].rgbtBlue;
        }
    }
    return;
}
