fun pow (x, 0)  = 1
|   pow (x, y) = x * pow(x, y-1);

pow(5, 2);
pow(5, 3);
pow(5, 4);