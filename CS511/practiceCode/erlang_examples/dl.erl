-module(dl).
-compile(export_all).

-spec driversLicense(number()) -> atom().

driversLicense(Age) when not(is_number(Age)) ->
	erlang:error('Arguement not a number');
driversLicense(Age) when Age < 16 ->
	forbidden;
driversLicense(Age) when Age == 16 ->
	'learners permit';
driversLicense(Age) when Age == 17 ->
	'probationary license';
driversLicense(Age) when Age >= 65 ->
	'vison test recommended but not requried';
driversLicense(_) -> 
	'full license'.