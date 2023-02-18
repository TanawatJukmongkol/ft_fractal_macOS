/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:51:56 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/19 00:08:28 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>

# include "../mlx/mlx.h"
# include "../lib/libft/libft.h"

# define ESCAPE 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define COLOR_NEXT 13
# define COLOR_PREV 1
# define SHAD_NEXT 0
# define SHAD_PREV 2
# define ORIGIN 4

enum	e_mousedef {
	mouse_Left			= 1,
	mouse_Right			= 2,
	mouse_Middle		= 3,
	mouse_Middle_Down	= 4,
	mouse_Middle_Up		= 5
};

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
	float	win_ratio;
}	t_mlx;

typedef struct s_cam {
	float	x;
	float	y;
	float	zoom;
}	t_cam;

typedef struct s_image
{
	t_mlx	mlx;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	void	*ptr;
	char	*buff;
}	t_image;

typedef struct s_cmplx
{
	float	re;
	float	im;
}	t_cmplx;

typedef struct s_shader
{
	int		x;
	int		y;
	int		ittr;
	int		is_in_set;
}	t_shader;

typedef struct s_vars {
	t_mlx			mlx;
	t_cam			cam;
	unsigned int	keys;
	t_image			image;
	int				*colors;
	int				*schemes[10];
	int				scheme;
	int				scheme_len;
	void			*renderers[10];
	int				renderer;
	int				renderer_len;
	int				max_ittr;
	int				draw_ittr;
	int				draw_offset;
	int				pressed;
	t_cmplx			init_cmplx;
	void			(*update)(struct s_vars *vars, int draw_ittr);
	void			(*fractol)(struct s_vars *vars, t_cmplx *cmplx_nbr,
			int *ittr, int *is_in_set);
}	t_vars;

// Init functions.
void	options(t_vars *vars, int ac, char **opt);
void	init_vars(t_vars *vars);

// Minilibx utils and extensions
int		close_window(t_vars *vars);
void	mlx_error(t_vars *vars, char *msg);

// MLX event listeners
int		key_event(int code, t_vars *vars);
int		mouse_event(int code, int x, int y, t_vars *vars);
int		mouse_released(int code, int x, int y, t_vars *vars);
int		mouse_event_move(int x, int y, t_vars *vars);

// Graphics
void	ft_init_image(t_vars *vars);
void	ft_draw_point(t_image *img, int x, int y, unsigned int color_hex);
void	ft_put_image(t_image *img, int x, int y);
int		change_color_scheme(int code, t_vars *vars);

// Shaders
void	shader_1(t_vars *vars, int draw_ittr);
void	shader_2(t_vars *vars, int draw_ittr);

// Math functions
void	cartesian_to_cmplx(t_vars *vars, t_cmplx *cmplx_nbr, int *x, int *y);
void	mandelbrot_set(t_vars *vars, t_cmplx *cmplx_nbr,
			int *ittr, int *is_in_set);
void	julia_set(t_vars *vars, t_cmplx *cmplx_nbr,
			int *ittr, int *is_in_set);
void	burning_ship(t_vars *vars, t_cmplx *cmplx_nbr,
			int *ittr, int *is_in_set);

#endif