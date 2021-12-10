datatype btree =
Leaf |
Node of (btree * int * btree);

fun
sumAll(Leaf) = 0 |
sumAll(Node(x, v, y)) = 
sumAll(x) + sumAll(y) + v;

val t =
Node(Node(Leaf, 1, Leaf), 
6,
Node(Leaf, 12, Leaf));

sumAll(t);
