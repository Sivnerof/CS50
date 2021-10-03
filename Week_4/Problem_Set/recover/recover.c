#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Handles attempts at inputing multiple files
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Opens forensic image and checks if empty
    FILE *forensicImage = fopen(argv[1], "r");

    if (forensicImage == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Initialize file pointer and set to null
    FILE *outputImage = NULL;

    // 3 bytes for 3 numbers in char array
    char fileName[3];

    // Keep lookout for how many times a header is found
    int count = 0;

    // Initialize array of 8bits total size 512
    uint8_t byte[BLOCK_SIZE];

    // Read until end of file
    while (fread(byte, sizeof(uint8_t), BLOCK_SIZE, forensicImage))
    {

        // Catch headers
        if (byte[0] == 0xff && byte[1] == 0xd8 && byte[2] == 0xff && (byte[3] & 0xf0) == 0xe0)
        {

            // If start of new jpeg close file
            if (outputImage != NULL)
            {
                fclose(outputImage);
            }

            // Print count loop iteration to file name
            sprintf(fileName, "%03i.jpg", count);

            // Open new image file and increment JPG count
            outputImage = fopen(fileName, "w");
            count++;
        }

        // Create JPG
        if (outputImage != NULL)
        {
            fwrite(byte, sizeof(uint8_t), BLOCK_SIZE, outputImage);
        }
    }

// Close open files
fclose(forensicImage);
fclose(outputImage);
return 0;
}
