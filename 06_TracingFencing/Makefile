move: move.c

remove.so: remove.c
	gcc my_remove.c -shared -fPIC -o my_remove.so

test: move remove.so
	
	echo -e "sddf\nsdfsdf\n" > in_file
	echo -e "sddf\nsdfsdf\n" > in_file
	./move in_file out_file
	

clean:
	rm -f move remove.so *.test
