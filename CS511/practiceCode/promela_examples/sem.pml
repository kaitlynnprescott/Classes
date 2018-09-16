byte sem = 1;
byte critical = 0;

inline acquire(sem) {
	atomic {
		sem > 0;
		sem--
	}
}

inline release(sem) {
	sem++
}

active [2] proctype user() {
	do
		:: acquire(sem);
		printf("%d is in the CS\n", _pid);
		critical++;
		assert(critical==1)
		critical--;
		assert(critical==0)
		release(sem)
	od
}
