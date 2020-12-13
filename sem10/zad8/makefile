all:
	cc baza.c main.c -o mydb -Wall --pedantic

test: all
	./mydb baza.csv list_students

test-ilestud: all
	./mydb baza.csv count_students

test-ileprzed: all
	./mydb baza.csv count_courses

test-memory: all
	valgrind ./mydb baza.csv add_student_to_course 1DE1203 213769 4.5 damn

test-dodajstud: all
	./mydb baza.csv add_student Izabela Lecka 213769 leckaiza@wp.pl

test-dodajprzed: all
	./mydb baza.csv add_course 1DM1103 Matematyka 2020Z
	
test-dodajstuddoprzed: all
	./mydb baza.csv add_student_to_course 1DE1203 213769 4.5 damn

test-sortuj-stud-malejaco: all
	./mydb baza.csv sort_stud_descending

test-sort-stud-ros: all
	./mydb baza.csv sort_stud_ascending

test-sort-przed-kod: all
	./mydb baza.csv sort_course_code

test-filtr-przed: all
	./mydb baza.csv filter_courses 1DE2103

test-filtr-przed2: all
	./mydb baza.csv filter_courses2 000007

clean:
	rm -f mydb