#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

uint8_t byte[BLOCK_SIZE];

char fileName[4];
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

    FILE *outputImage = NULL;

    int count = 0;
    while (fread(byte, sizeof(uint8_t), BLOCK_SIZE, forensicImage))
    {
        if (byte[0] == 0xff && byte[1] == 0xd8 && byte[2] == 0xff && (byte[3] & 0xf0) == 0xe0)
        {
                sprintf(fileName, "%03i.jpg", count);
                outputImage = fopen(fileName, "w");
                count++;

            if (outputImage != NULL)
            {
                fwrite(byte, sizeof(uint8_t), BLOCK_SIZE, outputImage);
            }
        }
    }

// Close open files
fclose(forensicImage);
fclose(outputImage);
return 0;

}
