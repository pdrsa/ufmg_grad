fun isSep(c) = Char.isSpace c 
orelse c = #","
orelse c = #"."
orelse c = #"-";

fun split(s) = 
String.tokens isSep s;

split("Bom dia,pra-voce");