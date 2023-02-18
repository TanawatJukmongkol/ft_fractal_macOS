/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:19:03 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/18 18:12:18 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_event(int code, t_vars *vars)
{
	if (code == kdef_mod)
		vars->keys |= kbit_mod;
	else if (code == kdef_up)
		vars->keys |= kbit_up;
	else if (code == kdef_down)
		vars->keys |= kbit_down;
	else if (code == kdef_left)
		vars->keys |= kbit_left;
	else if (code == kdef_right)
		vars->keys |= kbit_right;
	else if (code == kdef_term)
		close_window(vars);
	if (vars->keys & kbit_mod)
		return (mod_key(code, vars));
	vars->cam.x += 0.4 * (((vars->keys & kbit_right) != 0)
			- ((vars->keys & kbit_left) != 0)) / (vars->cam.zoom * 4);
	vars->cam.y -= 0.4 * (((vars->keys & kbit_down) > 0)
			- ((vars->keys & kbit_up) > 0)) / (vars->cam.zoom * 4);
	vars->draw_ittr = 0;
	return (0);
}

int	mod_key(int code, t_vars *vars)
{
	vars->draw_ittr = 0;
	if (code == kmod_origin)
		vars->keys |= kbit_origin;
	else if (code == kmod_color)
		vars->keys |= kbit_color;
	if (vars->keys == (kbit_mod | kbit_up))
		vars->cam.zoom *= 1.08;
	else if (vars->keys == (kbit_mod | kbit_down) && vars->cam.zoom > 0.08)
		vars->cam.zoom /= 1.08;
	else if (vars->keys == (kbit_mod | kbit_origin))
	{
		vars->cam.x = 0;
		vars->cam.y = 0;
		vars->cam.zoom = 1;
	}
	else
		change_color_scheme(code, vars);
	return (0);
}

int	key_released(int code, t_vars *vars)
{
	if (code == kdef_mod)
		vars->keys &= ~kbit_mod;
	else if (code == kdef_up)
		vars->keys &= ~kbit_up;
	else if (code == kdef_down)
		vars->keys &= ~kbit_down;
	else if (code == kdef_left)
		vars->keys &= ~kbit_left;
	else if (code == kdef_right)
		vars->keys &= ~kbit_right;
	else if (code == kmod_origin)
		vars->keys &= ~kbit_origin;
	else if (code == kmod_color)
		vars->keys &= ~kmod_color;
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