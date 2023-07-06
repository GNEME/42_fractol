/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_actions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:52:42 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/29 12:52:58 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_close(int keycode)
{
	if (keycode == ESC)
		exit(0);
	else if (!keycode)
		exit(0);
	return (0);
}

static int	handle_left_right(int keycode, void *param)
{
	if (keycode == LEFT)
	{
		(*(t_param *)param).z1_lim = complex_add((*(t_param *)param).z1_lim,
				complex_init(0.05, 0, 0));
		(*(t_param *)param).z2_lim = complex_add((*(t_param *)param).z2_lim,
				complex_init(0.05, 0, 0));
	}
	else if (keycode == RIGHT)
	{
		(*(t_param *)param).z1_lim = complex_add((*(t_param *)param).z1_lim,
				complex_init(-0.05, 0, 0));
		(*(t_param *)param).z2_lim = complex_add((*(t_param *)param).z2_lim,
				complex_init(-0.05, 0, 0));
	}
	if (ft_cmp((*(t_param *)param).str, "Mandelbrot"))
		mandelbrot(*(t_param *)param);
	else if (ft_cmp((*(t_param *)param).str, "Julia"))
		julia(*(t_param *)param);
	else
		buddabrot(*(t_param *)param);
	mlx_clear_window((*(t_param *)param).mlx, (*(t_param *)param).mlx_win);
	mlx_put_image_to_window((*(t_param *)param).mlx,
		(*(t_param *)param).mlx_win,
		(*(t_param *)param).img->img, 0, 0);
	return (0);
}

static int	handle_up_down(int keycode, void *param)
{
	if (keycode == UP)
	{
		(*(t_param *)param).z1_lim = complex_add((*(t_param *)param).z1_lim,
				complex_init(0, -0.05, 0));
		(*(t_param *)param).z2_lim = complex_add((*(t_param *)param).z2_lim,
				complex_init(0, -0.05, 0));
	}
	else if (keycode == DOWN)
	{
		(*(t_param *)param).z1_lim = complex_add((*(t_param *)param).z1_lim,
				complex_init(0, 0.05, 0));
		(*(t_param *)param).z2_lim = complex_add((*(t_param *)param).z2_lim,
				complex_init(0, 0.05, 0));
	}
	if (ft_cmp((*(t_param *)param).str, "Mandelbrot"))
		mandelbrot(*(t_param *)param);
	else if (ft_cmp((*(t_param *)param).str, "Julia"))
		julia(*(t_param *)param);
	else
		buddabrot(*(t_param *)param);
	mlx_clear_window((*(t_param *)param).mlx, (*(t_param *)param).mlx_win);
	mlx_put_image_to_window((*(t_param *)param).mlx,
		(*(t_param *)param).mlx_win, (*(t_param *)param).img->img, 0, 0);
	return (0);
}

int	handle_onkeydown(int keycode, void *param)
{
	ft_close(keycode);
	handle_left_right(keycode, param);
	handle_up_down(keycode, param);
	return (0);
}

int	handle_mousemove(int x, int y, void *param)
{
	t_param		par;

	par = (*(t_param *)param);
	if (0 <= x && x <= WIDTH && 0 <= y && y <= HEIGHT
		&& (*(t_param *)param).is_mousemove)
	{
		(*(t_param *)param).c = complex_init(x * (par.z2_lim.real_part
					- par.z1_lim.real_part)
				/ WIDTH + par.z1_lim.real_part, y * (par.z1_lim.im_part
					- par.z2_lim.im_part) / HEIGHT + par.z2_lim.im_part, 0);
		julia(*(t_param *)param);
		mlx_clear_window(par.mlx, par.mlx_win);
		mlx_put_image_to_window(par.mlx, par.mlx_win, par.img->img, 0, 0);
	}
	return (0);
}
