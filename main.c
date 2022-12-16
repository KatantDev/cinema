#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <regex.h>
#include <ctype.h>

typedef struct {
    char login[24];
    char password[24];
    char card[20];
    int favorites_size;
    int is_admin;
} User;

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

void print_gigachad() {
  printf("╔═══════════════════════════════════╗\n");
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
  printf("║⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄⠄║\n");
  printf("╚═══════════════════════════════════╝\n");
}

User *get_user() {
    FILE *users_txt = fopen("users.txt", "r");
    User *user = (User*)malloc(sizeof(User));
    char user_input[24];

    regex_t regex;
    if (regcomp(&regex, "^[[:alpha:][:digit:]]{3,20}$", REG_EXTENDED)) {
        fprintf(stderr, "Не удалось скомпилировать regex-выражение.\n");
        exit(1);
    }

    while (1) {
        printf("Для входа или регистрации введите свой логин (от 3 до 20 символов) >> ");
        scanf("%s", user_input);

        if (regexec(&regex, user_input, 0, NULL, 0) == REG_NOMATCH) {
            printf("Логин должен состоять из латинских букв и цифр. И его длина должна быть в диапазоне 3-20 символов.\n");
            continue;
        }

        while (fgets(user->login, sizeof(user->login), users_txt)) {
            fgets(user->password, sizeof(user->password), users_txt);
            fgets(user->card, sizeof(user->card), users_txt);
            fscanf(users_txt, "%d\n", &user->is_admin);

            strtok(user->login, "\n");
            strtok(user->password, "\n");
            strtok(user->card, "\n");

            if (strcmp(user->login, user_input) == 0) {
                free(user_input);
                fclose(users_txt);
                return user;
            }
        }
        free(user);
        user = (User*)malloc(sizeof(User));
        strcpy(user->login, user_input);
        return user;
    }
}

char auth(User* user) {
    char *password = (char*)calloc(20, sizeof(password));
    printf("Вход в аккаунт %s.\nВведите пароль >> ", user->login);
    scanf("%s", password);
    if (strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void save_user(User *user) {
    FILE *users_txt = fopen("users.txt", "a");
    fprintf(users_txt, "%s\n", user->login);
    fprintf(users_txt, "%s\n", user->password);
    fprintf(users_txt, "%s\n", user->card);
    fprintf(users_txt, "%d\n", user->is_admin);
    fclose(users_txt);
}

void sign_up(User* user) {
    regex_t regex;
    if (regcomp(&regex, "^[[:digit:]]{16}$", REG_EXTENDED)) {
        fprintf(stderr, "Не удалось скомпилировать regex-выражение.\n");
        exit(1);
    }

    printf("Регистрация аккаунта с логином %s.\n", user->login);
    while (1) {
        printf("Введите пароль для аккаунта (от 6 до 20 символов) >> ");
        scanf("%s", user->password);
        int has_lowercase = 0, has_uppercase = 0, has_number = 0;
        for (int i = 0; i < strlen(user->password); i++) {
            if (islower(user->password[i])) has_lowercase++;
            if (isupper(user->password[i])) has_uppercase++;
            if (isdigit(user->password[i])) has_number++;
        }
        if (has_lowercase && has_uppercase && has_number && strlen(user->password) > 6) break;
        else
            printf("Пароль должен содержать хотя бы одну латинскую букву в верхнем и нижнем регистре. "
                   "И его длина должна быть в диапазоне от 3 до 20 символов\n");;
    }
    printf("Ваш будущий пароль для входа в аккаунта %s: %s\n", user->login, user->password);

    while (1) {
        printf("Введите номер карты без пробелов >> ");
        scanf("%s", user->card);
        if (regexec(&regex, user->card, 0, NULL, 0) == REG_NOMATCH)
            printf("Номер карты не должен содержать лишних символов и содержать только цифры. Длина должна составлять 16 цифр.\n");
        else break;
    }

    char filename[36] = "favorites/";
    strcat(filename, user->login);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "w");
    fclose(file);

    user->favorites_size = 0;
    user->is_admin = 0;
    save_user(user);
}

int main() {

    setlocale(LC_ALL, "Russian");
    Films *films = get_films_from_file("films.txt");
    printf("Приветствую тебя в онлайн-кинотеатре.\n");
    while (1) {
        User *user = get_user();
        if (!strlen(user->password)) {
            system("clear");
            sign_up(user);
        }
        system("clear");
        if (!auth(user)) {
            printf("Введён неверный пароль. Попробуйте войти снова.\n");
            free(user);
            continue;
        }
        break;
    }

    system("clear");
    printf("Вы успешно вошли в систему! Скоро здесь будет меню навигации.\n");

    return 0;
}