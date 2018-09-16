-module (my_timer).
-compile(export_all).

sendTicks([]) ->
	sent;
sendTicks([H|T]) ->
	H!tick,
	sendTicks(T).

mytimer(PidList) ->
	receive 
		stop -> done
	after 0 ->
		timer:sleep(1000),
		sendTicks(PidList),
		mytimer(PidList)
	end.
client() ->
	receive
		tick ->
			io:format("Received tick~n"),
			client();
		stop ->
			done
	end.

start() ->
	C1 = spawn(?MODULE, client, []),
	C2 = spawn(?MODULE, client, []),
	C3 = spawn(?MODULE, client, []),
	Server = spawn(?MODULE, mytimer, [[C1, C2, C3]]),
	timer:sleep(5000),
	C1!stop,
	C2!stop,
	C3!stop,
	Server!stop.