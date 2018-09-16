#ifndef _MY_SELECT_H
#define _MY_SELECT_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/termios.h>
#include "my.h"
#include <signal.h>
#include <termcap.h>

#define READTIME 1

#define READMIN 3

#ifndef NULL
#define NULL (0)
#endif

#define KU "\E[A"
#define KD "\E[B"
#define KR "\E[C"
#define KL "\E[D"
#define UP "ku"
#define DOWN "kd"
#define LEFT "kl"
#define RIGHT "kr"
#define CLEAR "cl"
#define MOVE "cm"
#define HIGHLIGHTON "so"
#define HIGHLIGHTOFF "se"
#define UNDERLINEON "us"
#define UNDERLINEOFF "ue"
#define CURSORON "ve"
#define CURSOROFF "vi"
#define VECAP "\E[?25h"
#define VICAP "\E[?25l"
#define ESC 27

typedef struct s_elem
{
	char* elem;
	int size;
	int x;
	int y;
	int mode;
} t_elem;

typedef struct s_env
{
	char* left;
	char* right;
	char* up;
	char* down;
	char* esc;
	char* underlineon;
	char* underlineoff;
	char* highlighton;
	char* highlightoff;
	char* move;
	char* clear;
	char* cursoron;
	char* cursoroff;
	struct winsize win;
	struct termio line_backup;
	int flag;
	int stdio_backup;
	int nbelems;
	int pos;
	t_elem *elements;
} t_env;

t_env gl_env;

void start_term();
void restore_term();
void quit_term();
void clear_term();
char* get_cap(char*);
void intitial_termcaps();
int my_termprint(int);

void up();
void down();
void left();
void right();
void select_element();
void show_elements();
void setup_elements(int, char**);
void char_check(char*);
void move_next(int);
void highlight_on();
void highlight_off();
void underline_on();
void underline_off();
void underline_refresh();
void no_underline_refresh();

#endif