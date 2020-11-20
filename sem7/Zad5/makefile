DEPS=main.o dziekanat.o studenci.o

main: $(DEPS)
	cc $(DEPS) -o $@ -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f main
	rm -f *.o

test: main
	./main studenci.txt najlepszy_student