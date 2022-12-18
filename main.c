#include "termcolor-c.h"
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
  Films *films = (Films *)malloc(sizeof(Films));
  films->size = 0;
  films->current = NULL;
  return films;
}

// Добавление нового фильма в список
Film *add_film(Films *ring) {
  Film *previous = NULL;
  Film *film = (Film *)malloc(sizeof(Film));

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
Films *get_films_from_file(const char *filename) {
  FILE *films_txt = fopen(filename, "r");
  Films *films = create_films_ring();
  if (films_txt == NULL) {
    return films;
  }

  fseek(films_txt, 0, SEEK_END);
  long size = ftell(films_txt);
  if (0 == size) {
    return films;
  }
  fseek(films_txt, 0, SEEK_SET);

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

// Вывод полного двусвязного списка для наглядности того, что все действительно
// работает
void print_circle(Films *films) {
  Film *film = films->current;
  do {
    printf("%s\n%d\n%s\n%s\n%.1f\n", film->title, film->year, film->countries,
           film->genres, film->rating);
    film = film->next;
  } while (films->current != film);
}

size_t get_len(const char *string) {
  size_t size = 0;
  char byte;
  for (int i = 0;; i++) {
    byte = string[i];
    if (byte == '\0') {
      return size;
    }
    size += (((byte & 0x80) == 0) || ((byte & 0xC0) == 0xC0));
  }
}

// Вывод линий с информацией о фильме.
void print_line_with_spaces(const char *string, const char position) {
    int title_length = get_len(string), title_spaces;
    if (!position) {
        title_spaces = (46 - title_length) / 2;
    } else {
        title_length /= 2;
        if (title_length % 2 == 0) title_length++;
        title_spaces = (23 - title_length) / 2;
    }
    
    if (position != 2) printf("║");
    for (int j = 0; j < title_spaces; j++) printf(" ");
    
    text_red(stdout);
    if (!position) printf("%s", string);
    else for (int j = 0; j < title_length; j++) printf("*");
    text_blue(stdout);

    if (!position && title_length % 2 != 0) title_spaces++; 
    else if (position && title_length % 2 == 0) title_spaces++;
    for (int j = 0; j < title_spaces; j++) printf(" ");

    if (position != 1) printf("║");
    
}

// Вывод карусели
void print_cards(Film *film) {
  text_bold(stdout);
  text_blue(stdout);
  printf("                        ╔══════════════════════════════════════════════╗");
  printf("                        \n                        ");
  printf("║                                              ║");
  printf("                        \n                        ");
  printf("║                                              ║");
  printf("                        \n╔═══════════════════════");
  print_line_with_spaces(film->title, 0);
  printf("═══════════════════════╗\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n");
  print_line_with_spaces(film->prev->title, 1);
  print_line_with_spaces(film->genres, 0);
  print_line_with_spaces(film->next->title, 2);
  printf("\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n");
  print_line_with_spaces(film->prev->genres, 1);
  print_line_with_spaces(film->countries, 0);
  print_line_with_spaces(film->next->genres, 2);
  printf("\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n");
  print_line_with_spaces(film->prev->countries, 1);
  printf("║                     %.1f                      ║", film->rating);
  print_line_with_spaces(film->next->countries, 2);
  printf("\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n║          ***          ");
  printf("║                                              ║");
  printf("          ***          ║\n║                       ");
  printf("║                                              ║");
  printf("                       ║\n╚═══════════════════════");
  printf("║                     %d                     ║", film->year);
  printf("═══════════════════════╝\n                        ");
  printf("║                                              ║");
  printf("                        \n                        ");
  printf("║                                              ║");
  printf("                        \n                        ");
  printf("╚══════════════════════════════════════════════╝\n");
  reset_colors(stdout);
}

void print_gigachad() {
  printf("╔══════════════════════════════╗\n");
  printf("║⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠛⠋⠉⠈⠉⠉⠉⠉⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⡏⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿║\n");
  printf("║⣿⣿⣿⢏⣴⣿⣷⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿║\n");
  printf("║⣿⣿⣟⣾⣿⡟⠁⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣷⢢⠀⠀⠀⠀⠀⠀⠀⢸⣿║\n");
  printf("║⣿⣿⣿⣿⣟⠀⡴⠄⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⣿║\n");
  printf("║⣿⣿⣿⠟⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⢴⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⣿║\n");
  printf("║⣿⣁⡀⠀⠀⢰⢠⣦⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⡄⠀⣴⣶⣿⡄⣿║\n");
  printf("║⣿⡋⠀⠀⠀⠎⢸⣿⡆⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⠗⢘⣿⣟⠛⠿⣼║\n");
  printf("║⣿⣿⠋⢀⡌⢰⣿⡿⢿⡀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣧⢀⣼║\n");
  printf("║⣿⣿⣷⢻⠄⠘⠛⠋⠛⠃⠀⠀⠀⠀⠀⢿⣧⠈⠉⠙⠛⠋⠀⠀⠀⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣧⠀⠈⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⢀⢃⠀⠀⢸⣿⣿⣿⣿║\n");
  printf("║⣿⣿⡿⠀⠴⢗⣠⣤⣴⡶⠶⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡸⠀⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⡀⢠⣾⣿⠏⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠉⠀⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣧⠈⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠙⣿⣿⡟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠁⠀⠀⠹⣿⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⣿⣿⣿⣿║\n");
  printf("║⣿⣿⣿⣿⠿⠛⠉⠉⠁⠀⢻⣿⡇⠀⠀⠀⠀⠀⠀⢀⠈⣿⣿⡿⠉⠛⠛⠛⠉⠉║\n");
  printf("║⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄ ║\n");
  printf("╚══════════════════════════════╝\n");
}

int main() {
  Films *films = get_films_from_file("films.txt");
  int ch = 0;
  if (films->current != NULL) {
    // print_circle(films);
    Film *film = films->current;
    while (1) {
      system("clear");
      print_cards(film);
      printf("                             Переход между фильмами на кнопки A и D\n");
      system("/bin/stty raw");
      while (ch != 97 && ch != 100 && ch != 113) {
        ch = getchar();
      }
      system("/bin/stty cooked");
      if (ch == 97) {
        film = film->prev;
      } else if (ch == 100) {
        film = film->next;
      } else if (ch == 113) {
        break;
      }
      ch = 0;
    }
  } else {
    printf("Не удалось найти фильмы.\n");
  }
  system("clear");
  printf("            Пока-пока!\n");
  text_bold(stdout);
  text_green(stdout);
  print_gigachad();
  return 0;
}