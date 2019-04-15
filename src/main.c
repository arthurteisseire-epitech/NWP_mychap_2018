/*
** EPITECH PROJECT, 2018
** mychap
** File description:
** main.c
*/

#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>

struct iphdr ipv4_header(unsigned short data_len)
{
    struct iphdr header = {0};

    header.version = 4;
    header.ihl = 5;
    header.tot_len = data_len + header.ihl * 4;
    return header;
}

int main(void)
{
    struct iphdr ip_header = ipv4_header(0);

    write(1, &ip_header, sizeof(ip_header));
    return 0;
}
