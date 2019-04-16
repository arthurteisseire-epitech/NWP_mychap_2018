/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** main.c
*/

#include <unistd.h>
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
    header.tot_len = data_len + header.ihl * 4;
    header.id = htons(2000);
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
    header.uh_dport = htons(2002);
    header.len = htons(sizeof(struct udphdr));
    return header;
}

int main(void)
{
    struct iphdr ip_header = ipv4_header(0, "127.0.0.1", "127.0.0.1");
    struct udphdr udp_header = create_udp_header();
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    int optval = 1;

    setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));
    write(1, &ip_header, sizeof(ip_header));
    write(1, &udp_header, sizeof(udp_header));
    return 0;
}
