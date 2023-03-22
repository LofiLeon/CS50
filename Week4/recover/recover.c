#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // make sure user gives exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./recover [file to recover from]\n");
        return 1;
    }

    // open input file from user argument
    FILE *inFile = fopen(argv[1], "r");
    if (inFile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // create array of 512 bytes to store exactly one block from file
    BYTE buffer[512];

    FILE *outFile = NULL;
    int jpegCount = 0;
    char filename[8] = {0};

    //read until end
    while (fread(buffer, sizeof(BYTE) * 512, 1, inFile) == 1)
    {
        // check if new vlock is a new jpeg image with correct headers
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // close old outFile
            if (outFile != NULL)
            {
                fclose(outFile);
            }

            // create new file with filename ###.jpg
            sprintf(filename, "%03d.jpg", jpegCount++);

            // open new outFile
            outFile = fopen(filename, "w");
        }

        // write to outFile in blocks
        if (outFile != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outFile);
        }
    }

    if (outFile != NULL)
    {
        fclose(outFile);
    }

    fclose(inFile);

    return 0;

}