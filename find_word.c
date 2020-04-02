/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** brute_force.c
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return (i);
}

char *read_map(char *filepath)
{
    int size = 5000000;
    char *buffer = NULL;
    int fd = open(filepath, O_RDONLY);

    buffer = malloc(sizeof(char) * (size + 1));
    read(fd, buffer, size);
    close(fd);
    if (buffer == NULL)
        return (NULL);
    return (buffer);
}

char **str_to_world_array(char *first_letter, int lenght_word, int *a, char *buffer)
{
    int k = 0, i = 0, r = 0;
    char **a_position = NULL, *temp = NULL;
    char first_one = first_letter[0];

    a_position = malloc(sizeof(char * ) * *a + 1);
    while (r < *a) {
        temp = malloc(sizeof(char) * 25 + 1);
        while (buffer[i] != '\n' && buffer[i] != '\0') {
            temp[i] = buffer[i];
            i++;
        }
        buffer = &buffer[i+1];
        //printf("%d", lenght_word);
        if (my_strlen(temp) == lenght_word + 1 && temp[0] == first_one) {
            a_position[k] = temp;
            k++;
        }
        i = 0;
        r++;
    }
    k++;
    a_position[k] = NULL;
    //for (int i = 0; a_position[i] != NULL; i++)
    //        printf("%s\n", a_position[i]);
    return (a_position);
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

char *my_strdup(char *str)
{
    int len = my_strlen(str) + 1;

    char *newstr = malloc(sizeof(char) * len);
    if (newstr == NULL)
        return (NULL);
    newstr = my_strcpy(newstr, str);
    newstr[len - 1] = '\0';
    return (newstr);
}

int is_same_word(char *str1, char *str2, int size)
{
    int counter = 0;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (str1[j] != '%' && str2[i] != '%' && str1[j] == str2[i]){
                str1[j] = '%';
                str2[i] = '%';
            }
        }
    }
    for (int i = 0; i < size; i++){
        if (str1[i] != '%')
            return (0);
    }
    return (1);
}

int get_size_line(char *map)
{
    int i = 0, a = 0;

    while (map[i] != '\0') {
        if (map[i] == '\n')
            a++;
        i++;
    }
    return (a);
}

int sort_word(char *line_parsed, char *name)
{
    int i = 0, a = 0;

    while (line_parsed[i+1] != '\0') {
        if (line_parsed[i] < 97)
            line_parsed[i] = line_parsed[i] + 32;
        while (line_parsed[i] != name[a]) {
            if (name[a] == '\0')
                return (1);
            if (name[a] < 97)
                name[a] = name[a] + 32;
            a++;
        }
        if (line_parsed[i] == name[a]) {
            a = 0;
            i++;
        }
    }
    a = 0;
    i = 0;
    while (name[a] != '\0') {
        while (name[a] != line_parsed[i]) {
            if (line_parsed[i] == '\0')
                return (1);
            i++;
        }
        if (line_parsed[i] == name[a]) {
            i = 0;
            a++;
        }
    }
    return (0);
}

int compare_name(char **line_parsed, char *name)
{
    int i = 0, a = 0, j = 0, size = 0;
    char *save = NULL, *save2 = NULL;
    int word_size = my_strlen(name);

    while (line_parsed[a] != NULL) {
        size = my_strlen(line_parsed[a]);
        while (i < size) {
            if (my_strlen(name) != my_strlen(line_parsed[a] + 1))
                break;
            if (sort_word(line_parsed[a], name) == 0) {
                save = my_strdup(line_parsed[a]);
                save2 = my_strdup(name);
                if (is_same_word(save, save2, word_size)) {
                    j++;
                    printf("%s\n", line_parsed[a]);
                }
                break;
            }
            else
                break;
        }
        i = 0;
        a++;
    }
    if (j == 0)
        printf("No words found..\n");
    return (0);
}

void viderBuffer()
{
    int c = 0;

    while (c != '\n' && c != EOF)
        c = getchar();
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
            *positionEntree = '\0';
        else
            viderBuffer();
        return 1;
    }
    else {
        viderBuffer();
        return 0;
    }
}

long lire_long()
{
    char nombreTexte[100] = {0};

    if (lire(nombreTexte, 100))
        return strtol(nombreTexte, NULL, 10);
    else
        return 0;
}

int check_entire_word(char *found_letter, char *argv_parsed)
{
    int r = 0;
    int i = 0;

    while (i < my_strlen(argv_parsed)) {
        if (argv_parsed[i] == found_letter[r]) {
            i = 0;
            if (r + 2 < my_strlen(found_letter))
                r += 2;
            else
                return (1);
        }
        i++;
    }
    return (0);
}

int sort_every_word(char **arg_parsed, char *found_letter)
{
    int a = 0;
    char **find_word_parsed = NULL;
    int k = 0;
    int bol = 0;

    find_word_parsed = malloc(sizeof(char *) * 100000);
    for (int i = 0; arg_parsed[i] != NULL; i++) {
        while (a < my_strlen(arg_parsed[i])) {
            if (arg_parsed[i][a] == found_letter[0] && bol == 0) {
                if (check_entire_word(found_letter, arg_parsed[i])) {
                    find_word_parsed[k] = arg_parsed[i];
                    k++;
                    bol = 1;
                    break;
                }
            }
            a++;
        }
        a = 0;
        bol = 0;
    }
    find_word_parsed[k] = NULL;
    for (int i = 0; find_word_parsed[i] != NULL; i++)
        printf("%s\n", find_word_parsed[i]);
}

int brute_force(char *map)
{
    int i = get_size_line(map); //total nombre de mot
    char **arg_parsed = NULL;
    int lenght_word = 0;
    char first_letter[2];
    char found_letter[100];

    printf("quelle longueur fait le mot (ex : 1, 2, 5..) : ");
    lenght_word = lire_long();
    //printf("%d\n", lenght_word);
    printf("quelle est la premiere lettre du mot : ( a, b, c..) : ");
    lire(first_letter, 2);
    //printf("%s\n", first_letter);
    arg_parsed = str_to_world_array(first_letter, lenght_word, &i, map);
    for (int i = 0; arg_parsed[i] != NULL; i++)
        printf("%s\n", arg_parsed[i]);
    while (1) {
        printf("quelle lettre il y a dans ton mot (ex : a:e:i:r ) : ");
        lire(found_letter, 100);
        //printf("%s\n", found_letter);
        sort_every_word(arg_parsed, found_letter);
    }
    return (0);
}

void help()
{
    printf("    USAGE\n");
    printf("gcc find_word\n");
    printf("./a.out [DICO] [WORDS_TO_SEARCH]\n       --------------\n");
    printf("example : ./a.out liste_francais.txt rreoad");
    printf("\nname : adorer\n");
}

int main(int ac, char **argv)
{
    char *map = NULL;

    if (argv[1][0] == '-' && argv[1][1] == 'h') {
        help();
        return (84);
    }
    if (ac != 2)
        return 84;
    map = read_map(argv[1]);
    if (map == NULL)
        return (84);
    brute_force(map);
}