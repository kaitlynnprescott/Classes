#include "my_select.h"
#include <termios.h>
#include <signal.h>

WINDOW *menu;

int main(int argc, char** argv)
{
	int count;
	int character;

	int choice_y = 0;
	int choice_x = 0;
	int choice = 0;
	int c, n_choices, fnum, i, size_y, size_x;
	char* array[argc - 1];
	int columns_choices;
	if (argc < 2)
	{
		perror("Error Args: ./my_select args");
		return -1;
	}

	memset(boolean_array, 0, sizeof(boolean_array));

	for (fnum = 1; fnum < argc; funm++)
	{
		array[fnum - 1] = argv[fnum];
	}
	n_choices = fnum - 1;

	initscr();
	wclear(stdscr);
	noecho();
	raw();
	getmaxyx(stdscr, size_y, size_x);
	menu = newin(size_y, size_x, 0, 0);

	keypad(menu, TRUE);
	refresh();
	print_args(menu, choice_y, choice_x, boolean_array, n_choices, array);
	while(1)
	{
		getmaxyx(stdscr, size_y, size_x);
		if (n_choices > size_y)
		{
			columns_choices = (n_choices/size_y);
		}
		else
		{
			columns_choices = 0;
		}

		curs_set(0);
		c = wgetch(menu);
		switch(c)
		{
			case KEY_UP:
				if (choice_y == (n_choices - 1) && choice_x == 0)
				{
					choice_y = n_choices - 1;
				}
				else if (choice_y == 0 && choice_x == columns_choices)
				{
					choice_y = (n_choices - 1) - (choice_x*size_y);
				}
				else if (choice_y == 0 && choice_x == 0)
				{
					choice_x = columns_choices;
					choice_y = (n_choices - 1) - (choice_x*size_y);
				}
				else
				{
					--choice_y;
				}
				break;
			case KEY_DOWN:
				if (choice_y == (n_choices - 1) && choice_x == 0)
				{
					choice_y = 0;
				}
				else if(choice_y == ((choice_x + 1) * size_y) - 1)
				{
					choice_y = ((choice_x + size_y) * choice_x);
				}
				else if ((choice_x == columns_choices) && (choice_y == ((n_choices - 1) (choice_x * size_y))))
				{
					choice_x = 0;
					choice_y = 0;
				}
				else
				{
					++choice_y;
				}
				break;
			case KEY_RIGHT:
				if(columns_choices == 0)
				{
					choice_y = n_choices - 1;
				}
				else if (choice_x == columns_choices)
				{
					choice_y = (n_choices - 1) - (choice_x * size_y);
				}
				else if ((choice_y + (size_y * (choice_x + 1))) > (n_choices - 1))
				{
					continue;
				}
				else 
				{
					++choice_x;
				}
				break;
			case KEY_LEFT:
				if (choice_x == 0)
				{
					choice_y = 0;
				}
				else 
				{
					--choice_x;
				}
				break;
			case 10:
				choice = 5;
				break;
			case 27:
				clrtoeol();
				refresh();
				endwin();
				return 0;
			case 32:
				if (boolean_array[choice_y + (choice_x * size_y)] == 1)
				{
					boolean_array[choice_y + (choice_x * size_y)] = 0;
				}
				else 
				{
					if (choice_y == n_choices - 1 && (choice_x == 0))
					{
						boolean_array[choice_y + (choice_x * size_y)] = 1;
						choice_y = 0;
					}
					else if ((choice_y + (choice_x * size_y)) == n_choices - 1)
					{
						boolean_array[choice_y + (choice_x * size_y)] = 1;
						choice_y = 0;
					}
					else 
					{
						boolean_array[choice_y + (choice_x * size_y)] = 1;
						choice_y++;
					}
				}
				break;
			default:
				break;
		}
		if (choice != 0)
		{
			break;
		}
		print_args(menu, choice_y, choice_x, boolean_array, n_choices, array);
	}

	clrtoeol();
	refresh();
	endwin();

	for (i = 0; i < fnum; i++)
	{
		if (boolean_array[i] == 1)
		{
			fprintf(stdout, array[i]);
			fprintf(stdout, " ");
		}
	}
	
	return 0;
}