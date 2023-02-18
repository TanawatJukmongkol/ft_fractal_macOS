#include "fractol.h"

void	draw_point_rgb(t_vars *vars, int x, int y, int ittr)
{
	ft_draw_point(&vars->image, x, y,
		(((ittr * ((vars->colors[2] >> 16) & 0xff))
				/ vars->max_ittr) << 16)
		+ (((ittr * ((vars->colors[2] >> 8) & 0xff))
				/ vars->max_ittr) << 8)
		+ (((ittr * ((vars->colors[2]) & 0xff))
				/ vars->max_ittr)) + (0xff << 24));
}

void	shader_1(t_vars *vars, int draw_ittr)
{
	t_cmplx		complex;
	t_shader	shad;

	shad.y = (draw_ittr != -1) * draw_ittr / 8;
	while (shad.y < vars->mlx.win_height)
	{
		shad.x = (draw_ittr != -1) * draw_ittr % 8;
		while (shad.x < vars->mlx.win_width)
		{
			cartesian_to_cmplx(vars, &complex, &shad.x, &shad.y);
			vars->fractol(vars, &complex,
				&shad.ittr, &shad.is_in_set);
			if (shad.ittr != vars->max_ittr)
				ft_draw_point(&vars->image, shad.x, shad.y,
					vars->colors[2 + shad.ittr % vars->colors[0]]);
			else
				ft_draw_point(&vars->image, shad.x, shad.y, vars->colors[1]);
			shad.x += 1 + 7 * (draw_ittr != -1);
		}
		shad.y += 1 + 7 * (draw_ittr != -1);
	}
	ft_put_image(&vars->image, 0, 0);
}

void	shader_2(t_vars *vars, int draw_ittr)
{
	t_cmplx		complex;
	t_shader	shad;

	shad.y = (draw_ittr != -1) * draw_ittr / 8;
	while (shad.y < vars->mlx.win_height)
	{
		shad.x = (draw_ittr != -1) * draw_ittr % 8;
		while (shad.x < vars->mlx.win_width)
		{
			cartesian_to_cmplx(vars, &complex, &shad.x, &shad.y);
			vars->fractol(vars, &complex,
				&shad.ittr, &shad.is_in_set);
			if (shad.ittr != vars->max_ittr)
				draw_point_rgb(vars, shad.x, shad.y, shad.ittr);
			else
				ft_draw_point(&vars->image, shad.x, shad.y, vars->colors[1]);
			shad.x += 1 + 7 * (draw_ittr != -1);
		}
		shad.y += 1 + 7 * (draw_ittr != -1);
	}
	ft_put_image(&vars->image, 0, 0);
}
