all: clean full

executavel: src/main.c src/validadorDeInput.h src/simplex.h
	gcc -o $@ $^

.PHONY: clean full

full: executavel

clean: 
	rm -f executavel
