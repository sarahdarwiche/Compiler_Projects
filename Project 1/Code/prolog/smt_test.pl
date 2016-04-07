%List = ([pair(Y, int), pair(Y, int), pair(plus(Y, Y), int)]).
%Front = (['declare-const ']).

change(pair, ' ').
change(plus(Y, Y), 'declare fun plus').
change(pair(Y, ints), 'declare const y ints').
change(pair(Z, ints), 'declare const z ints').
change(X,X).
%change(predicate(pair), string).

alter([],[]).
alter([H|T],[X,Y]) :- change(H,X), alter(T,Y).

#alter([],[]).
#change(X,X). #catch all
#alter([H|T],[X,Y]) :- change(H,X), alter(T,Y).

append([],L,L).
append([X|L1],L2,[X|L3]):- append(L1, L2, L3).
atom("declare-const ").

