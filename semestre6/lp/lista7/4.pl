del3([],[]).
del3([X],[X]).
del3([X,Y],[X,Y]).
del3([X,Y,_|T],[X,Y|T]).
