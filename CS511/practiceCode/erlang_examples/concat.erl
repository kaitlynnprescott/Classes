-module(concat).
-compile(export_all).
concat(Dict) ->
	receive
		{CPID, start} ->
			%CPID ! {self(), ok},
			concat(dict:store(CPID, "", Dict));
		{CPID, add, S} ->
			%CPID ! {self(), ok},
			concat(dict:store(CPID, dict:fetch(CPID, Dict) ++ S, Dict));
		{CPID, done} ->
			String = dict:fetch(CPID, Dict),
			CPID ! {self(), result, String},
			concat(dict:erase(CPID, Dict));
		stop ->
			stop
	end.

client1(SPID) ->
	SPID ! {self(), start},
	%receive X -> X end,
	SPID ! {self(), add, "Hello"},
	timer:sleep(10),
	%receive X -> X end,
	SPID ! {self(), add, " World"},
	%receive X -> X end,
	SPID ! {self(), done},
	receive {SPID, result, S} -> io:format("~p", [S]) end.

client2(SPID) ->
	SPID ! {self(), start},
	%receive X -> X end,
	SPID ! {self(), add, "Test"},
	%receive X -> X end,
	SPID ! {self(), add, " Message"},
	%receive X -> X end,
	SPID ! {self(), add, " Complete"},
	SPID ! {self(), done},
	receive {SPID, result, S} -> io:format("~p", [S]) end.

start() ->
	SPID = spawn(?MODULE, concat, [dict:new()]),
	C1 = spawn(?MODULE, client1, [SPID]),
	C2 = spawn(?MODULE, client2, [SPID]).


