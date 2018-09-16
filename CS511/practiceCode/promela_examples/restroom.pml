
byte men = 0;
byte women = 0;
byte mutexH = 1;
byte mutexM = 1;
byte mutexHM = 1;
byte toilet = 10;

inline acquire(sem) {
  atomic {
    sem>0;
    sem-- 
  }
}

inline release(sem) {
  sem++ 
}
active [4] proctype menThread() {
  /* Complete */
  acquire(mutexHM);
  acquire(mutexH);

  men++;
  if
  :: men == 1 -> acquire(mutexM)
  :: else -> skip
  fi;
  release(mutexH);
  release(mutexHM);
  acquire(toilet);
  assert(women == 0 && men <= 10);
  release(toilet);
  acquire(mutexH);
  men--;
  if
  :: men == 0 -> release(mutexM);
  :: else -> skip;
  fi;
  release(mutexH);
}

active [4] proctype womanThread() {
   /* complete */
   acquire(mutexHM);
   acquire(mutexM);

   women++;
   if
   :: women == 1 -> acquire(mutexH);
   :: else -> skip;
   fi;
   release(mutexM);
   release(mutexHM);
   acquire(toilet);
   assert(men == 0 && women <= 10);
   release(toilet);
   acquire(mutexM);
   women--;
   if
   :: women == 0 -> release(mutexH);
   :: else -> skip;
   fi;
   release(mutexM);
}


