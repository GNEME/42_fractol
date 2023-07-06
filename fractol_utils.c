/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 02:48:25 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/24 01:46:03 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	color_me(int k, int max_iter)
{
	int	color;

	color = 0;
	if (k != max_iter)
	{
		color += ((5 * k) % 256) * 65536;
		color += ((7 * k) % 256) * 256;
		color += (10 * k) % 256;
	}
	return (color);
}

int	ft_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i ++;
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

void	init_repere_lim(char *str, t_complex *z1_lim, t_complex *z2_lim)
{
	if (ft_cmp(str, "Mandelbrot"))
	{
		*z1_lim = complex_init(-2, -1.25, 0);
		*z2_lim = complex_init(0.85, 1.25, 0);
	}
	else
	{
		*z1_lim = complex_init(-2, -2, 0);
		*z2_lim = complex_init(2, 2, 0);
	}
}

void	ft_message(int is_bonus)
{
	if (!is_bonus)
	{
		write(1, "./fractol Mandelbrot\n", 21);
		write(1, "./fractol Julia\n", 16);
		write(1, "./fractol Julia -0.8 0.156\n", 27);
		write(1, "\treal_part = -0.8, im_part = 0.156\n", 35);
	}
	else
	{
		write(1, "./fractol_bonus Mandelbrot\n", 27);
		write(1, "./fractol_bonus Bonus\n", 22);
		write(1, "./fractol_bonus Julia\n", 22);
		write(1, "./fractol_bonus Julia -0.8 0.156\n", 33);
		write(1, "\treal_part = -0.8, im_part = 0.156\n", 35);
	}
	exit(0);
}
