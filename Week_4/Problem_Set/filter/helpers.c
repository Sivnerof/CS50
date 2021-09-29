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
    int swapRed, swapGreen, swapBlue, position, center;
    for (int i = 0; i < height; i++)
    {
        position = width - 1;
        if (width % 2 == 0)
        {
            center = width / 2;
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

        else
        {
            center = ceil(width / 2);
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
    }
    return;
}
    /*
                         A  B  C    D  E  F
                        [0][1][2]  [3][4][5]

                A  [0]  [?][?][?]  [?][?][?]
                B  [1]  [?][?][?]  [?][?][?]
                C  [2]  [?][?][?]  [?][?][?]
                D  [3]  [?][?][?]  [?][?][?]
                E  [4]  [?][?][?]  [?][?][?]
                F  [5]  [?][?][?]  [?][?][?]

                         A  B  C    D    E  F  G
                        [0][1][2]  [3]  [4][5][6]

                A  [0]  [?][?][?]  [?]  [?][?][?]
                B  [1]  [?][?][?]  [?]  [?][?][?]
                C  [2]  [?][?][?]  [?]  [?][?][?]
                D  [3]  [?][?][?]  [?]  [?][?][?]
                E  [4]  [?][?][?]  [?]  [?][?][?]
                F  [5]  [?][?][?]  [?]  [?][?][?]
*/
    //Reflection
    //Note that all of the original pixels of the original image will still be present in the reflected image,
    //it’s just that those pixels may have rearranged to be in a different place in the image.
    //width - 1?

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
