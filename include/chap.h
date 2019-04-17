/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** chap.h
*/

#ifndef MYCHAP_CHAP_H
#define MYCHAP_CHAP_H

#include <netinet/ip.h>
#include <netinet/udp.h>

typedef struct __attribute((packed))packet_s {
    struct iphdr ip;
    struct udphdr udp;
    char data[0];
} packet_t;

typedef struct chap_s {
    char *password;
    packet_t *packet;
} chap_t;

typedef int (*arg_t)(chap_t *, char *);

int init_socket(void);

packet_t *create_packet(size_t size, char *data);
struct sockaddr_in init_addr(uint32_t daddr);

int parse_args(chap_t *chap, int ac, char **av);
int arg_target(chap_t *packet, char *optarg);
int arg_port(chap_t *packet, char *optarg);
int arg_password(chap_t *packet, char *optarg);

#endif
