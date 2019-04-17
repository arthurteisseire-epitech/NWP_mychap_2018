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
    packet_t *packet;
    struct sockaddr_in info;
    char *password;
    int port;
    in_addr_t ip;
} chap_t;

typedef int (*arg_t)(chap_t *, char *);

int init_socket(void);

void init_packet(chap_t *chap, char *data);
struct sockaddr_in init_addr(packet_t *packet);

int parse_args(chap_t *chap, int ac, char **av);
int arg_target(chap_t *packet, char *optarg);
int arg_port(chap_t *packet, char *optarg);
int arg_password(chap_t *packet, char *optarg);

void send_to(chap_t *chap, int fd, size_t data_size);

#endif
