-module (guess).
-compile(export_all).

start() ->
	S = spawn(fun server/0).
	%spawn(?MODULE, client, [S, 0]).

server() -> 
	receive
		{From, Ref, start} ->
			LS = spawn(?MODULE, loop_server, [rand:uniform(100)]),
			From!{self(), Ref, LS}
	end,
	server().

loop_server(N) ->
	receive
		{From, Ref, N} ->
			From!{self(), Ref, gotIt};
		{From, Ref, _} ->
			From!{self(), Ref, tryAgain},
			loop_server(N)
	end.

client(S) ->
	Ref = make_ref(),
	S!{self(), Ref, start},
	receive
		{S, Ref, Servlet} ->
			client_loop(Servlet,0)
	end.

client_loop(S, T) ->
	N = rand:uniform(100),
	Ref = make_ref(),
	S!{self(), Ref, N},
	receive
		{From, Ref, gotIt} ->
			io:format("Got it after ~w attempts, it was ~w~n", [T, N]);
		{From, Ref, tryAgain} ->
			client_loop(S, T+1)
	end.



% start() ->
% 	Pid_S = spawn(?MODULE, server, [rand:uniform(100)]),
% 	_Pid_C = spawn(?MODULE, client, [Pid_S]).

% client(Pid_S) ->
% 	R = make_ref(),
% 	Pid_S ! {self(), R, rand:uniform(100)},
% 	receive
% 		{Pid_S, _Ref, gotIt} ->
% 			done;
% 		{Pid_S, _Ref, tryAgain} ->
% 			client(Pid_S)
% 	end.


% server(A) ->
% 	Ref = make_ref(),
% 	receive 
% 		{Pid_C, _R, N} ->
% 			io:format("Server=~p and client guessed ~p\n", [A, N]),
% 			case A == N of
% 				true ->
% 					Pid_C ! {self(), Ref, gotIt};
% 				false ->
% 					Pid_C ! {self(), Ref, tryAgain}
% 			end,
% 			server(N);
% 		stop ->
% 			stop
% 	end.

% 				%% check if N is the right number 
% 				%% if it is, return gotIt
% 				%% if not, return tryAgain






