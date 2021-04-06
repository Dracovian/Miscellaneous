#ifndef __TADEXTRACTOR_TADFILE_H
#define __TADEXTRACTOR_TADFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long numfiles;     /* The number of files in the TAD file. */
    long *filesize;    /* The sizes of each file in the TAD file in bytes. */
} tadfile_header_t;

typedef struct {
    tadfile_header_t *header;

    FILE *tadfile; /* The file stream for the TAD file. */
    long filesize; /* The filesize of the TAD file in bytes. */
} tadfile_t;

tadfile_t open_tad_file(const char *); /* Open a TAD file accessing its contents. */
void close_tad_file(tadfile_t *);      /* Close a TAD file to free up used memory. */

void extract_tad_file(tadfile_t *, const char *); /* Extract files from an opened TAD file. */
void create_tad_file(const char *, char *, long); /* Create a TAD file from a folder of files. */

#endif