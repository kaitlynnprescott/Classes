global Semaphore resource = new Semaphore(1);
global Semaphore mutex = new Semaphore(1);
global Semaphore queue = new Semaphore(1,true);
global int readers = 0;

thread Writer() {
  queue.acquire()l
  resource.acquire();
  queue.release();

  write();
  resource.release();
}

thread Reader() {
  queue.acquire();
  mutex.acquire();
  readers++;
  if (readers == 1){
    resource.acquire();
  }
  mutex.release();
  queue.release();

  item = read();
  
  mutex.acquire();
  readers--;
  if (readers == 0) {
    resource.release();
  }
  mutex.release();
  
}