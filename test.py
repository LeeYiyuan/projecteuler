def choose(n, k):
	if (n < 0 or k < 0 or k > n):
		return 0
	top = 1
	bottom = 1
	for i in range(1, k + 1):
		top *= n - i + 1
		bottom *= i
	return top / bottom

def p(n):
    count = 0
    for a in xrange(0, n - 1):
        for b in xrange(a + 1, n):
            count += 2 ** (b - a - 1)
    return count
    
for n in range(2, 27):
	print(str(n) + ", " + str(p(n)))
