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

%% solution 2

op() ->
	dict:store(add, fun(X,Y) -> X+Y end,
	dict:store(sub, fun(X,Y) -> X-Y end,
	dict:store(mul, fun(X,Y) -> X*Y end,
	dict:store(divd, fun(X,Y) -> X div Y end,
	dict:new())))).

calc2(_Env, {const, N}) ->
	{const, N};
calc2(Env, {var, X}) ->
	{const, dict:fetch(X, Env)};
calc2(Env, {Tag, E1, E2})->
	{const, V1} = calc2(Env, E1),
	{const, V2} = calc2(Env, E2),
	{const, apply(dict:fetch(Tag,op()), [V1, V2])}.