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

typedef int (*arg_t)(packet_t *, char *);

int init_socket(void);

packet_t *create_packet(size_t size, char *data);
struct sockaddr_in init_addr(uint32_t daddr);

int parse_args(packet_t *packet, int ac, char **av);
int arg_target(packet_t *packet, char *optarg);
int arg_port(packet_t *packet, char *optarg);
int arg_password(packet_t *packet, char *optarg);

#endif
