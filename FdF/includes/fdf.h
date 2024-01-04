/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:48:31 by acoezard          #+#    #+#             */
/*   Updated: 2021/11/05 16:10:05 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define DRAW_HORIZONTAL	1
# define DRAW_VERTICAL		2

# define MOUSE_LEFT			1
# define MOUSE_RIGHT		2
# define MOUSE_WHEEL		3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define MOUSE_SCROLL_LEFT	6
# define MOUSE_SCROLL_RIGHT	7

# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_W				13

# define KEY_ESCAPE			53
# define KEY_LEFT			123
# define KEY_UP				126
# define KEY_RIGHT			124
# define KEY_DOWN			125

struct s_map
{
	int			width;
	int			height;

	t_vector3	**points;
};
typedef struct s_map	t_map;

struct s_camera
{
	int		x;
	int		y;
	int		zoom;
	float	alpha;
	float	beta;
	float	gamma;
};
typedef struct s_camera	t_camera;

struct s_fdf
{
	int			buttons[10];
	int			keyboard[256];
	int			width;
	int			height;
	void		*mlx;
	void		*window;
	void		*image;
	int			*buffer;
	t_camera	*camera;
	t_map		*map;
	int			x;
	int			y;
	int			prev_x;
	int			prev_y;
};
typedef struct s_fdf	t_fdf;

t_fdf		*ft_window_open(int width, int height);
void		ft_window_loop(t_fdf *fdf, int (*hook)());
void		ft_window_update(t_fdf *fdf);
void		ft_window_clear(t_fdf *fdf, int color);
void		ft_window_close(t_fdf *fdf);

int			ft_loop_hook(t_fdf *fdf);
int			ft_quit_hook(t_fdf *fdf);
int			ft_mouse_hook(int button, int x, int y, t_fdf *fdf);
int			ft_key_press_hook(int keycode, t_fdf *fdf);
int			ft_key_release_hook(int keycode, t_fdf *fdf);
int			ft_mouse_press_hook(int button, int x, int y, t_fdf *fdf);
int			ft_mouse_release_hook(int button, int x, int y, t_fdf *fdf);
int			ft_mouse_move_hook(int x, int y, t_fdf *fdf);

void		ft_draw_text(t_fdf *fdf, int x, int y, char *text);
void		ft_draw_integer(t_fdf *fdf, int x, int y, int i);
void		ft_draw_projection(t_fdf *fdf, int x, int y, int drawcode);
void		ft_draw_pixel(t_fdf *fdf, int x, int y, int color);
void		ft_draw_line(t_fdf *fdf, t_vector2 *a, t_vector2 *b, int color);
t_vector2	*ft_projection(t_vector3 *vector, t_fdf *fdf);

int			ft_camera_init(t_fdf *fdf);
t_camera	*ft_camera_move(t_camera *camera, int x, int y);
t_camera	*ft_camera_rotate(t_camera *camera, float a, float b, float g);
t_camera	*ft_camera_zoom(t_camera *camera, int zoom);
void		ft_camera_controls(t_fdf *fdf);

t_fdf		*ft_map_init(t_fdf *fdf, int width, int height);
t_map		*ft_map_init_points(t_map *map);
t_map		*ft_map_set_point(t_map *map, int x, int y, int height);
t_vector3	*ft_map_get_point(t_map *map, int x, int y);

int			ft_parser(t_fdf *fdf, char *filename);

#endif
