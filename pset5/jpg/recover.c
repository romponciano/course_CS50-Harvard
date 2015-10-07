// Recover Pset 5
// CS50x - 2014 - HarvardX
// Rômulo Ponciano - romulo_37@hotmail.com

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
typedef uint8_t BYTE;
#define BLOCKSIZE 512
 
int main(int argc, char *argv[]) 
{
    char forensic[1024] = {'\0'};
    if (argc == 2)
    {
        if (strlen(argv[1]) > 1024)
        {
            printf("/path.to/filename over 1024 bytes.\n");
            return 2;
        }
        snprintf(forensic, 1024, "%s", argv[1]);
    }
    else
    {
        sprintf(forensic, "/home/cs50/pub/share/pset5/card.raw");
    }
 
    // open card image
    FILE *fp;
    if ((fp = fopen(forensic, "r")) == NULL)
    {
        return 0;
    }
 
    FILE *outfile;
    outfile = NULL;
    int jpgnum = 0;
    int discarded = 0;
    int stored = 0;
    int total = 0;
    while (1)
    {
        total++;
        //the read buffer for the blocks
        BYTE block[BLOCKSIZE] = {};
        for (int c = 0; c < BLOCKSIZE; c++)
        {
            if (feof(fp))
            {
                total--;
                //reached the end of file
                fclose(fp);
                if (outfile != NULL)
                    fclose(outfile);
                printf("discarded %d blocks, stored %d blocks from %d total\n", discarded, stored, total);
                //printf("at end of read the cursor was at: c=%d\n", c);
                return (EXIT_SUCCESS);
            }
            //read one byte
            fread(&block[c], sizeof (BYTE), 1, fp);
        }
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            //this is a the start of a new jpeg
            // close previously opened out file ptr
            if (outfile != NULL)
            {
                fclose(outfile);
            }
            //make a new filename for each jpg found.
            jpgnum++; //we never write 000.jpg
            char filename[10];
            sprintf(filename, "%04d.jpg", jpgnum);
 
            //open the outfile pointer
            if ((outfile = fopen(filename, "w")) == NULL)
            {
                printf("Could not write jpg image.\n");
                return 2;
            }
 
            //write the block
            fwrite(&block[0], BLOCKSIZE * sizeof (BYTE), 1, outfile);
            stored++;
        }
        else if (jpgnum && outfile != NULL) // I have already started finding jpegs, and I have an active outfile pointer
        {
            //continue writing stuff into the outfile
            //write the block
            fwrite(&block[0], BLOCKSIZE * sizeof (BYTE), 1, outfile);
            stored++;
        }
        else
        {
            discarded++; // counts discarded blocks
        }
    }
 
    // close forensic image
    fclose(fp);
 
    // that's all folks
    return (EXIT_SUCCESS);
}
