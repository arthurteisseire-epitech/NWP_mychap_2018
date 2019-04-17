/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** arg_function.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include "chap.h"

int arg_target(chap_t *chap, char *optarg)
{
    if (strcmp(optarg, "localhost") == 0)
        chap->ip = inet_addr("127.0.0.1");
    else
        chap->ip = inet_addr(optarg);
    return 0;
}

int arg_port(chap_t *chap, char *optarg)
{
    char *p = strdup(optarg);
    char *end_ptr = p;
    int port = strtol(p, &end_ptr, 10);

    if (errno == 0 && p == end_ptr) {
        fprintf(stderr, "'%s' isn't a valid number\n", optarg);
        free(p);
        exit(84);
    }
    chap->port = port;
    free(p);
    return 0;
}

int arg_password(chap_t *chap, char *optarg)
{
    chap->password = optarg;
    return 0;
}
