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
#include <openssl/sha.h>
#include "chap.h"

static char *receive(int fd, chap_t *chap)
{
    struct udphdr *udp;
    char *buffer = malloc(4096);
    size_t nb_bytes;

    do {
        nb_bytes = recv(fd, buffer, 4096, 0);
        if (nb_bytes == 0) {
            perror("recv");
            exit(84);
        }
        buffer[nb_bytes] = 0;
        udp = (void *)buffer + sizeof(struct iphdr);
    } while (ntohs(udp->uh_sport) != ntohs(chap->packet->udp.uh_dport));
    return buffer + sizeof(packet_t);
}

static char *concat(const char *left, const char *right)
{
    char *res = calloc(1, 10 + strlen(right) + 1);

    strncpy(res, left, 10);
    strncpy(res + 10, right, strlen(right));
    return (res);
}

static char *sha256(const char *str, size_t nb_bytes)
{
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256_CTX sha256;
    char *output_buffer;

    if (!(output_buffer = calloc(1,
        sizeof(char) * ((SHA256_DIGEST_LENGTH * 2) + 1))))
        return (NULL);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, nb_bytes);
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(output_buffer + (i * 2), "%02x", hash[i]);
    output_buffer[64] = 0;
    return (output_buffer);
}

static void send_password(int fd, chap_t *chap, const char *random_bytes)
{
    char *str = concat(random_bytes, chap->password);
    char *hash = sha256(str, 10 + strlen(chap->password));

    init_packet(chap, hash);
    send_to(chap, fd, strlen(hash));
}

int main(int ac, char *av[])
{
    size_t size = strlen("client hello");
    chap_t chap;
    int fd = init_socket();
    char *rec;

    parse_args(&chap, ac, av);
    init_packet(&chap, "client hello");
    chap.info = init_addr(chap.packet);
    send_to(&chap, fd, size);
    rec = receive(fd, &chap);
    send_password(fd, &chap, rec);
    fd = init_socket();
    rec = receive(fd, &chap);
    if (strncmp(rec, "KO", 2) == 0)
        printf("KO\n");
    else
        printf("Secret: '%s'\n", rec);
    return 0;
}
