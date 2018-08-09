#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv[])
{
    int count = 0;
    int open = 0;
    char filenames[7];
    FILE *img = NULL;


    if (argc != 2)              // if command-line argument is not 2 then prompt an error.
    {
        fprintf(stderr, "Usage: ./recover.c raw_file\n");
        return 1;
    }
    char *file = argv[1];       // file pointer to command-line argument

    FILE *raw_file = fopen(file, "r");      //raw_file pointer to open file

    if (raw_file == NULL)           //checking if file is not open
    {
        fprintf(stderr, "Could not open %s\n", file);
        return 2;
    }

    unsigned char buffer[512];

    while (fread(buffer, sizeof(buffer), 1, raw_file))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(open>0)
            {
                fclose(img);
            }
            sprintf(filenames, "%03i.jpg", count);
            img = fopen(filenames, "w");


            count++;
        }
        if (count == 0) continue;
        fwrite(buffer, 512, 1, img);
    }

    fclose(img);
    fclose(raw_file);       // close the file
    return 0; // success.
}
