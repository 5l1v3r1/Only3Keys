#include "getopt.h"

char *pipename = "/tmp/only3keys";

int getCommandLineOptions(int argc, char **argv) {
    int flags = 0; // 0x10 - colormode, 0x01 - ascii chart
    int c;

    // parse options and fail early if invalid options
    while ((c = getopt (argc, argv, "acp:")) != -1)
        switch (c) {

            // show ascii_chart (default: NO)
            case 'a':
                flags |= 0x01;
                break;

            // use colors (default: NO)
            case 'c':
                flags |= 0x10;
                break;

            // change name of pipe (default: /tmp/only3keys)
            case 'p':
                pipename = optarg;
                break;

            // unknown options. failure.
            default:
                printf("Exiting!\n");
                exit(EXIT_FAILURE);
        }
    return flags;
}

// printf ("flags = 0x%x, cvalue = %s\n", flags, pipename);
//
// for(int index = optind; index < argc; index++)
//   printf ("Non-option argument %s\n", argv[index]);
