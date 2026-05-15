#include <stdio.h>
#include "id3v2.h"

int main()
{
    FILE *fp;
    char filename[100];

    printf("Enter MP3 file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    read_id3v2_tags(fp);

    fclose(fp);
    return 0;
}
