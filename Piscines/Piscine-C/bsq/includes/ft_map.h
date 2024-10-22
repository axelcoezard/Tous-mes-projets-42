/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:05:34 by acoezard          #+#    #+#             */
/*   Updated: 2021/09/27 15:35:08 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
# define FT_MAP_H

typedef struct s_map {
	char	*grid;
	int		width;
	int		height;
	char	c_empty;
	char	c_full;
	char	c_block;
}				t_map;

# define FT_MAP_FULL	10
# define FT_MAP_EMPTY	11
# define FT_MAP_BLOCK	12

t_map	*ft_map_create(int width, int height);
int		ft_map_fill(t_map *map, t_file *file);
int		ft_map_set(t_map *map, int x, int y, char c);
char	ft_map_get(t_map *map, int x, int y);
void	ft_map_define(t_map *map, int id, char c);
void	ft_map_print(t_map *map);
void	ft_map_destroy(t_map *map);

#endif
