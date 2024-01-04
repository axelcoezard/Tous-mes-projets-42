/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:28:00 by acoezard          #+#    #+#             */
/*   Updated: 2023/09/05 13:25:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool_t ping_socket_init(ping_t* ping, ping_socket_t* sock) {
	ft_memset((char *) &sock->sender, 0, sizeof(sock->sender));
	sock->sender.sin_family = AF_INET;

	ft_memset((char *) &sock->recipient, 0, sizeof(sock->recipient));
	sock->recipient.sin_family = AF_INET;
	sock->recipient.sin_port = (uint16_t) 1025;

	if (inet_pton(AF_INET, ping->destination_ip, &(sock->recipient.sin_addr)) == 0) {
		return false;
	}

	if ((sock->instance = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1) {
		return false;
	}
	return true;
}

int32_t ping_socket_send(ping_socket_t* sock, ping_packet_t* packet, uint32_t packet_size) {
	return sendto(sock->instance, packet, packet_size, 0, (struct sockaddr*) &sock->recipient, sizeof(sock->recipient));
}

int32_t ping_socket_receive(ping_t* ping, ping_socket_t* sock) {
	ft_memset(&(ping->iov[0]), 0, sizeof(ping->iov[0]));
	ft_memset(&ping->message, 0, sizeof(ping->message));

	ping->iov[0].iov_base = ping->iov_buffer;
	ping->iov[0].iov_len = sizeof(ping->iov_buffer);

	ping->message.msg_name = NULL;
	ping->message.msg_namelen = 0;
	ping->message.msg_iov = ping->iov;
	ping->message.msg_iovlen = 1;
	ping->message.msg_control = NULL;
	ping->message.msg_controllen = 0;
	ping->message.msg_flags = 0;

	return recvmsg(sock->instance, &ping->message, 0);
}
