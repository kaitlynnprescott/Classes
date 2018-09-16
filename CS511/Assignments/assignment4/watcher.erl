% We pledge our honor that we have abided by the stevens honor system %
-module (watcher).
-compile(export_all).
-author("Jennifer Cafiero and Kaitlynn Prescott").

start(NumSensor) ->
	if 
		NumSensor == 0 ->
			io:format("Please enter a number of sensors greater than 0.~n");
		true ->
			create(NumSensor, [], 0)
	end.

create(NumSensor, SensorList, SensorId) ->
	if 
		length(SensorList) == 10 ->
			io:fwrite("Watching:~n"),
			[io:fwrite("Id: ~p, Pid: ~p~n", [Id, Pid]) || {Id, Pid} <- SensorList],
			if 
				NumSensor /= 0 ->
					spawn(watcher, create, [NumSensor, [], SensorId]),
					watch(SensorList);
				true ->
					watch(SensorList)
			end;

		NumSensor == 0 ->
			io:format("Watching~n"),
			[io:fwrite("Id: ~p, Pid: ~p~n", [Id, Pid]) || {Id, Pid} <- SensorList],
			watch(SensorList);
		true ->
			{SensorPid, _} = spawn_monitor(sensor, start, [self(), SensorId]),
			create(NumSensor - 1, lists:merge(SensorList, [{SensorId, SensorPid}]), SensorId + 1)
	end.

restart(SensorList, SensorId) ->
	{SensorPid, _} = spawn_monitor(sensor, start, [self(), SensorId]),
	io:fwrite("Restarted sensor: ~p, new Pid: ~p~n", [SensorId, SensorPid]),
	RestartList = lists:merge(SensorList, [{SensorId, SensorPid}]),
	[io:fwrite("Id: ~p, Pid: ~p~n", [Id, Pid]) || {Id, Pid} <- RestartList],
	watch(RestartList).

watch(SensorList) ->
	receive
		{kill, {From, FromId}, anomalous_reading} ->
			io:fwrite("Sensor ~p died. Error: ~p~n", [FromId, anomalous_reading]),
			restart(lists:delete({FromId, From}, SensorList), FromId);
		{Measurement, {From, FromId}, Ref} ->
			io:fwrite("Measurement Data: ~2p, From sensor ~4p~n", [Measurement, FromId]),
			%io:fwrite("Sensor ~4p has measurement ~2p.~n", [FromId, Measurement]),
			From ! {ok, Ref},
			watch(SensorList)
	end.

