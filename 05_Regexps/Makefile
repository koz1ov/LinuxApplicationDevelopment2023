esub: esub.c
	gcc $< -o $@

test: esub
	./esub "a.*" "\0\0\0" abcdef > esub.tmp
	echo abcdef | sed -E 's/a.*/\0\0\0/' > sed.tmp
	diff esub.tmp sed.tmp
	
	./esub "z.*" "sdfsdfsf" abcdef > esub.tmp
	echo abcdef | sed -E 's/z.*/sdfsdfsf/' > sed.tmp
	diff esub.tmp sed.tmp
	
	./esub "([0-9]+)([a-z]+)([0-9]+)" "\0\2\3\3\1" "123sfs123df3fsddf423dsfs23423sdf" > esub.tmp
	echo '123sfs123df3fsddf423dsfs23423sdf' | sed -E 's/([0-9]+)([a-z]+)([0-9]+)/\0\2\3\3\1/' > sed.tmp
	diff esub.tmp sed.tmp
	
	./esub "([0-9]+)([a-z]+)([0-9]+)" "" "123sfs123df3fsddf423dsfs23423sdf" > esub.tmp
	echo '123sfs123df3fsddf423dsfs23423sdf' | sed -E 's/([0-9]+)([a-z]+)([0-9]+)//' > sed.tmp
	diff esub.tmp sed.tmp
clean:
	rm -f *.tmp esub
