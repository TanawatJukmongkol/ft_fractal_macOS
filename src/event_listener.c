/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:19:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/18 23:42:56 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_event(int code, t_vars *vars)
{
	if (code == 53) // escape
		close_window(vars);
	if (code == 126) // up
		vars->cam.y += 0.4 / (vars->cam.zoom * 4);
	else if (code == 125) // down
		vars->cam.y -= 0.4 / (vars->cam.zoom * 4);
	if (code == 123) // left
		vars->cam.x -= 0.4 / (vars->cam.zoom * 4);
	else if (code == 124) // right
		vars->cam.x += 0.4 / (vars->cam.zoom * 4);
	
	if (code == 13) // w
		change_color_scheme(1, vars);
	else if (code == 1) // s
		change_color_scheme(2, vars);
	if (code == 0) // a
		change_color_scheme(3, vars);
	else if (code == 2) // d
		change_color_scheme(4, vars);
	if (code == 34)
		vars->cam.zoom *= 1.08;
	if (code == 31)
		vars->cam.zoom /= 1.08;
	vars->draw_ittr = 0;
	return (0);
}

int	mouse_event(int code, int x, int y, t_vars *vars)
{
	if (code == mouse_Right)
		vars->pressed = 1;
	if (code == mouse_Middle_Up)
	{
		vars->cam.zoom *= 1.08;
		if (vars->keys != kbit_mod)
		{
			vars->cam.x += ((float)x - (vars->mlx.win_width >> 1))
				/ (vars->mlx.win_width >> 1)
				/ vars->cam.zoom * 0.4;
			vars->cam.y -= ((float)y - (vars->mlx.win_height >> 1))
				/ (vars->mlx.win_height >> 1)
				/ vars->cam.zoom * 0.4;
		}
	}
	else if (code == mouse_Middle_Down && vars->cam.zoom > 0.08)
		vars->cam.zoom /= 1.08;
	if (code == mouse_Middle_Up || code == mouse_Middle_Down)
		vars->draw_ittr = 0;
	return (0);
}

int	mouse_released(int code, int x, int y, t_vars *vars)
{
	vars->pressed = 0;
	return (0);
}

int	mouse_event_move(int x, int y, t_vars *vars)
{
	if (!vars->pressed)
		return (0);
	if (vars->fractol != &julia_set)
		return (1);
	vars->init_cmplx.im = (x - ((float)vars->mlx.win_width / 2))
		* 2 / vars->mlx.win_width;
	vars->init_cmplx.re = (y - ((float)vars->mlx.win_height / 2))
		* 2 / vars->mlx.win_height;
	vars->draw_ittr = 0;
	return (0);
}