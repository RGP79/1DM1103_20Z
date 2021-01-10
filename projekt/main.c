#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

char * make_request(char *url)
{
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            printf("%s\n", chunk.response);
        }

        /* zawsze po sobie sprzątaj */
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    return 0;
}

// void plansza (Memory chunk)
// {    
//     char* w;
//     strncpy(w, chunk.response, 1024);
//     w = strtok(NULL, "HTTP/1.0 200 OK Content-Type: application/json Content-Length: 149 Access-Control-Allow-Origin: * Server: Werkzeug/1.0.1 Python/3.6.9 Date: Sat, 09 Jan 2021 16:14:55 GMT");
//     printf("%s", w);
// }

void info(char *token) {
char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_22";
make_request(url);
}

void move(char *token) {
char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_22";
make_request(url);
}

void explore(char *token) {
char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_22";
make_request(url);
}

void left(char *token) {
char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_22/left";
make_request(url);
}

void right(char *token) {
char *url = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_22/right";
make_request(url);
}

int main(int argc, char **argv){
    char *token="qwerty_22";
    // Memory chunk;
    // Memory *chunk = (Memory*) malloc(sizeof(Memory));

    for(int i=1; i<argc;i++){
        if(strcmp(argv[i], "i") == 0){
        info(token);
        }
        if(strcmp(argv[i], "e") == 0){
        explore(token);
        // plansza(*chunk);
        }
        if(strcmp(argv[i], "r") == 0){
        right(token);
        }
        if(strcmp(argv[i], "m") == 0){
        move(token);
        }
        if(strcmp(argv[i], "l") == 0){
        left(token);
        }
    }    
}