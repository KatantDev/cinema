#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Film {
    char title[96];
    int year;
    char countries[64];
    char genres[64];
    float rating;

    struct Film *prev;
    struct Film *next;
} Film;

typedef struct Films {
    int size;
    Film *current;
} Films;

// Создание кольцевого списка
Films *create_films_ring() {
    Films *films = (Films*)malloc(sizeof(Films));
    films->size = 0;
    films->current = NULL;
    return films;
}

// Добавление нового фильма в список
Film* add_film(Films *ring) {
    Film *previous = NULL;
    Film *film = (Film*)malloc(sizeof(Film));

    if (ring->current == NULL) {
        ring->current = film;
        film->next = film->prev = film;
    } else {
        previous = ring->current->next->prev;
        film->next = ring->current->next;
        film->prev = ring->current;
        previous->prev = film;

        ring->current->next = film;
        ring->current = film;
    }
    ring->size++;
    return film;
}

// Считываем данные о фильмах из файла
Films* get_films_from_file(const char *filename) {
    FILE *films_txt = fopen(filename, "r");
    if (films_txt == NULL) {
        printf("Ошибка: отсутствует файл с фильмами.\n");
        return NULL;
    }

    fseek(films_txt, 0, SEEK_END);
    long size = ftell(films_txt);
    if (0 == size) {
        printf("Ошибка: файл пуст.\n");
        return NULL;
    }
    fseek(films_txt, 0, SEEK_SET);

    Films* films = create_films_ring();
    while (!feof(films_txt)) {
        Film *film = add_film(films);
        fgets(film->title, sizeof(film->title), films_txt);
        fscanf(films_txt, "%d\n", &film->year);
        fgets(film->countries, sizeof(film->countries), films_txt);
        fgets(film->genres, sizeof(film->genres), films_txt);
        fscanf(films_txt, "%f\n", &film->rating);

        strtok(film->title, "\n");
        strtok(film->countries, "\n");
        strtok(film->genres, "\n");
    }
    fclose(films_txt);
    return films;
}

// Вывод полного двусвязного списка для наглядности того, что все действительно работает
void print_circle(Films* films) {
    Film *film = films->current;
    do {
        printf("%s\n%d\n%s\n%s\n%.1f\n", film->title, film->year, film->countries, film->genres, film->rating);
        film = film->next;
    }
    while (films->current != film);
}

int main() {
    Films *films = get_films_from_file("../films.txt");
    if (films != NULL) {
        print_circle(films);
    }
    return 0;
}