/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:06:39 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/24 03:22:03 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mandelbrot_optimize(double *p, t_param param)
{
	double	x;
	double	y;

	x = param.c.real_part - 1. / 4;
	y = param.c.im_part;
	*p = sqrt(x * x + y * y);
	*p = *p - 2 * (*p) * (*p) + 1. / 4;
	x = param.c.real_part + 1;
	if (param.c.real_part < *p
		|| (x * x + y * y) < 1. / 16)
			*p = param.max_iter - 1;
	else
	*p = -1;
}

void	mandelbrot(t_param param)
{
	int			i;
	int			j;
	double		p;
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
			mandelbrot_optimize(&p, param);
			while (z.complex_expo.module_pow2 <= 4 && ++p < param.max_iter)
				z = complex_add(complex_dot(z, z), param.c);
			my_mlx_pixel_put(param.img, i, j, color_me(p, param.max_iter));
		}
	}
}

void	julia(t_param param)
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
			z = complex_init(i * (param.z2_lim.real_part
						- param.z1_lim.real_part) / WIDTH
					+ param.z1_lim.real_part, j * (param.z1_lim.im_part
						- param.z2_lim.im_part) / HEIGHT
					+ param.z2_lim.im_part, 1);
			p = -1;
			while (z.complex_expo.module_pow2 <= 4 && ++p < param.max_iter)
				z = complex_add(complex_dot(z, z), param.c);
			my_mlx_pixel_put(param.img, i, j, color_me(p, param.max_iter));
		}
	}
}

static void	ft_init(int ac, char **argv, t_param *par)
{
	t_param	param;

	param.is_mousemove = 0;
	param.zoom_factor = 0.85;
	param.dezoom_factor = 1.15;
	param.max_iter = 55;
	param.str = argv[1];
	init_repere_lim(argv[1], &param.z1_lim, &param.z2_lim);
	if (ft_cmp(argv[1], "Julia"))
	{
		if (ac == 4)
			param.c = complex_init(ft_atof(argv[2], 0), ft_atof(argv[3], 0), 0);
		else
			param.c = complex_init(-0.8, 0.156, 0);
	}
	else if (!ft_cmp(argv[1], "Mandelbrot"))
		ft_message(0);
	param.mlx = mlx_init();
	param.mlx_win = mlx_new_window(param.mlx,
			WIDTH, HEIGHT, "Fractol by ggneme");
	*par = param;
}

int	main(int ac, char **argv)
{
	t_data	img;
	t_param	param;

	if (ac < 2)
		ft_message(0);
	ft_init(ac, argv, &param);
	img.img = mlx_new_image(param.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	param.img = &img;
	if (ft_cmp(argv[1], "Julia"))
		julia(param);
	else if (ft_cmp(argv[1], "Mandelbrot"))
		mandelbrot(param);
	mlx_put_image_to_window(param.mlx, param.mlx_win, (*param.img).img, 0, 0);
	mlx_hook(param.mlx_win, ON_DESTROY, 0, ft_close, 0);
	mlx_hook(param.mlx_win, ON_KEYDOWN, 0, handle_onkeydown, &param);
	if (ft_cmp(argv[1], "Julia"))
		mlx_hook(param.mlx_win, ON_MOUSEMOVE, 0, handle_mousemove, &param);
	mlx_hook(param.mlx_win, ON_MOUSEDOWN, 0, handle_on_mousedown, &param);
	mlx_loop(param.mlx);
	return (0);
}
