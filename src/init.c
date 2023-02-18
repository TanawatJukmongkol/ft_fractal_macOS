/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 06:03:12 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/19 00:13:07 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_manual(void)
{
	ft_putstr_fd("\033[96mUsage:\033[32m\n", 1);
	ft_putstr_fd("> ./fractol <fractal:uint> <*re:int> <*im:int>\033[0m\n", 1);
	ft_putstr_fd("	fractal: 0 = Mandelbrot, 1 = Julia, 2 = Burning ship\n", 1);
	ft_putstr_fd("	re(al): -2000 to 2000 (maps to -2.000 to 2.000)\n", 1);
	ft_putstr_fd("	im(aginary): -2000 to 2000 (maps to -2.000 to 2.000)\n\n", 1);
	ft_putstr_fd("\033[96mKey bindings:\033[0m\n", 1);
	ft_putstr_fd("	[Arrow keys]: Pans the camera\n", 1);
	ft_putstr_fd("	[I / O]: Zooms in and out\n", 1);
	ft_putstr_fd("	[W / S]: Change color scheme\n", 1);
	ft_putstr_fd("	[A / D]: Change shader\n", 1);
	ft_putstr_fd("	[H]: Go back to home (origin, 0+0i).\n", 1);
	ft_putstr_fd("	[Esc]: Exit application.\n\n\033[93m", 1);
	ft_putstr_fd("Note: on OSX, the key [Ctrl] is replaced with [Cmd].\n", 1);
	ft_putstr_fd("\033[0m\n", 1);
}

static void	man_error(char *msg)
{
	ft_putstr_fd("\033[31m", 1);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\033[0m\n", 1);
	print_manual();
	exit(1);
}

static void	opt_switch(t_vars *vars, int ac, char **opt)
{
	int	frac;

	frac = ft_atoi(opt[1]);
	if (frac == 0)
		vars->fractol = &mandelbrot_set;
	else if (frac == 1)
	{
		if (ac >= 4 && !ft_isdigit(*opt[2])
			&& !ft_isdigit(*opt[3]))
			man_error("Invalid argument type.");
		vars->fractol = &julia_set;
		vars->init_cmplx.im = -0.4;
		vars->init_cmplx.re = 0.6;
		if (ac < 4)
			return ;
		vars->init_cmplx.im = (float)ft_atoi(opt[2]) / 1000;
		vars->init_cmplx.re = (float)ft_atoi(opt[3]) / 1000;
	}
	else if (frac == 2)
		vars->fractol = &burning_ship;
	else
		man_error("Invalid fractal selection.");
}

void	options(t_vars *vars, int ac, char **opt)
{
	int	frac;

	if (ac < 2)
		man_error("Not enough argument passed!");
	if (!ft_isdigit(*opt[1]))
		man_error("Invalid argument type.");
	opt_switch(vars, ac, opt);
}

void	init_vars(t_vars *vars)
{
	vars->mlx.mlx_ptr = mlx_init();
	if (!vars->mlx.mlx_ptr)
		mlx_error(vars, "Failed to initialize MLX.");
	vars->mlx.win_ptr = mlx_new_window(vars->mlx.mlx_ptr, vars->mlx.win_width,
			vars->mlx.win_height, "ft_fractal");
	if (!vars->mlx.mlx_ptr)
		mlx_error(vars, "Failed to initialize MLX window.");
	vars->keys = 0;
	vars->cam.x = 0;
	vars->cam.y = 0;
	vars->cam.zoom = 1;
	vars->max_ittr = 142;
	vars->draw_ittr = 0;
	vars->draw_offset = 5;
	vars->scheme = 0;
	vars->scheme_len = 2;
	vars->colors = vars->schemes[vars->scheme];
	vars->renderer = 0;
	vars->renderer_len = 1;
	vars->update = vars->renderers[vars->renderer];
}
