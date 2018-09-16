-module(bt).
-compile(export_all).

-type btree() :: {empty}
	      |  {node,number(),btree(),btree()}.

-spec at() -> btree().
at() ->
    {node,1,{node,2,{empty},{empty}},{node,3,{empty},{empty}}}.

-spec at2() -> btree().
at2() ->
    {node,1,
     {node,2,{empty},{empty}},
     {node,3,{empty},
      {node,3,{empty},{empty}}}}.


-spec all_empty(queue:queue()) -> boolean().
all_empty(Q) ->
    case queue:is_empty(Q) of
	true -> true;
	_ -> case queue:out(Q) of
		 {{value,{empty}},Q2} ->
		     all_empty(Q2);
		 _ -> false
	     end
    end.

-spec ich(queue:queue()) -> boolean().
ich(Q) ->
    {{value,T},Q2} = queue:out(Q),
    case T of
	{empty} -> all_empty(Q2);
	{node,_I,LT,RT} -> ich(queue:in(RT,queue:in(LT,Q2)));
	_ -> erlang:error("incorrect tree")
    end.

-spec ic(btree()) -> boolean().
ic(T) ->
    ich(queue:in(T,queue:new())).

