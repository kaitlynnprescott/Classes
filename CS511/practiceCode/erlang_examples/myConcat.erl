-module (myConcat).
-compile(export_all).

concat(Dict) -> 
	receive 
		{CPID, start} ->
			concat(dict:store(CPID, "", Dict));
		{CPID, add, S} ->
			concat(dict:store(CPID, dict:fetch(CPID, Dict) ++ S, Dict));
		{CPID, done} ->
			String = dict:fetch(CPID, Dict),
			CPID!{self(), result, String},
			concat(dict:erase(CPID, Dict));
		stop ->
			stop
	end.

client1(SPID) ->
	SPID!{self(), start},
	SPID!{self(), add, "Hello "},
	timer:sleep(10),
	SPID!{self(), add, "World!"},
	timer:sleep(10),
	SPID!{self(), done},
	receive
		{SPID, result, S} -> 
			io:format("~p~n", [S])
	end.

client2(SPID) ->
	SPID!{self(), start},
	SPID!{self(), add, "Testing "},
	timer:sleep(10),
	SPID!{self(), add, "concat "},
	timer:sleep(10),
	SPID!{self(), add, "complete"},
	timer:sleep(10),
	SPID!{self(), done},
	receive
		{SPID, result, S} ->
			io:format("~p~n", [S])
	end.

start() ->
	SPID = spawn(?MODULE, concat, [dict:new()]),
	C1 = spawn(?MODULE, client1, [SPID]),
	C2 = spawn(?MODULE, client2, [SPID]).

