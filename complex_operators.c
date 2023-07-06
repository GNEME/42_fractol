/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:14:49 by ggneme            #+#    #+#             */
/*   Updated: 2023/04/24 01:44:07 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	complex_init(double real_part, double im_part, int init_expo)
{
	t_complex	z;

	z.real_part = real_part;
	z.im_part = im_part;
	if (init_expo)
		z.complex_expo.module_pow2 = real_part * real_part + im_part * im_part;
	return (z);
}

t_complex	complex_dot(t_complex z1, t_complex z2)
{
	t_complex		z;

	z.complex_expo.module_pow2 = z1.complex_expo.module_pow2
		* z2.complex_expo.module_pow2;
	z.real_part = z1.real_part * z2.real_part - z1.im_part * z2.im_part;
	z.im_part = z1.real_part * z2.im_part + z1.im_part * z2.real_part;
	return (z);
}

t_complex	complex_add(t_complex z1, t_complex z2)
{
	t_complex	z;

	z = complex_init(z1.real_part + z2.real_part, z1.im_part + z2.im_part, 1);
	return (z);
}

static int	my_atoi(char *str, int *count, int *start)
{
	int	value;
	int	i;
	int	nbr;

	value = 0;
	i = *start;
	nbr = 0;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		value = value * 10 + (str[i] - '0');
		i ++;
		nbr ++;
	}
	*count = nbr;
	*start = i;
	return (value);
}

double	ft_atof(char *str, int is_bonus)
{
	int		i;
	int		nbr;
	double	value;
	int		sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1 * sign;
		i ++;
	}
	else if (str[i] == '+')
		i ++;
	if (!('0' <= str[i] && str[i] <= '9') && str[i] != '.')
		ft_message(is_bonus);
	value = my_atoi(str, &nbr, &i);
	if (str[i] == '.')
		i ++;
	if (!('0' <= str[i] && str[i] <= '9'))
		ft_message(is_bonus);
	value += my_atoi(str, &nbr, &i) * pow(10, -nbr);
	if (str[i])
		ft_message(is_bonus);
	return (sign * value);
}
