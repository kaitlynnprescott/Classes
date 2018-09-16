% hello world program
-module(ex).
-compile(export_all).

start() ->
    io:fwrite("Factorial of 20 is ~p~n",[fact(20)]),
    io:fwrite("Size of tree is ~p~n",[size_tree(abt())]).
    
arith(X, Y) ->
    io:format("Arguments: ~p ~p~n", [ X, Y ]) ,
    Sum = X + Y ,
    Diff = X - Y ,
    Prod = X * Y ,
    Quo = X div Y ,
    io:fwrite("~p ~p ~p ~p~n", [ Sum, Diff, Prod, Quo ]) ,
    { Sum, Diff, Prod, Quo }.

drivers_license(Age) when not(is_number(Age)) ->
    error_in_argument ;
drivers_license(Age) when Age < 16 ->
    forbidden ;
drivers_license(Age) when Age == 16 ->
    'learners permit' ;
drivers_license(Age) when Age == 17 ->
    'probationary license' ;
drivers_license(Age) when Age >= 65 ->
    'vision test recommended but not required' ;
drivers_license(_) ->
    'full license'.

fact(0) ->
   1;
fact(N) when N>0 ->
  N * fact(N-1).

ffact(0,A) ->    
    A;
ffact(N,A) ->
    ffact(N-1,N*A).
 
abt() ->
   {node, {node, {leaf, 3}, {leaf, 4}}, {leaf, 5}}.
   
size_tree({leaf,_}) ->
    1;
size_tree({node,L,R}) ->
    1+size_tree(L)+size_tree(R).

mirror({leaf,X}) ->
    {leaf,X};
mirror({node,L,R}) ->
    {node,mirror(R),mirror(L)}.

mapt(F,{leaf,X}) ->
    {leaf, F(X)};
mapt(F,{node,LT,RT}) ->
    {node,mapt(F,LT),mapt(F,RT)}.

mapL(_F,[]) ->
    [];
mapL(F,[H|T]) ->
     [F(H)|mapL(F,T)].

foldL(_F,A,[]) ->
    A;
foldL(F,A,[H|T]) ->
   foldL(F,F(A,H),T).




-type gtree() :: {node, number(), [gtree()]}.

-spec agt() -> gtree().

agt() ->
    {node, 1, [{node, 2, []}, {node, 3, []}]}