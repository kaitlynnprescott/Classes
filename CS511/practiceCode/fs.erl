-module(fs).
-compile(export_all).


start(State,F) ->
    S=spawn(?MODULE,server,[State,F]),
    register(server,S).

server(State,F) ->
    receive 
	{From, Ref, apply, N} ->
	    case (catch (F(State,N))) of
		{'EXIT',Reason} ->
		    From!{self(),Ref,error,Reason};
		{NewState,Result} ->
		    From!{self(),Ref,Result},
		    server(NewState,F)
	    end;
	{From, Ref, update, G} ->
	    From!{self(),Ref,okUpdate},
	    server(State,G);
	{From, Ref, getState} ->
	    From!{self(),Ref,State},
	    server(State,F)
    end.

run_client(X) ->
    spawn(?MODULE,client,[X]).

client(X) ->
    S = whereis(server),
    R = make_ref(),
    S!{self(),R,apply,X},
    receive
	{From,Ref,Result} ->
	    io:format("Result is ~w~n",[Result]);
	{From,Ref,error,Reason} ->
	    io:format("Error in computation: ~w~n",[Reason])
    end.


