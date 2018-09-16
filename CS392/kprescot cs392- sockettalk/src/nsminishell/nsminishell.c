#include "my.h"
#include "list.h"
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <sys/queue.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <signal.h> 
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_SIZE 1024
struct s_node* history;
struct s_node* newnode;

char* interpretKey(int ch);

void killProc()
{
	/* ctrl c */
	int i = 0;
	char** user_input = 0;
	if (user_input != NULL)
	{
		while (user_input[i] != NULL)
		{
			free(user_input[i]);
			i++;
		}
		free(user_input);
	}
}

void right(WINDOW* mainwindow)
{
	/* 
	 * right arrow
	 */
	int row, col;
	int newcol;
	getyx(mainwindow, row, col);
	newcol = col + 1;
	move(row, newcol);
	refresh();
}

void left(WINDOW* mainwindow)
{
	/* 
	 * left arrow
	 */
	int row, col, newcol;
	getyx(mainwindow, row, col);
	newcol = col - 1;
	move(row, newcol);
	refresh();
}

void paste_append(char*s, char c)
{
	int len = strlen(s);
	s[len] = c;
}

char** up(WINDOW* mainwindow)
{
	char** user_input = NULL;
	if (count_s_nodes(history) != 0)
	{
		user_input = elem_at(history, 1);
	}
	return user_input;
}

char** down(WINDOW* mainwindow)
{
	char** user_input = NULL;
	return user_input;
}

