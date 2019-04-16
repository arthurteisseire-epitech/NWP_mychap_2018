/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** main.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include "chap.h"

int main(void)
{
    size_t size = sizeof("client hello");
    packet_t *packet = create_packet(size, "client hello");
    int fd = init_socket();
    struct sockaddr_in info = init_addr(packet->ip.daddr);
    char buffer[4096];
    struct udphdr *udp;
    size_t nb_bytes;

    sendto(fd, packet, sizeof(struct iphdr) + sizeof(struct udphdr) + size, 0,
        (struct sockaddr *)&info, sizeof(info));
    do {
        nb_bytes = recv(fd, buffer, 4096, 0);
        if (nb_bytes == 0) {
            perror("recv");
            return 84;
        }
        udp = (void *)buffer + sizeof(struct iphdr);
    } while (ntohs(udp->uh_sport) != 2000);
    write(1, buffer, nb_bytes);
    return 0;
}
