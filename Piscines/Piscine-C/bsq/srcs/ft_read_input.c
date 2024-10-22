/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:16:43 by lmataris          #+#    #+#             */
/*   Updated: 2021/09/30 09:38:03 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft.h"

int	ft_read_input(void)
{
	t_file	*file;
	t_map	*map;
	char	*str;

	str = malloc(100000000);
	if (read(0, str, 100000000) < 0)
		return (ft_error(FT_MAP_ERROR));
	file = malloc(sizeof(t_file));
	file->buffer = str;
	file->lines = ft_split(str, "\n");
	file->size = ft_strlen(str);
	map = ft_parser_file(file);
	if (map != NULL)
		ft_solve(map, 0, 0, 0), ft_map_print(map);
	ft_map_destroy(map);
	ft_file_close(file);
	return (0);
}
