#ifndef ID3V2_H
#define ID3V2_H

#include <stdio.h>

/* ID3v2 header (10 bytes) */
typedef struct
{
    char id[3];        // "ID3"
    char version;      // Version major
    char revision;     // Version revision
    char flags;
    unsigned char size[4]; // Sync-safe integer
} ID3Header;

/* Function prototype */
void read_id3v2_tags(FILE *fp);

#endif
