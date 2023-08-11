/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:07:19 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/24 03:23:51 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 650
# define HEIGHT 650
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

enum {
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
	ON_MOUSEMOVE = 6,
	ON_MOUSEDOWN = 4,
	ESC = 53,
	LEFT = 123,
	UP = 126,
	RIGHT = 124,
	DOWN = 125
};

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex_expo {
	double	module_pow2;
}	t_complex_expo;

typedef struct s_complex {
	double			real_part;
	double			im_part;
	t_complex_expo	complex_expo;
}	t_complex;

typedef struct s_param {
	void		*mlx;
	void		*mlx_win;
	float		zoom_factor;
	float		dezoom_factor;
	int			is_mousemove;
	int			max_iter;
	char		*str;
	t_data		*img;
	t_complex	z2_lim;
	t_complex	z1_lim;
	t_complex	mouse_pos;
	t_complex	c;
}				t_param;

t_complex	complex_init(double real_part, double im_part, int init_expo);
t_complex	complex_dot(t_complex z1, t_complex z2);
t_complex	complex_add(t_complex z1, t_complex z2);
double		ft_atof(char *str, int is_bonus);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			color_me(int k, int max_iter);
int			ft_cmp(char *str1, char *str2);
void		init_repere_lim(char *str, t_complex *z1_lim, t_complex *z2_lim);
void		ft_message(int is_bonus);
int			ft_close(int keycode);
int			handle_onkeydown(int keycode, void *param);
void		julia(t_param param);
void		mandelbrot(t_param param);
int			handle_mousemove(int x, int y, void *param);
int			handle_on_mousedown(int button, int x, int y, void *param);
#endif
