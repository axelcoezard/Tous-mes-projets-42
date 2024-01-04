/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:44:20 by acoezard          #+#    #+#             */
/*   Updated: 2023/09/05 13:47:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int argc, char** argv) {
	ping_t ping;
	ping.pid = getpid();
	ping.argc = argc;
	ping.argv = argv;
	ping.options_size = 0;
	ping.print_version = false;

	if (!parse_all_options(&ping)) {
		if (ping.print_version)	{ ping_version(argv[0]); }
		else					{ ping_usage(argv[0]); }
		return EXIT_FAILURE;
	}

	if (!dns_lookup(&ping, ping.destination_ip, ping.destination) && !dns_validate(ping.destination)) {
		printf("%s: %s: Name or service not known\n", argv[0], ping.destination);
		return EXIT_FAILURE;
	}

	if (!dns_reverse_lookup(&ping)) {
		ft_strcpy(ping.destination_reverse, ping.destination_ip);
	}

	ping_socket_t sock;
	if (!ping_socket_init(&ping, &sock)) {
		printf("%s: Socket failed to be initialized\n", argv[0]);
		return EXIT_FAILURE;
	}

	ping_loop(&ping, &sock);
	ping_free(&ping);

	return EXIT_SUCCESS;
}
