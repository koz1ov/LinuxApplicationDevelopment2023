#include <ncurses.h>
#include <stdlib.h>
#include <assert.h>

#define DX 3
#define SPACE_CHAR 32

char* read_str(FILE* file) {
    char *input = calloc(1, sizeof(char));

    int input_cap = 1;
    int input_size = 0;
    int ch;
    while (1) {
        ch = fgetc(file);
        if (ch == EOF)
            break;

        if (input_size + 1 >= input_cap) {
            input_cap = input_cap * 2 + 1;
            input = realloc(input, input_cap);
        }

        input[input_size++] = ch;
        if (ch == '\n') 
            break;
    }

    input[input_size] = 0;
    input = realloc(input, input_size + 1);
    return input;
}

char** read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    char **lines = calloc(1, sizeof(char*));;
    int input_cap = 1;
    int input_size = 0;
    char *line = NULL;
    while (*(line = read_str(file))) {
        if (input_size + 1 >= input_cap) {
            input_cap = input_cap * 2 + 1;
            lines = realloc(lines, input_cap * sizeof(char*));
        }
        
        lines[input_size++] = line;
    }

    free(line);
    lines[input_size] = 0;
    return lines;
}

void draw_text(WINDOW* win, char** lines, int start_line) {
    werase(win);
    wmove(win, 1, 0);
    for (int i = start_line; i + 1 < start_line + win->_maxy && lines[i]; ++i) {
        wprintw(win, " %4d: %s", i + 1, lines[i]);
        box(win, 0, 0);
    }
    box(win, 0, 0);
    wrefresh(win);   
}

int main(int argc, char** argv) {
    char **lines = read_file(argv[1]);

    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    printw("%s", argv[1]);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, FALSE);
    wmove(win, 1, 0); 
    box(win, 0, 0); 
    int start_line = 0;
    
    do {
        draw_text(win, lines, start_line);
    
        c = wgetch(win);    
        if (c == SPACE_CHAR && lines[start_line] && lines[start_line + 1]) {
            start_line += 1;
        } 
    } while(c != 27);
    endwin();

    for (int i = 0; lines[i]; ++i)
        free(lines[i]);
    free(lines);

    return 0;
}
