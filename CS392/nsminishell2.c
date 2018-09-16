#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <sys/queue.h>
#include <string.h>
#include <stdio.h>


//TO DO: Make a stack that handles each command
//TO DO: Store every input in a file called .nsmshistory
//TO DO: Dollar Sign: Program the ability to use the $() to pass output from one program into another (i.e. more $(myselect *.c)) 
//TO DO: ADD CD, HELP, AND EXIT, print current directory

char * intprtkey(int ch);

void moveRight(WINDOW * mainwin){
	int row, col;
	getyx(mainwin,row, col);
    int newcol = col+1;
    move(row, newcol);
    refresh();
}

void moveLeft(WINDOW * mainwin){
	int row, col;
    getyx(mainwin, row, col);
    int newcol = col-1;
    move(row,newcol);
    refresh();
}

void append(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
    //s[len+1] = '\0';
}


int main(void) {

    WINDOW * mainwin;
    int ch, row, col, totalrow, totalcol;
    char currentcmd[1024];
    row = 0;
    col = 0;
    int cmdsize;
    char clipboard[1024];
    memset(clipboard, 0, sizeof(clipboard));


    FILE *fp;
	fp = fopen("test.txt", "w");// "w" means that we are going to write on this file

    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initializing ncurses.\n");
		exit(EXIT_FAILURE);
    }

    if(!has_colors()) {
    	printw("This terminal does not support colours.\n");
    	exit(1);
  	}
  	start_color();
  	init_pair(1, COLOR_BLACK, COLOR_WHITE);
  	wbkgd(mainwin, COLOR_PAIR(1));

  	initscr();
  	getmaxyx(stdscr,totalrow,totalcol);		/* get the number of rows and columns */

	printw("$ NSMINISHELL: ");
    refresh();

    keypad(mainwin, TRUE);     /*  Enable the keypad for non-char keys  */

    while(1){

		//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);

    	//left arrow gets pressed
    	noecho();

    	ch = getch();

    	getyx(mainwin, row, col);
    	//getstr(currentcmd);
    	//printw("%d", strlen(currentcmd));
//    	raw();

    	if(ch == KEY_LEFT){
    		moveLeft(mainwin);
    	}

    	//right arrow gets pressed
    	else if(ch == KEY_RIGHT){
			moveRight(mainwin);    		
    	}

    	//up arrow gets pressed
    	else if(ch == KEY_UP){
    		addstr("UP KEY PRESSED\n");
    	}

    	//down arrow gets pressed
    	else if(ch == KEY_DOWN){
    		addstr("DOWN KEY PRESSED\n");
    	}

    	//backspace gets pressed
    	else if(ch == KEY_BACKSPACE){
    		noecho();
            addstr("\b \b");//implementing the effect of backspace
    	}

    	else if(ch == 12){ //12
    		/* Clear the terminal except for the current command */
    		clear();
    		printw("$ NSMINISHELL: ");
    		printw(currentcmd);

    	}

    	else if(ch == 1){ //1
    		/*  Move to the start of the current command */
    		//addstr("CONTROL+A PRESSED\n");
    		int i;
    		for(i = col; i >15; i--){
    			moveLeft(mainwin);
    		}

    	}

    	else if(ch == 5){ //5
    		/* Move to the end of the current command */
    		//addstr("CONTROL+E PRESSED\n");
    		cmdsize = strlen(currentcmd);
    		int i;
    		getyx(mainwin,row, col);

    		//printf("%d\n", cmdsize);
    		move(row, cmdsize+13);


    	}

    	else if(ch  == 23){ //23
    		/*  Cut a word into the clipboard. You should be abe to cut multiple words. (Try using it in bash!) */
    		//addstr("CONTROL+W PRESSED\n");
    		int i;
    		i = col;
    		// printw("%d",col);
    		int newrow, newcol;

    		while(i > 14 && currentcmd[i-14] !=' '){
    			append(clipboard, currentcmd[i-14]);
    			mvaddstr(row, i," ");
    			i--;
    			if(i > 14) move(row, i);
    			else move(row, 15);
    		}

    		fprintf(fp, "This is being written in the file. This is an int variable: %s", clipboard);

    	
    	}

    	else if(ch == 21){ // 21
    		/* Cut a line into the clipboard. It should be able to work with the above commend. (Once again, try using it in bash!) */
    		//addstr("CONTROL+U PRESSED\n");
    		//getstr(currentcmd);
    		//printw("%d", strlen(currentcmd));

    		int i;
    		i = col;
    		// printw("%d",col);
    		int newrow, newcol;

    		while(i > 14){
    			append(clipboard, currentcmd[i-15]);
    			mvaddstr(row, i," ");
    			i--;
    			if(i > 14) move(row, i);
    			else move(row, 15);
    		}
    	
    	}

    	else if(ch == 25){ //25
    		/*  Paste. */
    		//addstr("CONTROL+Y PRESSED\n");
    		//getstr(currentcmd);
    		int i;
    		for(i=strlen(clipboard)+1; i>= 0; i--){
    			printw("%c",clipboard[i]);
    		}

    		memset(clipboard, 0, sizeof(clipboard));


    	
    	}

    	else if(ch == 10){
    		printw("\n$ NSMINISHELL: ");
    		memset(currentcmd, 0, sizeof(currentcmd));
    	}

    	else{
    		printw("%s", keyname(ch));
    		strcat(currentcmd, keyname(ch));

    	}

    	refresh();

    }

    delwin(mainwin);
    endwin();
    refresh();
    fclose(fp);
    return EXIT_SUCCESS;
}

struct keydesc {
    int  code;
    char name[20];
};

char * intprtkey(int ch) {

    /*  Define a selection of keys we will handle  */

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
    
    if ( isprint(ch) && !(ch & KEY_CODE_YES)) {

	/*  If a printable character  */

	keych[0] = ch;
	return keych;
    }
    else {

	/*  Non-printable, so loop through our array of structs  */

	int n = 0;
	
	do {
	    if ( keys[n].code == ch )
		return keys[n].name;
	    n++;
	} while ( keys[n].code != -1 );

	return keys[n].name;
    }    
    
    return NULL;        /*  We shouldn't get here  */
}


