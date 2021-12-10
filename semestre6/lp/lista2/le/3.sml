datatype perimetro = 
RConst of real | 

PQuadrado   of perimetro | 

PCirculo    of perimetro |

PRetangulo  of 
perimetro * perimetro |

PTriangulo  of
perimetro * perimetro * perimetro;

(*---------------------------------*)

fun
eval(RConst x) = x |

eval(PQuadrado x) =
eval(x) * 4.0  |

eval(PCirculo  x) = 
6.28 * eval(x) |

eval(PRetangulo(x, y)) =
2.0 * eval(x) + 2.0 * eval(y)|

eval(PTriangulo(x, y, z)) =
eval(x) + eval(y) + eval(z);


(*-------------
val p  = PQuadrado(RConst 4.0);
val p2 = PCirculo(RConst 4.0);
val p3 = PTriangulo(RConst 4.0, RConst 3.0, RConst 2.0);

eval(p);
eval(p2);
eval(p3);
-------------------*)