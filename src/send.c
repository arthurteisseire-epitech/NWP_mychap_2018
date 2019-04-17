/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** send.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "chap.h"

void send_to(chap_t *chap, int fd, size_t data_size)
{
    if (sendto(fd, chap->packet, sizeof(packet_t) + data_size, 0,
        (struct sockaddr *)&chap->info, sizeof(chap->info)) == -1) {
        printf("No such hostname: 'nonexistent_hostname'\n");
        exit(84);
    }
}