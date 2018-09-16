#include "my_select.h"

/* initialize termcaps */

void initialize_termcaps()
{
	char* term;
	char bp[2048];

	term = getenv("TERM");
	tgetent(bp, term);

	gl_env.left = get_cap(LEFT);
	gl_env.right = get_cap(RIGHT);
	gl_env.up = get_cap(UP);
	gl_env.down = get_cap(DOWN);
	gl_env.underlineon = get_cap(UNDERLINEON);
	gl_env.underlineoff = get_cap(UNDERLINEOFF);
	gl_env.highlighton = get_cap(HIGHLIGHTON);
	gl_env.highlightoff = get_cap(HIGHLIGHTOFF);
	gl_env.move = get_cap(MOVE);
	gl_env.clear = get_cap(CLEAR);
	gl_env.cursoroff = get_cap(CURSOROFF);
	gl_env.cursoron = get_cap(CURSORON);
}