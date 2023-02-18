/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:49:59 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/18 17:59:03 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	loop(t_vars *vars)
{
	int	count;

	count = 0;
	if (!vars->image.ptr)
		return (0);
	if (vars->draw_ittr < 64 * 8)
	{
		while (count < 9)
		{
			vars->update(vars, vars->draw_ittr % 64);
			vars->draw_ittr += (count + vars->draw_offset) % 8;
			count++;
		}
		vars->draw_offset = (vars->draw_offset + 1) % 8;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.schemes[0] = (int [5]){3, 0xffbababa,
		0xff424242, 0xff242424, 0xff121212};
	vars.schemes[1] = (int [9]){7, 0xff000000, 0xffff0000, 0xffffa500,
		0xffffff00, 0xff008000, 0xff0000ff, 0xff4b0082, 0xffee82ee};
	vars.schemes[2] = (int [10]){8, 0xff000d0b, 0xff16d9b5, 0xff008b99,
		0xff4c3c99, 0xffff9019, 0xffff36d0, 0xffaa4fd1, 0xffff5555, 0xfff1fa8c};
	vars.renderers[0] = &shader_1;
	vars.renderers[1] = &shader_2;
	vars.mlx.win_width = 800;
	vars.mlx.win_height = 600;
	vars.mlx.win_ratio = (float)vars.mlx.win_width / vars.mlx.win_height;
	options(&vars, argc, argv);
	init_vars(&vars);
	ft_init_image(&vars);
	mlx_hook(vars.mlx.win_ptr, 17, 0L, close_window, &vars);
	mlx_hook(vars.mlx.win_ptr, 4, (1L<<2), mouse_event, &vars);
	mlx_hook(vars.mlx.win_ptr, 5, (1L<<3), mouse_released, &vars);
	mlx_hook(vars.mlx.win_ptr, 6, (1L<<9),
		mouse_event_move, &vars);
	mlx_hook(vars.mlx.win_ptr, 2, (1L<<0), key_event, &vars);
	mlx_hook(vars.mlx.win_ptr, 3, (1L<<1), key_released, &vars);
	mlx_loop_hook(vars.mlx.mlx_ptr, loop, &vars);
	mlx_loop(vars.mlx.mlx_ptr);
	return (0);
}
