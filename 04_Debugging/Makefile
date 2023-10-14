range: range.c
	gcc -g -O0 $< -o $@

test: range
	gdb --quiet --batch  --command=script1 ./range | grep "@@@" | cut -c 4- > test1.tmp
	diff test1 test1.tmp
	gdb --quiet --batch  --command=script2 ./range | grep "@@@" | cut -c 4- > test2.tmp
	diff test2 test2.tmp

clean:
	rm -f *.tmp range
