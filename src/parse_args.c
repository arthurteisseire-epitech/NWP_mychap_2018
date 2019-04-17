/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** parse_args.c
*/

#include <getopt.h>
#include <stdlib.h>
#include "chap.h"

static const struct option long_options[] = {
    {"target", required_argument, NULL, 't'},
    {"port", required_argument, NULL, 'p'},
    {"password", required_argument, NULL, 'P'},
    {0, 0, 0, 0}
};

static const arg_t args[] = {
    arg_target,
    arg_port,
    arg_password,
};

static int get_index(const char *shorts, char c)
{
    int i = 0;
    char *short_index = "0:1:2:";

    while (shorts[i] != c)
        i++;
    return (short_index[i] - '0');
}

int parse_args(chap_t *chap, int ac, char **av)
{
    const char *shorts = "t:p:P:";
    int opt_index = 0;
    char c;

    for (;;) {
        c = getopt_long(ac, av, shorts, long_options, &opt_index);
        if (c == -1)
            return 0;
        if (c == '?')
            exit(84);
        opt_index = get_index(shorts, c);
        if (optarg)
            args[opt_index](chap, optarg);
    }
}
