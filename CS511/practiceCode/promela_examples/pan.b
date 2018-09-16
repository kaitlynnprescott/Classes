	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* PROC woman */

	case 3: // STATE 1
		;
		now.ticket = trpt->bup.oval;
		;
		goto R999;

	case 4: // STATE 3
		;
		now.w = trpt->bup.oval;
		;
		goto R999;

	case 5: // STATE 4
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC man */

	case 6: // STATE 2
		;
		now.mutex = trpt->bup.oval;
		;
		goto R999;

	case 7: // STATE 6
		;
		now.ticket = trpt->bup.oval;
		;
		goto R999;

	case 8: // STATE 10
		;
		now.ticket = trpt->bup.oval;
		;
		goto R999;

	case 9: // STATE 13
		;
		now.mutex = trpt->bup.oval;
		;
		goto R999;

	case 10: // STATE 15
		;
		now.m = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 12: // STATE 17
		;
		p_restor(II);
		;
		;
		goto R999;
	}

