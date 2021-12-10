datatype Dinheiro =
  Real of real
| Centavos of int
| Pessoa_Dinheiro of string * real;

fun
  amount(Real x) =  floor(x * 100.0)
| amount(Centavos x) = x
| amount(Pessoa_Dinheiro(_, x)) = floor(x * 100.0);

val d = Real(2.0);
amount(d);
val d = Centavos(2);
amount(d);
val d = Pessoa_Dinheiro("Gene", 2.5);
amount(d);