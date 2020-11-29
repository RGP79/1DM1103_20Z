DEPS=main.o calc.o file.o

main: $(DEPS)
	valgrind	cc $(DEPS) -o $@ -lm -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f zad6
	rm -f *.o

test: main
	./main norm A.txt