fun concat(list) = foldr (op ^) "" list;

fun getF(l: (string * string) list) = 
	(map(fn x => #1 x) l);

fun getS(l: (string * string) list) = 
	(map(fn x => #2 x) l);

fun vconc(l: (string * string) list) =
	(concat (getF l), concat (getS l));