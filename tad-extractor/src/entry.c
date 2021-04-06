#include "tadfile.h"

#ifdef PLATFORM_WIN32
	#include <direct.h>
    #define PATH_SEP "\\"
#else
	#include <sys/stat.h>
    #define PATH_SEP "/"
    #define mkdir(a) mkdir(a, 0777);
#endif

void help(void) {
    fprintf(stdout, "Usage: tadextractor.exe {tadfile} {directory}\n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        help();
        return -1;
    }

	char outputdir[255];
    sprintf(outputdir, ".%s%s%s", PATH_SEP, argv[2], PATH_SEP);
	int check = mkdir(outputdir);

    tadfile_t tadfile = open_tad_file(argv[1]);
    extract_tad_file(&tadfile, outputdir);
    close_tad_file(&tadfile);

    // create_tad_file("custom.tad", outputdir, 61);
    return 0;
}