% <exp> ::= {var, <string>}
% 		| const int
% 		| add exp exp
% 		| sub exp exp
% 		| mul exp exp 
% 		| div exp exp 
% return a value

% val ::=  const int
-module (quiz6).
-module (export_all).

anEnv()->
	dict:store("x", 1, dict:store("y", 2, dict:new())).

newEnv()->
	[].

extendEnv(Env, Key, Value) ->
	[{Key, Value}|Env].

lookupEnv([], _Key) ->
	exit(error);
lookupEnv([{Key1, Value}|_T], Key)

calc(Env, {const, N}) ->
	{const, N};
calc(Env, {var, V}) ->
	{const, dict:fetch(V, Env)};
calc(Env, {add, E1, E2}) ->
	{const, N1} = calc(Env, E1),
	{const, N2} = calc(Env, E2),
	{const, N1+N2};
calc(Env, {sub, E1, E2}) ->
	{const, N1} = calc(Env, E1),
	{const, N2} = calc(Env, E2),
	{const, N1-N2};
calc(Env, {mul, E1, E2}) ->
	{const, N1} = calc(Env, E1),
	{const, N2} = calc(Env, E2),
	{const, N1*N2};
calc(Env, {divi, E1, E2}) ->
	{const, N1} = calc(Env, E1),
	{const, N2} = calc(Env, E2),
	{const, N1 div N2}.