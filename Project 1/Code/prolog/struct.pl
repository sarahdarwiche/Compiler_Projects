course(

  cse340,
  day(mon,wed),
  time(11,12),
  prof(holton, bryce),
  coor500
  ).

course(

  cse340,
  day(mon,wed),
  time(11,12),
  prof(ivan,andersen),
  coor300
).

instructor(Instructor,Class) :-
    course(Class,
           _,
           _,
           Instructor,
           _).