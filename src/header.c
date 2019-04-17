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

static unsigned short check_sum(unsigned char *buf, int nwords)
{
    unsigned long sum;

    for (sum = 0; nwords > 0; --nwords)
        sum += *buf++;
    sum = (sum >> 16u) + (sum & 0xffffu);
    sum += (sum >> 16u);
    return ~sum;
}

static struct iphdr ipv4_header(unsigned short data_len)
{
    struct iphdr header = {0};

    header.version = 4;
    header.ihl = 5;
    header.tos = 16;
    header.tot_len = data_len + sizeof(struct iphdr) + sizeof(struct udphdr);
    header.id = htons(54321);
    header.frag_off = 0;
    header.ttl = 64;
    header.protocol = IPPROTO_UDP;
    header.check = 0;
    return header;
}

static struct udphdr create_udp_header(size_t data_len)
{
    struct udphdr header;

    header.uh_sport = htons(2001);
    header.check = 0;
    header.len = htons(sizeof(struct udphdr) + data_len);
    return header;
}

packet_t *create_packet(size_t data_len, char data[data_len])
{
    packet_t *packet = malloc(sizeof(packet_t) + data_len);

    packet->ip = ipv4_header(data_len);
    packet->udp = create_udp_header(data_len);
    memcpy(packet->data, data, data_len);
    packet->ip.check = check_sum((void *)packet,
        sizeof(struct iphdr) + sizeof(struct udphdr) + data_len);
    return packet;
}
