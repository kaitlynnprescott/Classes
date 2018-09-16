-module (barriers).
-compile(export_all).

coordinator(N) ->
	S = spawn(?MODULE, barrier_loop, [N,N,[]]),
	register(barrier, S).

barrier_loop(0,N,L) ->
	[From!{self(), Ref, ok} || {From, Ref} <- L],
	barrier_loop(N,N,[]);
barrier_loop(N,M,L) ->
	receive
		{From, Ref, arrived} ->
			barrier_loop(N-1,M,[{From,Ref} | L])
	end.

start() ->
	spawn(fun client1/0),
	spawn(fun client2/0).

client1() ->
	io:format("a~n"),
	B = whereis(barrier),
	R = make_ref(),
	B!{self(), R, arrived},
	receive
		{B, R, ok} ->
			io:format("b~n")
	end.

client2() ->
	io:format("c~n"),
	B = whereis(barrier),
	R = make_ref(),
	B!{self(), R, arrived},
	receive
		{B, R, ok} ->
			io:format("d~n")
	end.


