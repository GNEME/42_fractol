/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 04:19:52 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/24 05:52:54 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	normi(t_param param, t_complex *z)
{
	*z = complex_init(fabs(z->real_part), fabs(z->im_part), 1);
	*z = complex_add(complex_dot(*z, *z), param.c);
}

static int	color_me_bonus(int k, int max_iter)
{
	int	color;

	color = 0;
	if (k != max_iter)
	{
		color += 192 * 65536;
		color += 192 * 256;
		color += 192;
	}
	else
	{
		color += (k % 255) * 65536;
		color += (k % 74) * 256;
		color += k % 2;
	}
	return (color);
}

void	buddabrot(t_param param)
{
	int			i;
	int			j;
	int			p;
	t_complex	z;

	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			param.c = complex_init(i * (param.z2_lim.real_part
						- param.z1_lim.real_part) / WIDTH
					+ param.z1_lim.real_part, j * (param.z1_lim.im_part
						- param.z2_lim.im_part) / HEIGHT
					+ param.z2_lim.im_part, 1);
			z = complex_init(0., 0., 1);
			p = -1;
			while (z.complex_expo.module_pow2 <= 4 && ++p < param.max_iter)
				normi(param, &z);
			my_mlx_pixel_put(param.img, i, j,
				color_me_bonus(p, param.max_iter));
		}
	}
}
