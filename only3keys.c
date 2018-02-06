/*  Only3Keys - a keyboard userspace driver. with only 3 keys.
AUTHOR: Skyler Curtis (deadPix3l)
DATE:  6 FEB 2018
WHY: just cause. for the lulz.
*/
#include <ncurses.h>
#include <stdio.h> // fprintf()
#include <stdlib.h> // exit()
#include <unistd.h> // getopt()

// these seem to be unneeded?
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "ascii2.h"

#define SHIFTBYTE(a) if (++(a) >= 8) (a) = 1;

//globals
char binary[] = "0b0000000";
uint8_t current_pos = 1;

void setBitOn(int* out, int bit) { (*out) = (*out) | 1 << (bit - 1); }
void setBitOff(int* out, int bit) { (*out) = (*out) & ~(1 << (bit - 1)); }
void incrementPos(uint8_t* x) { if (++(*x) >= 8) *x = 1; }

void binarystr(int out_char) {
    for(int i = 0; i < 7; i++)
        binary[2+i] = (out_char & (1 << (6-i))) ? '1' : '0';
}

void printCurrentCode(int y, int x, int out_char){
    mvprintw(y, x, "%s (0x%x) = %c", binary, out_char, out_char);
    mvprintw(y+1, x+2+(7-current_pos), "^");
    refresh();
}

int main(int argc, char** argv) {

  //ncurses vars
  WINDOW *stdscr;

  //application vars
  //FILE *fifo;
  int in_char = 0;
  int out_char = 0;
  // GNU getopt() vars
  //opterr = 0; //uncomment to silence getopt() errors
  int flags = 0; // 0x10 - colormode, 0x01 - ascii chart
  char *pipename = "/tmp/only3keys";
  int index;
  int c;

  // parse options and fail early if invalid options
  while ((c = getopt (argc, argv, "acp:")) != -1)
    switch (c) {
      case 'a':
        flags |= 0x01;
        break;

      case 'c':
        flags |= 0x10;
        break;

      case 'p':
        pipename = optarg;
        break;

      default:
        printf("Exiting!\n");
        exit(EXIT_FAILURE);
      }

  printf ("flags = 0x%x, cvalue = %s\n", flags, pipename);

  for(index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);

  //mkfifo(pipename, 0666);
  //fifo = fopen(pipename, "wb");

  //fclose(fifo);
  //exit(2);

  //basic ncurses setup
  if ((stdscr = initscr()) == NULL){
    fprintf(stderr, "ncurses Error!");
    exit(EXIT_FAILURE);
  }
  if (flags & 0x10 && !has_colors()){
    endwin();
    fprintf(stderr, "Error: No Color Support!\n");
    fprintf(stderr, "Turn off color option to continue.\n");
    exit(EXIT_FAILURE);
  }

  if (flags & 0x10)
    start_color();

  cbreak(); //single keypress at a time. no need for CR
  noecho();
  curs_set(FALSE);
  keypad(stdscr, true);

  while(true) {
    binarystr(out_char);

    // print the current keycode
    clear();
    printCurrentCode(0,0,out_char);


    //print the ascii legend
    for(int row = 0; row < (sizeof ascii_legend / sizeof ascii_legend[0]); row++) {
        mvaddstr(4+row, 10, ascii_legend[row]);
    }

    //print the ascii chart (with colors?)
    //TODO: magic numbers - get rid of them.
    for(int row = 0; row < 16; row++) {
            move(6+row, 10);
            for (int i = 0; i < 9; i++ ) {
                //if reachable { color = on };
                addstr(ascii_chart2[row][i]);
                addstr(" ");
                // color = off;
            }
    }

    refresh();

    // currently hard coding the keys, and providing several options
    // for each. maybe allow custom keys via config file?
    // OR: put into the README to change these as needed and compile
    switch(in_char = wgetch(stdscr)) {
        case 'q':
            goto end;
            break;

        // 1
        case '1':
        case KEY_LEFT:
            setBitOn(&out_char, current_pos);
            incrementPos(&current_pos);
            break;

        // 0
        case '0':
        case KEY_RIGHT:
            setBitOff(&out_char, current_pos);
            incrementPos(&current_pos);
            break;

        // ENTER
        case KEY_UP:
        case KEY_DOWN:
        case ' ':
        case '\n':
            fprintf(stderr, "%c", out_char);
            current_pos = 1;
            // if(command line option is set) out_char = 0;
            break;
    }
  }

end:
  //clean up
  //fclose(fifo);
  clear();
  delwin(stdscr);
  endwin();
  refresh();
  return EXIT_SUCCESS;
}
