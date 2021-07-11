s = set()
while True:
	try:
		s.add(input())
	except EOFError:
		print(len(s))
		break
