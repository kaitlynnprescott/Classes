-module(gs).
-compile(export_all).

fact(0) ->
	1;
fact(N) when N>0 ->
	N * fact(N-1).

start(F) ->
	spawn(?MODULE, server, [0,F]).

server(State, F) ->
	receive 
		{From, Ref, compute, N} ->
			{UState,Result} = F(State,N),
			From!{self(), Ref, fact(N)},
			server(UState, F);
			}
		{From, Ref, update, G} ->
			From!{self(), Ref, okUpdate},
			server(State,G);
		{From, Ref, getState} ->
			From!{self(), Ref, State},
			server(State,F);
	end.

client(S,X) ->
	R = make_ref(),
	S!{self(), R, X},
	receive
		{S, R, compute, FN} ->
			io:format("Got ~w~n", [FN])
end.