/*will not compile*/
/*weather(City, Season, Temp).*/
  
weather(pheonix, summer, hot).
weather(la, summer, warm).
weather(pheonix, winter, warm).

warmer_than(C1,C2) :-
  weather(C1,hot, summer),
  weather(C2,warm,summer),
  write(C1), write ('is warmer than'), write(C2), nl.