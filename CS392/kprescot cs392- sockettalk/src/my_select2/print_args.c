#include "my_select.h"
#include "my.h"

void print_args(WINDOW *menu_win, int choice_y, int choice_x, int* boolean_test, int num_args, char** list)
{
	int print_x = 0;
	int print_y = 0;
	int arg, size_y, size_x;
	getmaxyx(stdscr, size_y, size_x);
	int str_len = 0;

	if ((size_y < 15) || (size_x < 55))
	{
		wclear(menu_win);
		wrefresh(menu_win);
		mvwprintw(menu_win, size_y/2, (size_x/2)-2, "Please Enlarge the Window.");
		clear();
		wrefresh(stdscr);
		return;
	}
	else
	{
		wclear(menu_win);
		wrefresh(menu_win);
	}
	
	str_len = 0;
	for (arg = 0; arg < num_args; ++arg)
	{
		if (my_strlen(list[arg]) > str_len)
		{
			str_len = my_strlen(list[arg]);
		}
		if (print_y > size_y - 1)
		{
			print_x += str_len + 2;
			print_y = 0;
		}
		if (boolean_test[arg] == 1)
		{
			if (choice_y + (choice_x * size_y) == arg)
			{
				wattron(menu_win, A_BLINK);
				mvwprintw(menu_win, print_y, print_x, "%s", list[arg]);
				wattroff(menu_win, A_BLINK);
			}
			else
			{
				wattron(menu_win, A_REVERSE);
				mvwprintw(menu_win, print_y, print_x, "%s", list[arg]);
				wattroff(menu_win, A_REVERSE);
			}
		}
		else if (choice_y + (choice_x * size_y) == arg)
		{
			wattron(menu_win, A_UNDERLINE);
			mvwprintw(menu_win, print_y, print_x, "%s", list[arg]);
			wattroff(menu_win, A_UNDERLINE);
		}
		else
		{
			mvwprintw(menu_win, print_y, print_x, "%s", list[arg]);
		}
		++print_y;
	}
	wrefresh(menu_win);
}