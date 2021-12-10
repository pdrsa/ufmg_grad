fun allTrue(h::t) =
h andalso allTrue(t) |
allTrue([]) = true;

allTrue([true, true, true]);
allTrue([true, false, true]);