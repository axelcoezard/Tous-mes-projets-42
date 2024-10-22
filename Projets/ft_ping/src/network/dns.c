/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:16:58 by acoezard          #+#    #+#             */
/*   Updated: 2023/09/05 13:45:27 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool_t	dns_lookup(ping_t* ping, char* ip, const char* host) {
	struct addrinfo hints, *res, *result;
	void *ptr;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;

	if (getaddrinfo(host, NULL, &hints, &result) != 0 || result == NULL) {
		return false;
	}

	res = result;
	while (res)
	{
		inet_ntop(res->ai_family, res->ai_addr->sa_data, ip, 100);
		if (res->ai_family == AF_INET) {
			ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
			inet_ntop(res->ai_family, ptr, ip, 100);
			break;
		}

		ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
		inet_ntop(res->ai_family, ptr, ip, 100);
		res = res->ai_next;
	}

	bool_t found = res != 0;
	ping->res = res;
	freeaddrinfo(result);
	return found;
}

bool_t	dns_reverse_lookup(ping_t* ping) {
	char sbuf[NI_MAXSERV];
	struct sockaddr_in tmp_addr;
	tmp_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ping->destination_ip, &tmp_addr.sin_addr.s_addr);
	return getnameinfo((struct sockaddr*) &tmp_addr, (socklen_t) sizeof(tmp_addr), ping->destination_reverse, sizeof(ping->destination_reverse), sbuf, sizeof(sbuf), NI_NAMEREQD) == 0;
}

bool_t	dns_validate(char *ipAddress) {
	struct sockaddr_in sa;
	return inet_pton(AF_INET, ipAddress, &(sa.sin_addr)) > 0;
}
