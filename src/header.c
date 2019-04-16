/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** header.c
*/

#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "chap.h"

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
    header.check = 0;
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

packet_t *create_packet(size_t size, char data[size])
{
    packet_t *packet = malloc(sizeof(packet_t) + size);

    packet->ip = ipv4_header(size, "127.0.0.1", "127.0.0.1");
    packet->udp = create_udp_header();
    memcpy(packet->data, data, size);
    packet->ip.check = csum((void *)packet,
        sizeof(struct iphdr) + sizeof(struct udphdr) + 10);
    return packet;
}
