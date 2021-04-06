#include "tadfile.h"

tadfile_t open_tad_file(const char *filename) {

    // Create the TAD file header which will be incorporated in our TAD file.
    tadfile_header_t *header = malloc(sizeof(tadfile_header_t));

    // Create the TAD file which will end up being returned.
    tadfile_t tadfile;
    tadfile.header = header;

    // Initialize the TAD file stream.
    tadfile.tadfile = fopen(filename, "rb");

    // Go to the end of the TAD file stream.
    fseek(tadfile.tadfile, 0, SEEK_END);

    // Get the file size of the TAD file.
    tadfile.filesize = ftell(tadfile.tadfile);

    // Return to the beginning of the file.
    fseek(tadfile.tadfile, 0, SEEK_SET);

    // Return the TAD file.
    return tadfile;
}

void close_tad_file(tadfile_t *file) {

    // NULL the TAD file header data to clear it from memory.
    free(file->header);
    file->header = 0;

    // Close the TAD file stream.
    fclose(file->tadfile);

    // Reset the TAD file size to 0.
    file->filesize = 0l;

    // NULL the TAD file and clear it from memory.
    file = 0;
}

void extract_tad_file(tadfile_t *file, const char *path) {
    
    /* ------------------------------------------ *
     *  Get the number of files in the TAD file.  *
     * ------------------------------------------ */

    long bit = 0l;
    char *files = malloc(sizeof(char) * 18);

    while (1) {
        char byte;
        fread(&byte, sizeof(char), 1, file->tadfile);

        if (byte == 0x20)
            break;

        *(files + bit) = byte;
        ++bit;
    }

    long numfiles = strtol(files, 0, 10);
    file->header->numfiles = numfiles;
    free(files);

    /* --------------------------------------------- *
     *  Get the sizes of each file in the TAD file.  *
     * --------------------------------------------- */

    fseek(file->tadfile, sizeof(char), SEEK_CUR);
    file->header->filesize = malloc(sizeof(long) * numfiles);

    for (long i = 0l; i < numfiles; ++i) {
        char *size = malloc(sizeof(char) * 18);
        long bit = 0l;

        while (1) {
            char byte;
            fread(&byte, sizeof(char), 1, file->tadfile);
            
            if (byte == 0x20)
                break;

            *(size + bit) = byte;
            ++bit;
        }

        *(file->header->filesize + i) = strtol(size, 0, 10);
        fseek(file->tadfile, sizeof(char), SEEK_CUR);
        free(size);
    }

    /* -------------------------------------------------------------- *
     *  Now we can begin the process of extracting from the TAD file. *
     * -------------------------------------------------------------- */
    
    for (long i = 0l; i < numfiles; ++i) {
        char *filename = malloc((strlen(path) * sizeof(char)) + (sizeof(char) * 8));
        sprintf(filename, "%s%04ld.png", path, i);

        long filesize = *(file->header->filesize + i);

        char *filedata = malloc(sizeof(char) * filesize);
        fread(filedata, sizeof(char), filesize, file->tadfile);

        FILE *fp = fopen(filename, "wb");
        fwrite(filedata, sizeof(char), filesize, fp);

        free(filedata);
        free(filename);
    }
}

/*
void create_tad_file(const char *filename, char *path, long numfiles) {
    FILE *tadfile = fopen(filename, "wb");
    
    // Start off the TAD file with the number of files going into it.
    char *initdata = malloc(sizeof(char) * 20);
    sprintf(initdata, "%ld%c%c", numfiles, 0x20, 0x71);

    fwrite(initdata, sizeof(char), strlen(initdata), tadfile);
    free(initdata);

    /* ------------------------------------------------------- *
     *  Gather the sizes for the files going in the TAD file.  *
     * ------------------------------------------------------- *

    for (long i = 0l; i < numfiles; ++i) {
        char *filename = malloc((strlen(path) * sizeof(char)) + (sizeof(char) * 8));
        sprintf(filename, "%s%04ld.png", path, i);

        FILE *fp = fopen(filename, "rb");
        fseek(fp, 0, SEEK_END);

        long filesize = ftell(fp);
        fclose(fp);
        fp = 0;

        char *sizedata = malloc(sizeof(char) * 20);
        sprintf(sizedata, "%ld%c%c", filesize, 0x20, 0x71);
        fwrite(sizedata, sizeof(char), strlen(sizedata), tadfile);

        free(sizedata);
        free(filename);
    }

    /* ------------------------------------------------------------ *
     *  Append the file data of each file going into the TAD file.  *
     * ------------------------------------------------------------ *

    for (long i = 0l; i < numfiles; ++i) {
        char *filename = malloc((strlen(path) * sizeof(char)) + (sizeof(char) * 8));
        sprintf(filename, "%s%04ld.png", path, i);

        FILE *fp = fopen(filename, "rb");
        fseek(fp, 0, SEEK_END);

        long filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char *filedata = malloc(sizeof(char) * filesize);
        fread(filedata, sizeof(char), filesize, fp);

        fclose(fp);
        free(filename);

        fwrite(filedata, sizeof(char), filesize, tadfile);
    }

    fclose(tadfile);
}
*/