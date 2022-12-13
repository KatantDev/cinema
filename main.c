#include <stdio.h>
#include <string.h>

// Считываем данные о фильмах из файла.
void get_films_from_file(const char *filename) {
    FILE *films_txt = fopen(filename, "r");
    if (films_txt == NULL) {
        printf("Ошибка: отсутствует файл с фильмами.\n");
        return;
    }

    char title[96];
    int year;
    char countries[64];
    char genres[64];
    float rating;

    while (!feof(films_txt)) {
        fgets(title, sizeof(title), films_txt);
        fscanf(films_txt, "%d\n", &year);
        fgets(countries, sizeof(countries), films_txt);
        fgets(genres, sizeof(genres), films_txt);
        fscanf(films_txt, "%f\n", &rating);

        strtok(title, "\n");
        strtok(countries, "\n");
        strtok(genres, "\n");


        printf("%s\n%d\n%s\n%s\n%.1f\n\n", title, year, countries, genres, rating);
    }
    fclose(films_txt);
}

int main() {
    get_films_from_file("./films.txt");
    return 0;
}