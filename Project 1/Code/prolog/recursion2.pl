size([], 0).
size([A|B], S) :-
  size(B, S2),
  S is 1+S2.
  
location([H|T], 0, H).
location([H|T], I, C) :-
  location(T, I2, C),
  I is 1+I2.
  

listeq([],[]).
listeq([H|T1], [H|T2]) :-
  listeq(T1,T2).
  
equal(A,A).

first([X|T],X).

sorted([]).
sorted([X]).
sorted([H1|T1]) :-
  sorted(T1),
  first(T1,H2),
  H1 =< H2.
  