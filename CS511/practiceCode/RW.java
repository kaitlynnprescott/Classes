monitor RW {
	private int readers = 0;
	private int writers = 0;
	private condition noWriters;
	private condition noRW;
	startReading() {
		if (writers != 0 || !noRW.empty()) { // give priority to writers if more readers try to get in. 
			noWriters.wait();
		}
		readers++;
		noWriters.signal(); // cascaded signaling 
	}
	stopReading() {
		readers--;
		if (readers == 0) {
			noRW.signal();
		}
	}
	startWriting() {
		if (readers != 0 || writers != 0) {
			noRW.wait();
		}
		writers++;
	}
	stopWriting() {
		writers--;
		if (noWriters.empty()) {
			noWriters.signal();
		} else {
			noRW.signal();
		}
	}
}