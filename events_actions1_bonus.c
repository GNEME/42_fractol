/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_actions1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:55:03 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/29 14:51:49 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	handle(t_param *param, double *xx, double *yy, float factor)
{
	t_param	par;

	par = (*param);
	*xx = factor * (par.z1_lim.real_part - par.mouse_pos.real_part)
		+ par.mouse_pos.real_part;
	*yy = factor * (par.z1_lim.im_part - par.mouse_pos.im_part)
		+ par.mouse_pos.im_part;
	(*param).z1_lim = complex_init(*xx, *yy, 0);
	*xx = factor * (par.z2_lim.real_part - par.mouse_pos.real_part)
		+ par.mouse_pos.real_part;
	*yy = factor * (par.z2_lim.im_part - par.mouse_pos.im_part)
		+ par.mouse_pos.im_part;
	(*param).z2_lim = complex_init(*xx, *yy, 0);
	if (ft_cmp(par.str, "Mandelbrot"))
		mandelbrot(*param);
	else if (ft_cmp(par.str, "Julia"))
		julia(*param);
	else
		buddabrot(*param);
	mlx_clear_window(par.mlx, par.mlx_win);
	mlx_put_image_to_window(par.mlx, par.mlx_win, par.img->img, 0, 0);
}

static void	normi(void *param, t_param par)
{
	if ((*(t_param *)param).max_iter <= 50)
		(*(t_param *)param).max_iter = 50;
	else
		(*(t_param *)param).max_iter = par.max_iter - 7;
}

int	handle_on_mousedown(int button, int x, int y, void *param)
{
	t_param	par;
	double	xx;
	double	yy;

	par = (*(t_param *)param);
	if (button == 1 || button == 2)
		(*(t_param *)param).is_mousemove = 1 - (*(t_param *)param).is_mousemove;
	else if (button == 4 || button == 5)
	{
		(*(t_param *)param).mouse_pos = complex_init(x * (par.z2_lim.real_part
					- par.z1_lim.real_part) / WIDTH + par.z1_lim.real_part, y
				* (par.z1_lim.im_part - par.z2_lim.im_part)
				/ HEIGHT + par.z2_lim.im_part, 0);
		if (button == 5)
		{
			normi(param, par);
			handle((t_param *)param, &xx, &yy, par.dezoom_factor);
		}
		else
		{
			(*(t_param *)param).max_iter = par.max_iter + 7;
			handle((t_param *)param, &xx, &yy, par.zoom_factor);
		}
	}
	return (0);
}
