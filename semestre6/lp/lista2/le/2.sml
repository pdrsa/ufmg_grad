datatype area = 
RConst of real | 
AQuadrado   of area | 
ACirculo    of area |
ARetangulo  of area * area;


fun
eval(RConst x) = x |

eval(AQuadrado x) =
eval(x) * eval(x)  |

eval(ACirculo  x) = 
3.14 * eval(x) * eval(x) |

eval(ARetangulo(x, y)) =
eval(x) * eval(y);


(*-----------------
val e  = ACirculo(RConst 2.0);
val e2 = AQuadrado(RConst 2.0);
val e3 = ARetangulo(RConst 2.0, RConst 3.0);

eval(e);
eval(e2);
eval(e3);
-------------------*)