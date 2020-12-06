Struktury danych

----

* Listy dynamiczne (nr_albumu, student, imie, nazwisko) - jedno i dwukierunkowe
* Listy dynamiczne (kod_przedmiotu, przedmiot, nazwa, semestr) - jedno i dwukierunkowe
* Lista dynamiczna (zapisy i oceny) - nr_albumu, kod_przedmiotu, ocena, komentarz, data_wystawienia
* Głowa listy, ogon listy (NULL)
* Wstawianie, usuwanie, dodawanie, ile elementów



Program do zrobienia:

* Program obsługujący bazę danych (zakładamy, że mamy plik z bazą danych (wczytujemy do pamięci, potem wykonujemy operację i całość znowu zapisujemy do pliku))
* Operacje:
  * dodaj przedmiot (np. ./mydb add course 1DE2103 "Metody numeryczne" 2020Z)
  * dodaj studenta (np.: ./mydb add student )
  * dodaj studenta do przedmiotu (np.: ./mydb add student_to_course 123456 1DE1203)
  * wystaw ocenę studenta na przedmiocie (np.: ./mydb set_grade 123456 1DE1203 3.5 "Bardzo ładny projekt.")
  * oblicz średnią studenta (np.: ./mydb student_average 123456)
  * wyświetl listę studentów posortowanych alfabetycznie na przedmiocie (np.: ./mydb list_students 1DE2103)
  * oblicz średnią ocen na przedmiocie (np.: ./mydb course_average 1DE2103)
  * oblicze liczbę poszczególnych ocen na przedmiocie (np.: ./mydb course_grades 1DE2103)
  * wyświetl listę studentów
  * wyświetl listę przedmiotów

Proszę zaprojektować interfejs. Można użyć przykładu. Proszę napisać makefile zawierający między innymi co najmniej 3 przykłady testowe.



