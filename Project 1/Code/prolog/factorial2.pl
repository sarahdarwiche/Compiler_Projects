factorial(0,1).
  
factorial(A,B) :-  
           A > 0, 
           C is A-1,
           factorial(C,D),
           B is A*D. 

append([],A,A).

append([H|A],B,[H|C]) :-
  append(A,B,C).
  
rem(A,[A|B],B).

rem(A,[B|C],[B|D]) :-
  rem(A,C,D).
  
removeall(A,[],[]).

removeall(A,[A|B],C) :-
  removeall(A,B,C).

removeall(A,[B|C],[B|D]) :-
  removeall(A,C,D).
  
likes(dan,sally).
likes(sally,dan).
likes(josh,brittney).

dating(X,Y):-
  likes(X,Y),
  likes(Y,X).

friendship(X,Y):-
  likes(X,Y);
  likes(Y,X).
