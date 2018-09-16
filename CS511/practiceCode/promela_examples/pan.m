#define rand	pan_rand
#define pthread_equal(a,b)	((a)==(b))
#if defined(HAS_CODE) && defined(VERBOSE)
	#ifdef BFS_PAR
		bfs_printf("Pr: %d Tr: %d\n", II, t->forw);
	#else
		cpu_printf("Pr: %d Tr: %d\n", II, t->forw);
	#endif
#endif
	switch (t->forw) {
	default: Uerror("bad forward move");
	case 0:	/* if without executable clauses */
		continue;
	case 1: /* generic 'goto' or 'skip' */
		IfNotBlocked
		_m = 3; goto P999;
	case 2: /* generic 'else' */
		IfNotBlocked
		if (trpt->o_pm&1) continue;
		_m = 3; goto P999;

		 /* PROC woman */
	case 3: // STATE 1 - bar.pml:12 - [ticket = (ticket+1)] (0:0:1 - 1)
		IfNotBlocked
		reached[1][1] = 1;
		(trpt+1)->bup.oval = ((int)now.ticket);
		now.ticket = (((int)now.ticket)+1);
#ifdef VAR_RANGES
		logval("ticket", ((int)now.ticket));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 4: // STATE 3 - bar.pml:24 - [w = (w+1)] (0:0:1 - 1)
		IfNotBlocked
		reached[1][3] = 1;
		(trpt+1)->bup.oval = ((int)now.w);
		now.w = (((int)now.w)+1);
#ifdef VAR_RANGES
		logval("w", ((int)now.w));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 5: // STATE 4 - bar.pml:25 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[1][4] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC man */
	case 6: // STATE 1 - bar.pml:7 - [((mutex>0))] (8:0:1 - 1)
		IfNotBlocked
		reached[0][1] = 1;
		if (!((((int)now.mutex)>0)))
			continue;
		/* merge: mutex = (mutex-1)(0, 2, 8) */
		reached[0][2] = 1;
		(trpt+1)->bup.oval = ((int)now.mutex);
		now.mutex = (((int)now.mutex)-1);
#ifdef VAR_RANGES
		logval("mutex", ((int)now.mutex));
#endif
		;
		_m = 3; goto P999; /* 1 */
	case 7: // STATE 5 - bar.pml:7 - [((ticket>0))] (12:0:1 - 1)
		IfNotBlocked
		reached[0][5] = 1;
		if (!((((int)now.ticket)>0)))
			continue;
		/* merge: ticket = (ticket-1)(0, 6, 12) */
		reached[0][6] = 1;
		(trpt+1)->bup.oval = ((int)now.ticket);
		now.ticket = (((int)now.ticket)-1);
#ifdef VAR_RANGES
		logval("ticket", ((int)now.ticket));
#endif
		;
		_m = 3; goto P999; /* 1 */
	case 8: // STATE 9 - bar.pml:7 - [((ticket>0))] (14:0:1 - 1)
		IfNotBlocked
		reached[0][9] = 1;
		if (!((((int)now.ticket)>0)))
			continue;
		/* merge: ticket = (ticket-1)(0, 10, 14) */
		reached[0][10] = 1;
		(trpt+1)->bup.oval = ((int)now.ticket);
		now.ticket = (((int)now.ticket)-1);
#ifdef VAR_RANGES
		logval("ticket", ((int)now.ticket));
#endif
		;
		_m = 3; goto P999; /* 1 */
	case 9: // STATE 13 - bar.pml:12 - [mutex = (mutex+1)] (0:0:1 - 1)
		IfNotBlocked
		reached[0][13] = 1;
		(trpt+1)->bup.oval = ((int)now.mutex);
		now.mutex = (((int)now.mutex)+1);
#ifdef VAR_RANGES
		logval("mutex", ((int)now.mutex));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 10: // STATE 15 - bar.pml:19 - [m = (m+1)] (0:0:1 - 1)
		IfNotBlocked
		reached[0][15] = 1;
		(trpt+1)->bup.oval = ((int)now.m);
		now.m = (((int)now.m)+1);
#ifdef VAR_RANGES
		logval("m", ((int)now.m));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 11: // STATE 16 - bar.pml:20 - [assert(((m*2)<=w))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][16] = 1;
		spin_assert(((((int)now.m)*2)<=((int)now.w)), "((m*2)<=w)", II, tt, t);
		_m = 3; goto P999; /* 0 */
	case 12: // STATE 17 - bar.pml:21 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[0][17] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */
	case  _T5:	/* np_ */
		if (!((!(trpt->o_pm&4) && !(trpt->tau&128))))
			continue;
		/* else fall through */
	case  _T2:	/* true */
		_m = 3; goto P999;
#undef rand
	}

