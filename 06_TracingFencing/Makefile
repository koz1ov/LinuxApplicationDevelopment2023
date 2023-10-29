move: move.c

remove.so: remove.c
	gcc remove.c -shared -fPIC -o remove.so

test: move remove.so
	
	# happy path
	yes "Some text" | head -n 1000 > check.test
	cp check.test in_file.test
	./move in_file.test out_file.test
	test ! -s in_file.test
	diff out_file.test check.test	
	
	# LD_PRELOAD
	cp check.test PROTECTED_in.test
	LD_PRELOAD=./remove.so ./move PROTECTED_in.test out_file.test
	test -s PROTECTED_in.test
	diff out_file.test check.test
	diff PROTECTED_in.test check.test
	rm out_file.test
	
	# open input file fault
	cp check.test in_file.test
	strace -e openat -P in_file.test -e fault=openat:error=EACCES \
	./move in_file.test out_file.test > /dev/null 2>&1 || test 2 = "$$?"
	test ! -s out_file.test
	
	# open output file fault
	cp check.test in_file.test
	strace -e openat -P out_file.test -e fault=openat:error=EACCES \
	./move in_file.test out_file.test > /dev/null 2>&1 ||  test 3 = "$$?"
	test ! -s out_file.test
	
	# read inupt file fault
	cp check.test in_file.test
	strace -e read -P in_file.test -e fault=read:error=EIO \
	./move in_file.test out_file.test > /dev/null 2>&1 || test 4 = "$$?"
	test -s in_file.test
	test ! -s out_file.test
	
	# write out file fault
	cp check.test in_file.test
	strace -e write -e fault=write:error=EIO \
	./move in_file.test out_file.test > /dev/null 2>&1 || test 5 = "$$?"
	test -s in_file.test
	test ! -s out_file.test
	
	# close out file fault
	cp check.test in_file.test
	strace -e close -e fault=close:error=EIO:when=4 \
  ./move in_file.test out_file.test > /dev/null 2>&1 || test 7 = "$$?"
	test -s in_file.test
	test ! -s out_file.test

clean:
	rm -f move remove.so *.test
