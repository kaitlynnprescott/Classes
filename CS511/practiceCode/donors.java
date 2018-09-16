Semaphore beds = new Semaphore(4);
Semaphore magazines = new Semaphore(10);
Semaphore mutex = new Semaphore(1);
thread Donor : {
    boolean haveMagazine = false;
    boolean wantMagazine = true;
    thread { // donor competes for beds
        beds.acquire(); // bed.1
        mutex.acquire(); // bed.2
        if (haveMagazine) {
            magazines.release)();
        }
        wantMagazine = false;
        haveMagazine = false;
        mutex.release();
        // donate blood
    }   
    thread { // donor competes for magazines
        magazines.acquire(); // mag.1
        mutex.acquire(); // mag.2
        haveMagazine = true;
        if (!wantMagazine) {
            magazines.release();
            haveMagazine = false;
        }
        mutex.release();
    }
}
