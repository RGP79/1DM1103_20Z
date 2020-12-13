#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

int main(int argc, char ** argv) {
    SBaza *baza;
    baza = wczytaj_baze(argv[1]);

    if (strcmp("list_students", argv[2]) == 0) {
        listuj_studentow(baza);
    } else if (strcmp("add_student", argv[2]) == 0) {
        dodaj_studenta(baza, argv[3], argv[4], argv[5], argv[6]);
    } else if (strcmp("count_students", argv[2]) == 0) {
        printf("Liczba studentów: %d\n", ile_studentow(baza));
    } else if (strcmp("add_course", argv[2]) == 0){
        dodaj_przedmiot(baza, argv[3], argv[4], argv[5]);
    } else if (strcmp("count_courses", argv[2]) == 0) {
        printf("Liczba przedmiotow: %d\n", ile_przedmiotow(baza));
    } else if (strcmp("add_student_to_course", argv[2]) == 0) {
        dodaj_stud_do_przed(baza, argv[3], argv[4], argv[5], argv[6]);
    } else if (strcmp("sort_stud_descending", argv[2]) == 0) {
        baza->lista_studentow = sortuj_stud_przez_wybieranie(baza->lista_studentow); 
        listuj_studentow(baza);
    } else if (strcmp("sort_stud_ascending", argv[2]) == 0) {
        baza->lista_studentow = sortuj_stud_przez_wybieranie(baza->lista_studentow); 
        listuj_studentow_od_konca(baza);
    } else if (strcmp("sort_course_code", argv[2]) == 0) {
        baza->lista_przedmiotow = sortuj_przed_przez_wybieranie_kod(baza->lista_przedmiotow); 
        listuj_przedmioty_od_konca(baza);
    } else if (strcmp("sort_course_name", argv[2]) == 0) {
        baza->lista_przedmiotow = sortuj_przed_przez_wybieranie_nazwa(baza->lista_przedmiotow); 
        listuj_przedmioty_od_konca(baza);
    } else if (strcmp("filter_courses", argv[2]) == 0) {
        baza->lista_ocen = filtruj_przedmiot(baza->lista_ocen, argv[3], baza);
        listuj_oceny(baza);
    } else if (strcmp("filter_courses2", argv[2]) == 0) {
        baza->lista_ocen = filtruj_przedmiot2(baza->lista_ocen, argv[3], baza);
        listuj_oceny(baza);
    }
    zapisz_baze(argv[1], baza);
    zwolnij(baza);

    return 0;
}