/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** chap.h
*/

#ifndef MYCHAP_CHAP_H
#define MYCHAP_CHAP_H

struct iphdr ipv4_header(unsigned short data_len, char *ip_s, char *ip_d);
struct udphdr create_udp_header(void);
unsigned short csum(unsigned short *buf, int nwords);

#endif
