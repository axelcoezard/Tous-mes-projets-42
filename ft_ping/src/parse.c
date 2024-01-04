/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:11:29 by acoezard          #+#    #+#             */
/*   Updated: 2023/04/25 13:27:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static bool_t parse_option_is_valid(char* values, char option_key) {
	while (*values != 0) {
		if (*values == option_key) { return true; }
		values++;
	}
	return false;
}

static bool_t parse_option_already_exists(char option_key, ping_t* ping) {
	for (int i = 0; i < ping->options_size; i++) {
		if (ping->options[i]->key == option_key) { return true; }
	}
	return false;
}

static bool_t parse_option(char option_key, int* i, ping_t* ping) {
	// define when an option needs an arg
	bool_t option_need_value[128];
	option_need_value['v'] = false;
	option_need_value['s'] = true;
	option_need_value['t'] = true;
	option_need_value['c'] = true;
	option_need_value['D'] = false;
	option_need_value['i'] = true;
	option_need_value['n'] = false;
	option_need_value['o'] = false;
	option_need_value['q'] = false;
	// if key is unset, show usage
	if (option_key == 0)								{ return false; }
	// if key is unknown, show usage
	if (!parse_option_is_valid("cDhinoqvVst", option_key))	{ return false; }
	// if key is h, show usage
	if (option_key == 'h')								{ return false; }
	// if key is V, show version
	if (option_key == 'V') { ping->print_version = true;  return false; }
	// if key already exists, show usage
	if (parse_option_already_exists(option_key, ping))	{ return false; }
	//
	char* option_value = NULL;
	if (option_need_value[(int) option_key]) {
		// if value required but end of line, show usage
		if ((*i) + 1 > ping->argc)			{ return false; }
		//
		option_value = (ping->argv)[++(*i)];
	}
	// prepare option
	ping_option_t* option = malloc(sizeof(ping_option_t));
	option->key = option_key;
	option->value = option_value;
	// store option in ping struct
	ping->options[ping->options_size++] = option;
	return true;
}

bool_t parse_all_options(ping_t* ping) {
	bool_t destination_is_set = false;
	//
	for (int i = 1; i < ping->argc; i++) {
		// if option, parse it and its potential value
		if (ping->argv[i][0] == '-') {
			if (!parse_option(ping->argv[i][1], &i, ping)) {
				return false;
			}
			continue;
		}
		// if not option and not at the end of line, show usage
		if (i + 1 < ping->argc) { return false; }
		// if not option and at the end of line, found destination
		ping->destination = ping->argv[i];
		destination_is_set = true;
	}
	return destination_is_set;
}
