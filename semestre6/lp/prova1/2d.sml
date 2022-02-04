fun f l1 l2 =
	case l1 of
		nil => l2
		| (h::t) => f t ([h] @ l2);
fun g l = f l [];