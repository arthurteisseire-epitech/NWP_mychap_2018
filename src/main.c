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
    char buffer[4096];
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    int optval = 1;
    struct udphdr *udp;
    struct sockaddr_in info;
    size_t nb_bytes;

    info.sin_port = htons(2000);
    info.sin_addr.s_addr = packet->ip.daddr;
    info.sin_family = AF_INET;
    if (fd == -1) {
        perror("socket");
        return 84;
    }
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int)) == -1) {
        perror("setsockopt");
        return 84;
    }
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
