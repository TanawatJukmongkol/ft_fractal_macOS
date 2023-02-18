/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 07:56:47 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/18 17:23:08 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_vars *vars)
{
	if (vars->image.ptr)
		mlx_destroy_image(vars->mlx.mlx_ptr, vars->image.ptr);
	mlx_destroy_window(vars->mlx.mlx_ptr, vars->mlx.win_ptr);
	free(vars->mlx.mlx_ptr);
	exit(0);
}

void	mlx_error(t_vars *vars, char *msg)
{
	ft_putstr_fd("\033[31mERROR: ", 1);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\033[0m\n", 1);
	if (vars->image.ptr)
	{
		mlx_destroy_image(vars->mlx.mlx_ptr, vars->image.ptr);
		ft_putstr_fd(">> image ptr destroyed.\n", 1);
	}
	if (vars->mlx.win_ptr)
	{
		mlx_destroy_window(vars->mlx.mlx_ptr, vars->mlx.win_ptr);
		ft_putstr_fd(">> window ptr destroyed.\n", 1);
	}
	if (vars->mlx.mlx_ptr)
	{
		free(vars->mlx.mlx_ptr);
		ft_putstr_fd(">> mlx freed.\n", 1);
	}
	else
	{
		ft_putstr_fd("\033[31mERROR: ", 1);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\033[0m\n", 1);
	}
	exit(1);
}
