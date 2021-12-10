datatype Planeta = 
Mercurio | Venus | Terra | Marte |
Jupiter  | Saturno| Urano | Netuno;

fun
planetAge(x, Mercurio) =
floor((real(x) / 12.0) * 88.0)
|
planetAge(x, Venus) =
floor((real(x) / 12.0) * 225.0)
|
planetAge(x, Terra) =
floor((real(x) / 12.0) * 365.0)
|
planetAge(x, Marte) =
floor((real(x) / 12.0) * 687.0)
|
planetAge(x, Jupiter) =
floor((real(x) / 12.0) * 4332.0)
|
planetAge(x, Saturno) =
floor((real(x) / 12.0) * 10760.0)
|
planetAge(x, Urano) =
floor((real(x) / 12.0) * 30681.0)
|
planetAge(x, Netuno) =
floor((real(x) / 12.0) * 60190.0);

planetAge(24, Jupiter);
planetAge(24, Netuno);
planetAge(18, Mercurio);
planetAge(12, Terra);