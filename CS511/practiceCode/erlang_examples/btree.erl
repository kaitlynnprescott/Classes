-module (btree).
-compile(export_all).

isComplete({empty}) ->
	true;
isComplete({node, X, LT, RT}) ->
	Nodes = countNodes({node, X, LT, RT}),
	isComplete(LT, 0, Nodes) and isComplete(RT, 0, Nodes).

isComplete({empty}, Index, Count) -> 
	if 
		Index >= Count ->
			false;
		true ->
			true
	end;

isComplete({node, _X, LT, RT}, Index, Count) ->
	%%%
	if 
		Index >= Count ->
			false;
		true ->
			(isComplete(LT, 2*Index+1, Count) and isComplete(RT, 2*Index+2, Count))
	end.

countNodes({empty}) ->
	0;
countNodes({node, _X, LT, RT}) ->
	1+countNodes(LT)+countNodes(RT).
