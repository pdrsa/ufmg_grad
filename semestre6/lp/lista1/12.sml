fun multiPairs(xH::xT, yH::yT) = if xT = [] then [xH*yH] else [xH*yH] @ multiPairs(xT, yT); 
multiPairs([2, 5, 10], [4, 10, 8]);