int main(void)
{
	WINDOW* mainwindow;
	int ch, row, col, totalrow, totalcol, newrow, newcol;
	char currcmd[1024];
	int cmdsize;
	struct s_node* history = NULL;
	char clipboard[1024];
	FILE *fp;
	memset(clipboard, 0, sizeof(clipboard));
	row = 0;
	col = 0;

	char* current;
	int size, i;
	int process_id;
	int return_value;
	char** user_input;
	char buffer[BUFFER_SIZE];

	

	signal(SIGINT, killProc);

	fp = fopen("test.txt", "w");

	if ((mainwindow = initscr()) == NULL)
	{
		fprintf(stderr, "Error initializing.\n");
		exit(EXIT_FAILURE);
	}
	if (!has_colors())
	{
		printw("This terminal does not support colors.\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	wbkgd(mainwindow, COLOR_PAIR(1));

	initscr();
	getmaxyx(stdscr, totalrow, totalcol);

	printw("$ NSMINISHELL: ");
	current = getcwd(current, BUFFER_SIZE);
    my_str(current);
    my_str(" / ");

	refresh();

	keypad(mainwindow, TRUE);

	while(ch != EOF)
	{
		/*
		 * Keyboard strokes
		 */
		noecho();
		ch = getch();
		getyx(mainwindow, row, col);

		if (ch == KEY_LEFT)
		{
			/* move cursor left */
			left(mainwindow);
		}
		else if (ch == KEY_RIGHT)
		{
			/* move cursor right */
			right(mainwindow);
		}
		else if (ch == KEY_UP)
		{
			/* move up */
			up(mainwindow);
		}
		else if (ch == KEY_DOWN)
		{
			/* move down */ 
			down(mainwindow);
		}
		else if (ch == KEY_BACKSPACE)
		{
			/*  
			 * Backspace
			 */ 
			noecho();
			addstr("\b \b");
		}
		else if (ch == 12)
		{
			/* 
			 * clear terminal
			 * CTRL-L
			 */
			clear();
			printw("$ NSMINISHELL: ");
			printw(currcmd);
		}
		else if (ch == 1)
		{
			/* 
			 * move to start of current command 
			 * CTRL-A 
			 */
			for (i = col; i > 15; i--)
			{
				left(mainwindow);
			}
		}
		else if (ch == 5)
		{
			/*
			 * move to end of current command
			 * CTRL-E
			 */
			 cmdsize = strlen(currcmd);
			 getyx(mainwindow, row, col);
			 move(row, cmdsize + 13);
		}
		else if (ch == 23)
		{
			/* 
			 * cut word into clipboard (should work for multiple words) 
			 * CTRL-W 
			 */
			i = col;
			while (i > 14 && currcmd[i-14] != ' ')
			{
			 	paste_append(clipboard, currcmd[i-14]);
			 	mvaddstr(row, i, " ");
			 	i--;
			 	if (i > 14)
			 	{
			 		move(row, i);
			 	}
			 	else
			 	{
			 		move(row, 15);
			 	}
			}
		 	fprintf(fp, "This is being written in the file. This is an int variale: %s", clipboard);
		}
		else if (ch == 21)
		{
			/* 
			 * cut line to clipboard. should be able to work with above commend.
			 * CTRL-U 
			 */
			i = col;
			while (i > 14)
			{
				paste_append(clipboard, currcmd[i-15]);
				mvaddstr(row, i, " ");
				i--;
				if (i > 14)
				{
					move(row, i);
				}
				else
				{
					move(row, 15);
				}
			}
		}
		else if (ch == 25)
		{
			/* 
			 * Paste
			 * CTRL-Y 
			 */
			 for (i = strlen(clipboard) + 1; i >= 0; i--)
			 {
			 	printw("%c", clipboard[i]);
			 }
			 memset(clipboard, 0, sizeof(clipboard));
		}
		else if (ch == 10)
		{
			printw("\n$ NSMINISHELL: ");
			memset(currcmd, 0, sizeof(currcmd));
		}
		else
		{
			printw("%s", keyname(ch));
			strcat(currcmd, keyname(ch));
		}

		/*
		 * commands (i.e. help, cd, exit)
		 * saving command to history
		 */

		if ((size = read(0, buffer, BUFFER_SIZE - 1)) < 0)
		{
			my_str("Error Reading.\n");
			exit(0);
		}
		buffer[size - 1] = '\0';
		user_input = my_str2vect(buffer);

		newnode = new_node(user_input, NULL, NULL);
		add_node(newnode, &history);

		if (user_input[0] != NULL)
		{
			if (strcmp(user_input[0], "help") == 0)
			{
				/*help commmand*/
            	my_str("\n    MINISHELL HELP DIRECTORY     \n");
                my_str("Possible Commands:\n");
                my_str("  cd : example/c/hello/: : Changes the current working directory to directory.\n");
                my_str("  exit : Exits the minishell.\n");
                my_str("  help : Prints a help message listing the built in commands.\n");
                my_str("  <executable> <args> - Run Programs while in their working directory.\n");
                my_str("  ls : Displays all files within the selected directory.\n");
                my_str("  CTRL + C : Kills the current running process.\n");
                my_str("\n");
			}
			else if (strcmp(user_input[0], "exit") == 0)
			{
				/* exit command */
				my_str("Exiting NSMINISHELL");
				i = 0;
				if (user_input != NULL)
				{
					while (user_input[i] != NULL)
						{
							free(user_input[i]);
							i++;
						}
						free(user_input);
				}
				exit(0);
			}
			else if (strcmp(user_input[0], "cd") == 0)
			{
				if ((return_value = chdir(user_input[1])) < 0)
				{
					if (user_input[1] == NULL)
					{
						my_str("Invalid input\n");
					}
					else
					{
						my_str(": ");
						my_str(user_input[1]);
						my_str(" : Directory not found\n");
					}
				}
			}
			else
			{
				if ((process_id = fork()) < 0)
				{
					my_str("Error\n");
					exit(0);
				}
				if (process_id > 0)
				{
					wait(NULL);
				}
				else
				{
					if ((return_value = execvp(user_input[0], user_input)) < 0)
					{
						my_str(user_input[0]);
						my_str(": Command not found\n");
						exit(0);
					}
				}
			}
			i = 0;
			if (user_input != NULL)
			{
				while(user_input[i] != NULL)
				{
					free(user_input[i]);
					i++;
				}
				free(user_input);
			}
		}
		refresh();
	}
	delwin(mainwindow);
	endwin();
	refresh();
	fclose(fp);
	return 0;
}

struct keydesc
{
	int code;
	char name[20];
};
char* interpretKey(int ch)
{
	/* define keys we will handle */
	static struct keydesc keys[] = { { KEY_UP,        "Up arrow"        },
				     { KEY_DOWN,      "Down arrow"      },
				     { KEY_LEFT,      "Left arrow"      },
				     { KEY_RIGHT,     "Right arrow"     },
				     { KEY_HOME,      "Home"            },
				     { KEY_END,       "End"             },
				     { KEY_BACKSPACE, "Backspace"       },
				     { KEY_IC,        "Insert"          },
				     { KEY_DC,        "Delete"          },
				     { KEY_NPAGE,     "Page down"       },
				     { KEY_PPAGE,     "Page up"         },
				     { KEY_F(1),      "Function key 1"  },
				     { KEY_F(2),      "Function key 2"  },
				     { KEY_F(3),      "Function key 3"  },
				     { KEY_F(4),      "Function key 4"  },
				     { KEY_F(5),      "Function key 5"  },
				     { KEY_F(6),      "Function key 6"  },
				     { KEY_F(7),      "Function key 7"  },
				     { KEY_F(8),      "Function key 8"  },
				     { KEY_F(9),      "Function key 9"  },
				     { KEY_F(10),     "Function key 10" },
				     { KEY_F(11),     "Function key 11" },
				     { KEY_F(12),     "Function key 12" },
				     { -1,            "<unsupported>"   }
    };
    static char keych[2] = {0};
    if (isprint(ch) && !(ch & KEY_CODE_YES))
    {
    	/* can print it */
    	keych[0] = ch;
    	return keych;
    }
    else
    {
    	/* can't print it */
    	int n = 0;
    	do {
    		if (keys[n].code == ch)
    		{
    			return keys[n].name;
    		}
    		n++;
    	} while (keys[n].code != -1);

    	return keys[n].name;
    }
    return NULL; /* wouldn't get here */
}