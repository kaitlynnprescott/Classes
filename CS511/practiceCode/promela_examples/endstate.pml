byte request = 0;
active proctype Server1() {
  do
  :: request == 1 ->
    printf("Service 1\n");
	  request = 0;
	od
}

active prototype Server2() {
  do
  :: request == 2 ->
    printf("Service 2\n");
		request = 0;
	od
}

active prototype Client() {
  request = 1;
  request == 0;
  request = 2;
  request == 0;
}
