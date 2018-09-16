byte mutex = 1;
byte ticket = 0;
byte m = 0;
byte w = 0;
inline acquire(sem) {
	atomic {
		sem > 0;
		sem--
	}
}
inline release(sem) {
	sem++
}
active [5] proctype man(){
	acquire(mutex);
	acquire(ticket);
	acquire(ticket);
	release(mutex);
	m++;
	assert(m*2 <= w)
}
active [10] proctype woman(){
    release(ticket);
	w++	
}