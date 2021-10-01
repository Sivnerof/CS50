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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sobelImage[height][width];

    // 3x3 Sobel Grids

    // Gx
    int sobelX[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // Gy
    int sobelY[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Loop through pixels
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            // Set RGB variables
            float gxRed, gxBlue, gxGreen, gyRed, gyBlue, gyGreen;
            gxRed = gxBlue = gxGreen = gyRed = gyBlue = gyGreen = 0;

            // Outer loop checks values around position in y axis
            for (int k = -1; k < 2; k++)
            {
                // Inner loop does same along x axis
                for (int l = -1; l < 2; l++)
                {

                    // Exclude corner and edge pixels from algorithm
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    // Run Sobel Grid along x axis
                    gxRed += image[i + k][j + l].rgbtRed * sobelX[k + 1][l + 1];
                    gxGreen += image[i + k][j + l].rgbtGreen * sobelX[k + 1][l + 1];
                    gxBlue += image[i + k][j + l].rgbtBlue * sobelX[k + 1][l + 1];

                    // Run Sobel Grid along y axis
                    gyRed += image[i + k][j + l].rgbtRed * sobelY[k + 1][l + 1];
                    gyGreen += image[i + k][j + l].rgbtGreen * sobelY[k + 1][l + 1];
                    gyBlue += image[i + k][j + l].rgbtBlue * sobelY[k + 1][l + 1];
                }
            }

            int redPixel, greenPixel, bluePixel;

            // Apply second part of Sobel algorithm

            // Gx^2 + Gy^2 to fit both results of Sobel Grids into one pixel
            redPixel = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            greenPixel = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            bluePixel = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // If results are greater than 255 max channel rgb value, set cap to 255
            sobelImage[i][j].rgbtRed = redPixel > 255 ? 255 : redPixel;
            sobelImage[i][j].rgbtGreen = greenPixel > 255 ? 255 : greenPixel;
            sobelImage[i][j].rgbtBlue = bluePixel > 255 ? 255 : bluePixel;
        }
    }

    // Transfer pixels to image brought in
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = sobelImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = sobelImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = sobelImage[i][j].rgbtBlue;
        }
    }
}