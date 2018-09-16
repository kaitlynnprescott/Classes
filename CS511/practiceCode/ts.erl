-module(ts).
-compile(export_all).

%% counter: should support two "operations": read and bump
counter(N) ->
   receive
       {From,R,bump} ->
	   From!{self(),R,ok},
	   counter(N+1);
       {From,R,read} ->
	   From!{self(),R,N},
	   counter(N);
       stop ->
	   stop
end.

%% turnstile: should bump the counter every so many milliseconds 
turnstile(TPID,_CPID,0) ->
    TPID!{self(),done};
turnstile(TPID,CPID,N) ->
    timer:sleep(rand:uniform(50)),
    R=make_ref(),
    CPID!{self(),R,bump},
    receive
	{CPID,R,ok} ->
	    turnstile(TPID,CPID,N-1)
    end.

start() ->
    CPID = spawn(?MODULE,counter,[0]), 
    T1PID = spawn(?MODULE,turnstile,[self(),CPID,50]),
    T2PID = spawn(?MODULE,turnstile,[self(),CPID,50]),
    %%% Wait for some amount of time and then print value of counter
    %%% timer:sleep(rand:uniform(2000)),
    receive 
	{T1PID,done} ->
	    receive 
		{T2PID,done} ->
		    ok
	    end
    end,
    R=make_ref(),
    CPID!{self(),R,read},
    receive
	{CPID,R,N} ->
	    io:format("The value of the counter is ~w~n",[N])
    end,
    CPID!stop.
    
    
