#include <stdio.h>
#include <string.h>
#include "id3v2.h"

/* Convert sync-safe integer to normal integer */
int get_tag_size(unsigned char size[4])
{
    return (size[0] << 21) |
           (size[1] << 14) |
           (size[2] << 7)  |
           (size[3]);
}

void read_frame(FILE *fp, char frame_id[5], int frame_size)
{
    char text_encoding;
    char data[1024];

    fread(&text_encoding, 1, 1, fp);   // Encoding byte
    fread(data, 1, frame_size - 1, fp);
    data[frame_size - 1] = '\0';

    printf("%s : %s\n", frame_id, data);
}

void read_id3v2_tags(FILE *fp)
{
    ID3Header header;
    char frame_id[5];
    int frame_size;
    char flags[2];
    int tag_size;

    fread(&header, sizeof(ID3Header), 1, fp);

    if (strncmp(header.id, "ID3", 3) != 0)
    {
        printf("No ID3v2 tag found\n");
        return;
    }

    printf("\nID3 Version: 2.%d.%d\n",
           header.version, header.revision);

    tag_size = get_tag_size(header.size);

    printf("Tag Size  : %d bytes\n\n", tag_size);

    while (ftell(fp) < tag_size)
    {
        fread(frame_id, 1, 4, fp);
        frame_id[4] = '\0';

        if (frame_id[0] == '\0')
            break;

        fread(&frame_size, 4, 1, fp);
        frame_size = __builtin_bswap32(frame_size); // big endian

        fread(flags, 1, 2, fp);

        if (strcmp(frame_id, "TIT2") == 0 ||
            strcmp(frame_id, "TPE1") == 0 ||
            strcmp(frame_id, "TALB") == 0 ||
            strcmp(frame_id, "TYER") == 0 ||
            strcmp(frame_id, "TDRC") == 0)
        {
            read_frame(fp, frame_id, frame_size);
        }
        else
        {
            fseek(fp, frame_size, SEEK_CUR);
        }
    }
}
