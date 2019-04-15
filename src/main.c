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
    header[1] = 0b00011110;
    write(1, header, 2);
}

int main(void)
{
    ipv4_header();
    return 0;
}
