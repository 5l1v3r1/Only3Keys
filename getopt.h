#ifndef O3K_GETOPT_H
#define O3K_GETOPT_H

#include <stdio.h> // printf()
#include <unistd.h> // getopt()
#include <stdlib.h> // exit()

// these seem to be unneeded?
// but I think its getopt() related.
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char *pipename;

int getCommandLineOptions(int argc, char **argv);

#endif
