/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:44:42 by acoezard          #+#    #+#             */
/*   Updated: 2023/09/05 13:32:34 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static bool_t 		sending = false;

static unsigned short ping_checksum(unsigned short* buffer, int length) {
	unsigned short oddByte;
	register unsigned short answer;
	register long sum = 0;

	for (sum = 0; length > 1; length -= 2) {
		sum += *buffer++;
	}

	if (length == 1) {
		oddByte = 0;
		*((unsigned char*) &oddByte) = *(unsigned char*) buffer;
		sum += oddByte;
	}

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

static void ping_signal_handler(int dummy) {
	(void) dummy;
	sending = false;
}

static ping_option_t* ping_find_option(ping_t* ping, char option) {
	for (int i = 0; i < ping->options_size; i++) {
		if (ping->options[i]->key == option) {
			return ping->options[i];
		}
	}
	return NULL;
}

static char* ping_get_option_or_default(ping_t* ping, char option, char* def) {
	for (int i = 0; i < ping->options_size; i++) {
		if (ping->options[i] != NULL && ping->options[i]->key == option) {
			return ping->options[i]->value;
		}
	}
	return def;
}

uint32_t ping_loop(ping_t* ping, ping_socket_t* sock) {
	//
	signal(SIGINT, ping_signal_handler);
	// get packet size option -s or set it to default
	ping_option_t*	packet_size = ping_find_option(ping, 's');
	// get verbose option -v or set it to false
	bool_t			verbose = ping_find_option(ping, 'v') != NULL;
	// get print_timestamp option -D or set it to false
	bool_t			print_timestamp = ping_find_option(ping, 'D') != NULL;
	// get numeric only option -n or set it to false
	bool_t			numeric_only = ping_find_option(ping, 'n') != NULL;
	// get quiet option -q or set it to false
	bool_t			quiet = ping_find_option(ping, 'q') != NULL;
	// get stop after one option -o or set it to false
	bool_t			stop_after_one = ping_find_option(ping, 'o') != NULL;
	// get interval option -i or set it to 1000000
	bool_t			has_interval = ping_find_option(ping, 'i') != NULL;
	int32_t			interval = ft_atoi(ping_get_option_or_default(ping, 'i', "1")) * 1000000;
	if (has_interval && interval < 0) {
		printf("%s: bad timing interval\n", ping->argv[0]);
		return EXIT_FAILURE;
	}
	// get ttl option -t or set it to 37 by default
	bool_t			has_ttl = ping_find_option(ping, 't') != NULL;
	int32_t			ttl = ft_atoi(ping_get_option_or_default(ping, 't', "37"));
	if (has_ttl && ttl <= 0) {
		printf("%s: can't set unicast time-to-live: Invalid argument\n", ping->argv[0]);
		return EXIT_FAILURE;
	}
	// get max count option -c or set it to default
	bool_t			has_count = ping_find_option(ping, 'c') != NULL;
	int32_t			count = ft_atoi(ping_get_option_or_default(ping, 'c', "-1"));
	if (has_count && count <= 0) {
		printf("%s: bad number of packets to transmit\n", ping->argv[0]);
		return EXIT_FAILURE;
	}
	//
	uint32_t		flag = 1;
	//
	uint32_t		msg_count = 0;
	//
	uint32_t		msg_received_count = 0;
	//
	ping_timeval_t	tv_out = { 1, 0 };
	//
	unsigned long	start_time, end_time, tts, tte;
	//
	ping_stats_t	stats = { DBL_MAX, 0, 0, 0, 0, 0 };
	//
	ping_packet_t packet;
	ft_memset((char *) &packet, 0, sizeof(packet));
	//
	int packet_msg_size;
	if (packet_size == NULL) {
		packet_msg_size = 64 - sizeof(packet.header);
	} else {
		packet_msg_size = sizeof(char) * ft_atoi(packet_size->value);
	}
	packet.message = malloc(packet_msg_size);
	//
	ping_get_time(&tts);
	//
	if (setsockopt(sock->instance, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0 && verbose) {
		fprintf(stderr, "Unable to set socket option IPPROTO_IP:IP_TTL to %d", ttl);
	}
	//
	if (setsockopt(sock->instance, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv_out, sizeof(tv_out)) < 0 && verbose) {
		fprintf(stderr, "Unable to set socket option SOL_SOCKET:SO_RCVTIMEO to {%ld,%ld}", tv_out.tv_sec, tv_out.tv_usec);
	}
	//
	if (verbose) {
		fprintf(stdout, "ft_ping: sock4.fd: 3 (socktype: SOCK_RAW), sock6.fd: 4 (socktype: SOCK_RAW), hints.ai_family: PF_UNSPEC\n\n");
		fprintf(stdout, "ai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", ping->destination);
	}
	//
	printf("PING %s (%s) %d(%d) bytes of data.\n",
		ping->destination,
		ping->destination_ip,
		packet_msg_size,
		packet_msg_size + (int) sizeof(packet.header));
	//
	sending = true;
	while (sending) {
		flag = 1;

		if (has_count && count <= 0) {
			break;
		}

		int seq = msg_count++;
		packet.header.icmp_type = ICMP_ECHO;
		packet.header.icmp_code = 0;
		packet.header.icmp_cksum = 0;
		packet.header.icmp_id = ping->pid;
		packet.header.icmp_seq = seq;
		packet.header.icmp_cksum = ping_checksum((unsigned short*) &packet, sizeof(packet.header) + packet_msg_size);

		ft_memset(packet.message, 0, packet_msg_size);
		for (int i = 0; i < packet_msg_size - 1; i++) {
			packet.message[i] = 1;
		}

		ping_get_time(&start_time);

		if (ping_socket_send(sock, &packet, sizeof(packet.header) + packet_msg_size) <= 0) {
			if (verbose) { fprintf(stderr, "Cannot send packet to: %s\n", ping->destination_ip); }
			flag = 0;
		}
		count--;

		int32_t bytes = ping_socket_receive(ping, sock);
		if (bytes <= 0) {
			if (verbose) { fprintf(stderr, "Cannot receive packet from: %s: %s\n", ping->destination_ip, strerror(errno)); }
			flag = 0;
		}

		ping_get_time(&end_time);
		double timeElapsed = (end_time - start_time) / 1000.0;

		if (flag == 0)						{ continue; }

		if (timeElapsed < stats.min_rtt)	{ stats.min_rtt = timeElapsed; }
		if (timeElapsed > stats.max_rtt)	{ stats.max_rtt = timeElapsed; }
		stats.total_rtt += timeElapsed;
		stats.squared_total_rtt += timeElapsed * timeElapsed;

		if (sending == 0)					{ msg_count--; break; }

		if (!quiet && print_timestamp) {
			ping_timeval_t now;
			gettimeofday(&now, NULL);
			printf("[%ld.%ld] ", now.tv_sec, now.tv_usec);
		}

		struct ip *ip_header = (struct ip *) ping->iov_buffer;
		struct icmphdr *icmp_header = (struct icmphdr *)(ping->iov_buffer + (ip_header->ip_hl << 2));
		int received_ttl = ip_header->ip_ttl;

		if(icmp_header->type != ICMP_ECHOREPLY) {
			if (!quiet) {
				printf("From ");
				if (numeric_only)	{ printf("%s: ", ping->destination_ip); }
				else				{ printf("%s (%s): ", ping->destination_reverse, ping->destination_ip); }
				printf("icmp_seq=%d %s\n", msg_count, "Time to live exceeded");
			}
		} else {
			if (!quiet) {
				printf("%d bytes from ", (int) (packet_msg_size + sizeof(packet.header)));
				if (numeric_only)	{ printf("%s: ", ping->destination_ip); }
				else				{ printf("%s (%s): ", ping->destination_reverse, ping->destination_ip); }
				printf("icmp_seq=%d ttl=%d time=%.1f ms\n", msg_count, received_ttl, timeElapsed);
			}
			msg_received_count++;
		}

		if (stop_after_one) { sending = false; }
		usleep(interval);
	}
	//
	ping_get_time(&tte);
	//
	stats.avg_rtt = stats.total_rtt / msg_count;
	//
	stats.mdev_rtt = stats.total_rtt / msg_received_count;
	stats.mdev_rtt = sqrt((stats.squared_total_rtt / msg_received_count) - (stats.mdev_rtt * stats.mdev_rtt));
	//
	free(packet.message);
	//
	printf("\n");
	printf("--- %s ping statistics ---\n", ping->destination);
	//
	if (msg_count - msg_received_count > 0) {
		printf("%d packets transmitted, %d received, +%d errors, %d%% packet loss, time %.0f ms\n",
			msg_count,
			msg_received_count,
			(int) msg_count - msg_received_count,
			(int) ((msg_count - msg_received_count) * 100.0 / msg_count),
			(float) (tte - tts) / 1000.0f);
	} else {
		printf("%d packets transmitted, %d received, %d%% packet loss, time %.0f ms\n",
			msg_count,
			msg_received_count,
			(int) ((msg_count - msg_received_count) * 100.0 / msg_count),
			(float) (tte - tts) / 1000.0f);
	}
	//
	if (msg_received_count > 0) {
		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms",
			stats.min_rtt, stats.avg_rtt, stats.max_rtt, stats.mdev_rtt);
	}
	printf("\n");
	//
	return EXIT_SUCCESS;
}
