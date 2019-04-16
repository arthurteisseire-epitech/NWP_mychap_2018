/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** chap.h
*/

#ifndef MYCHAP_CHAP_H
#define MYCHAP_CHAP_H

typedef struct __attribute((packed))packet_s {
    struct iphdr ip;
    struct udphdr udp;
    char data[0];
} packet_t;

int init_socket(void);
struct iphdr ipv4_header(unsigned short data_len, char *ip_s, char *ip_d);
struct udphdr create_udp_header(void);
unsigned short csum(unsigned short *buf, int nwords);

packet_t *create_packet(size_t size, char *data);
struct sockaddr_in init_addr(uint32_t daddr);

#endif
