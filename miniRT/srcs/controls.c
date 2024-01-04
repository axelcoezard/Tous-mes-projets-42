/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:40:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/18 09:47:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	controls_init(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < 256)
		scene->keys[i] = 0;
}

int	controls_listen(t_scene *scene)
{
	if (scene->keys[KEY_ESCAPE])
		hook_close(scene);
	return (0);
}
