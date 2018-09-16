-module(primeA).
-compile(export_all).
isPrime(N) when N == 2 -> 
	true;
isPrime(N) when N < 2 orelse N rem 2 == 0 -> 
	false;
isPrime(N) -> 
	isPrimeH(N, 3).

isPrimeH(N, K) when K * K > N -> 
	true;
isPrimeH(N, K) when N rem K == 0 ->
	false;
isPrimeH(N, K) ->
	isPrimeH(N, K + 2).
prime() ->
	receive
		{CID, N} ->
			CID ! {self(), isPrime(N)},
			prime();
		stop ->
			stop
	end.
start() ->
	SID = spawn(?MODULE, prime, []),
	SID ! {self(), 1},
	receive
		{SID, B} -> io:format("~p\n", [B])
	end,
	SID ! {self(), 7},
	receive
		{SID, B2} -> io:format("~p\n", [B2])
	end,
	SID ! stop.
