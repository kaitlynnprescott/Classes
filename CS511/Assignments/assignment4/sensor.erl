% We pledge our honor that we have abided by the stevens honor system %
-module(sensor).
-compile(export_all).
-author("Jennifer Cafiero and Kaitlynn Prescott").

start(WatcherPid, SensorId) ->
	Ref = make_ref(),
	sensor(WatcherPid, SensorId, Ref).

sensor(WatcherPid, SensorId, Ref) ->
	Measurement = rand:uniform(11),
	if 
		Measurement == 11 ->
			WatcherPid ! {kill, {self(), SensorId}, anomalous_reading},
			exit(anomalous_reading);
		true ->
			WatcherPid ! {Measurement, {self(), SensorId}, Ref}
	end,
	receive 
		{ok, Ref} ->
			Sleep_time = rand:uniform(10000),
			timer:sleep(Sleep_time),
			sensor(WatcherPid, SensorId, Ref)
	end.