/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:11:16 by acoezard          #+#    #+#             */
/*   Updated: 2023/04/25 13:27:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void ping_usage(char* exec) {
	printf("Usage: %s [-DhnoqvV] [-c count] [-i interval] [-s packetsize] [-t ttl] destination\n", exec);
}

void ping_version(char* exec) {
	printf("%s utility, iputils-s20161105\n", exec);
}

void ping_free(ping_t* ping) {
	for (int i = 0; i < ping->options_size; i++) {
		free(ping->options[i]);
	}
}

void ping_get_time(unsigned long* value) {
	ping_timeval_t time;

	if (gettimeofday(&time, NULL) == -1) {
		fprintf(stderr, "failed getting time of day");
		return (void) (*value = 0L);
	}
	*value = time.tv_sec * 1000000 + time.tv_usec;
}
