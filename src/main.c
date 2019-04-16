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

unsigned short csum(unsigned short *buf, int nwords)
{
    unsigned long sum;

    for (sum = 0; nwords > 0; --nwords)
        sum += *buf++;
    sum = (sum >> 16u) + (sum & 0xffffu);
    sum += (sum >> 16u);
    return ~sum;
}

struct iphdr ipv4_header(unsigned short data_len, char *ip_s, char *ip_d)
{
    struct iphdr header = {0};

    header.version = 4;
    header.ihl = 5;
    header.tos = 16;
    header.tot_len = data_len + sizeof(struct iphdr);
    header.id = htons(54321);
    header.frag_off = 0;
    header.ttl = 64;
    header.protocol = IPPROTO_UDP;
    header.saddr = inet_addr(ip_s);
    header.daddr = inet_addr(ip_d);
    header.check = csum((unsigned short *)&header, header.tot_len);
    return header;
}

struct udphdr create_udp_header(void)
{
    struct udphdr header;

    header.uh_sport = htons(2001);
    header.uh_dport = htons(2000);
    header.check = 0;
    header.len = htons(sizeof(struct udphdr));
    return header;
}

int main(void)
{
    struct iphdr ip_header = ipv4_header(0, "127.0.0.1", "127.0.0.1");
    struct udphdr udp_header = create_udp_header();
    char buffer[4096];
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    int optval = 1;
    struct udphdr *udp;
    void *p = malloc(sizeof(struct iphdr) + sizeof(struct udphdr) + 10);
    struct sockaddr_in info;

    info.sin_port = htons(2000);
    info.sin_addr.s_addr = ip_header.daddr;
    info.sin_family = AF_INET;

    if (fd == -1) {
        perror("socket");
        return 84;
    }
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int)) == -1) {
        perror("setsockopt");
        return 84;
    }
    memcpy(p, &ip_header, sizeof(struct iphdr));
    memcpy(p + sizeof(struct iphdr), &udp_header, sizeof(struct udphdr));
    memcpy(p + sizeof(struct iphdr) + sizeof(struct udphdr), "0123456789", 10);
    ((struct iphdr *)p)->check = csum(p, sizeof(struct iphdr) + sizeof(struct udphdr) + 10);
    sendto(fd, p, sizeof(struct iphdr) + sizeof(struct udphdr) + 10, 0, (struct sockaddr *)&info, sizeof(info));
    do {
        if (recv(fd, buffer, 4096, 0) == -1) {
            perror("recv");
            return 84;
        }
        udp = (void *)buffer + sizeof(struct iphdr);
    } while (ntohs(udp->uh_sport) != 2000);
    write(1, &buffer, sizeof(buffer));
    return 0;
}
