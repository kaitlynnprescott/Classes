-module (myPrime).
-compile(export_all).

isPrime(N) when N == 2 ->
	true;
isPrime(N) when N < 2 orelse N rem 2 == 0 ->
	flase;
isPrime(N) ->
	help(N, 3).

help(N, K) when K*K>N ->
	true;
help(N, K) when N rem K == 0 ->
	false;
help(N, K) ->
	help(N, K+2).

prime() ->
	receive 
		{CID, N} ->
			CID!{self(), isPrime(N)},
			prime();
		stop ->
			stop
	end.
start() ->
	SID = spawn(?MODULE, prime, []),
	X = 35,
	Y = 29,
	SID!{self(), X},
	receive
		{SID, B} ->
			io:format("~p is ~p~n", [X,B])
	end,
	SID!{self(), Y},
	receive
		{SID, B2} ->
			io:format("~p is ~p~n", [Y,B2])
	end,
	SID!stop.