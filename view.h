#include <stdio.h>
#include <string.h>
#include "view.h"

void view_mp3_tags(FILE *fp)
{
    ID3v1 tag;

    // Move file pointer to last 128 bytes
    fseek(fp, -128, SEEK_END);

    fread(&tag, sizeof(ID3v1), 1, fp);

    // Check TAG identifier
    if (strncmp(tag.tag, "TAG", 3) != 0)
    {
        printf("No ID3v1 tag found\n");
        return;
    }

    printf("\n------ MP3 TAG DETAILS ------\n");
    printf("Title   : %.30s\n", tag.title);
    printf("Artist  : %.30s\n", tag.artist);
    printf("Album   : %.30s\n", tag.album);
    printf("Year    : %.4s\n", tag.year);
    printf("Comment : %.30s\n", tag.comment);
    printf("Genre   : %d\n", tag.genre);
}
