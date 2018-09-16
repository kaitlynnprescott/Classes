-module (my_timer).
-compile(export_all).

sendTicks([]) ->
	sent;
sendTicks([H|T]) ->
	H!tick,
	sendTicks(T).

my_timer(PidList) ->
	receive 
		stop -> done
	after 0 ->
		timer:sleep(1000),
		sendTicks(PidList),
		my_timer(PidList)
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
	Server = spawn(?MODULE, my_timer, [[C1, C2, C3]]),
	timer:sleep(3500),
	C1!stop,
	C2!stop,
	C3!stop,
	Server!stop.