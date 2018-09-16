#include "my_select.h"

int main(int argc, char** argv)
{
	int count;
	int bytes;
	char input[READMIN + 2];

	if (argc < 2)
	{
		my_str("Usage: ./my_select itemSelector\n");
		exit(1);
	}

	signal(SIGWINCH, show_elements);

	initialize_termcaps();
	start_term();
	setup_elements(argc-1, &argv[1]);
	tputs(gl_env.cursoroff, 0, my_termprint);
	show_elements();

	while(1)
	{
		bytes = read(0, &input, READMIN + 2);
		input[bytes] = '\0';

		if (!gl_env.flag)
		{
			char_check(input);
		}
	}
	
	return 0;
}