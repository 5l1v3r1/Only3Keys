#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//globals
char binary[] = "0b0000000";

int incrementPos(int x) {
    if (++x >= 8) x = 1;
    return x;
}

void binarystr(int out_char) {
    for(int i = 0; i < 7; i++) 
        binary[2+i] = (out_char & (1 << (6-i))) ? '1' : '0';
}

int main(int argc, char** argv) {

  //define  vars
  WINDOW *stdscr;
  int in_char = 0;
  int out_char = 0;
  uint8_t current_pos = 1;

  //basic ncurses setup
  if ((stdscr = initscr()) == NULL){
    fprintf(stderr, "ncurses Error!");
    exit(EXIT_FAILURE);
  }
  if (!has_colors()){
    endwin();
    fprintf(stderr, "Error: No Color Support!");
    exit(EXIT_FAILURE);
  }

  start_color();
  cbreak(); //single keypress at a time. no need for CR
  noecho(); 
  curs_set(FALSE);
  keypad(stdscr, true);

  while(true) {
    binarystr(out_char);

    clear();
    mvprintw(0, 0, "%s (0x%x) = %c", binary, out_char, out_char);
    mvprintw(1, 2 + (7-current_pos), "^");
    refresh();

    in_char = wgetch(stdscr);
  
    switch(in_char) {
        case 'q':
            goto end;
            break;
 
        // 1
        case KEY_LEFT:
            out_char = out_char | 1 << (current_pos - 1);
            current_pos = incrementPos(current_pos);
            break;

        // 0
        case KEY_RIGHT:
            out_char = out_char & ~(1 << (current_pos -1));
            current_pos = incrementPos(current_pos);
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
  delwin(stdscr);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}
