#include "my_select.h"

void changed_window()
{
	int x, y;
	getmaxyx(stdscr, y, x);
	if (y < 2 || x < 2)
	{
		clrtoeol();
		refresh();
		attron(A_REVERSE);
		printw(A_REVERSE);
	}
	else
	{
		resizeterm(y, x);
	}
}