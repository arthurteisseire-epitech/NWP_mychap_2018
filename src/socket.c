/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** socket.c
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include "chap.h"

int init_socket(void)
{
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    int optval = 1;

    if (fd == -1) {
        perror("socket");
        exit(84);
    }
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(84);
    }
    return fd;
}

struct sockaddr_in init_addr(packet_t *packet)
{
    struct sockaddr_in info;

    info.sin_port = packet->udp.uh_dport;
    info.sin_addr.s_addr = packet->ip.daddr;
    info.sin_family = AF_INET;
    return info;
}
