/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** space.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"

int my_strcmp(char *s1, char *s2, int size)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] && s2[i] && size > i)
        i = i + 1;
    if (s1[i] == '\0' && s2[i] == '\0')
        return (0);
    else
        return (s1[i] - s2[i]);
}