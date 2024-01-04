/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:42:11 by acoezard          #+#    #+#             */
/*   Updated: 2023/09/05 12:58:54 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <math.h>

#include <string.h>

#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>

typedef enum {false, true} bool_t;

typedef struct {
	char				key;
	char*				value;
} ping_option_t;

typedef struct {
	struct icmp			header;
	char*				message;
} ping_packet_t;

typedef struct {
	int					instance;
	int					size;

	struct sockaddr_in	sender;
	struct sockaddr_in	recipient;
} ping_socket_t;

typedef struct {
	int					pid;

	ping_option_t*		options[15];
	int					options_size;
	char*				destination;
	char				destination_ip[NI_MAXHOST];
	char				destination_reverse[NI_MAXHOST];
	struct addrinfo*	res;

	struct msghdr		message;
	struct iovec		iov[1];
	char				iov_buffer[100];

	int					argc;
	char**				argv;

	bool_t				print_version;
} ping_t;

typedef struct {
	double				min_rtt;
	double				max_rtt;
	double				avg_rtt;
	double				total_rtt;
	double				squared_total_rtt;
	double				mdev_rtt;
} ping_stats_t;

typedef struct timeval ping_timeval_t;

void*		ft_memset(void *s, int c, size_t n);
char*		ft_strcpy(char *dest, const char *src);
int			ft_atoi(const char *nptr);

void		ping_usage(char* exec);
void		ping_version(char* exec);
void		ping_free(ping_t* ping);
void 		ping_get_time(unsigned long* value);

bool_t		parse_all_options(ping_t* ping);

bool_t		ping_socket_init(ping_t* ping, ping_socket_t* socket);
int32_t		ping_socket_send(ping_socket_t* sock, ping_packet_t* packet, uint32_t packet_size);
int32_t		ping_socket_receive(ping_t* ping, ping_socket_t* sock);
uint32_t	ping_loop(ping_t* ping, ping_socket_t* sock);


bool_t		dns_lookup(ping_t* ping, char* ip, const char* host);
bool_t		dns_reverse_lookup(ping_t* ping);
bool_t		dns_validate(char *ipAddress);

#endif
