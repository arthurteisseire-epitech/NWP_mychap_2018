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
#include <openssl/sha.h>
#include "chap.h"

int receive(int fd, packet_t *packet)
{
    struct udphdr *udp;
    char buffer[4096];
    size_t nb_bytes;

    do {
        nb_bytes = recv(fd, buffer, 4096, 0);
        if (nb_bytes == 0) {
            perror("recv");
            exit(84);
        }
        udp = (void *)buffer + sizeof(struct iphdr);
    } while (ntohs(udp->uh_sport) != ntohs(packet->udp.uh_dport));
    write(1, buffer, nb_bytes);
    return 0;
}

static char *send_password(const chap_t *chap)
{
    (void)chap;
    return NULL;
}

int main(int ac, char *av[])
{
    size_t size = strlen("client hello");
    chap_t chap;
    int fd = init_socket();

    chap.packet = create_packet(size, "client hello");
    parse_args(&chap, ac, av);
    chap.info = init_addr(chap.packet);
    send_to(&chap, fd, size);
    receive(fd, chap.packet);
    send_password(&chap);
    sendto(fd, chap.packet, sizeof(packet_t) + size, 0,
        (struct sockaddr *)&chap.info, sizeof(chap.info));
    return 0;
}
