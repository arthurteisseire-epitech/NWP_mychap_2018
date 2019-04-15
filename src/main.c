/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** main.c
*/

#include <unistd.h>

void ipv4_header()
{
    unsigned char header[20];

    header[0] = (4u << 4u) | 5u;
    write(1, header, 1);
}

int main(void)
{
    ipv4_header();
    return 0;
}
