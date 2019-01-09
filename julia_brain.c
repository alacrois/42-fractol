/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_brain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 22:35:08 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/11 22:41:04 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_complex	new_julia_argument(t_complex arg)
{
	t_complex		new;

	new.im = 0;
	arg.real = arg.real + (arg.im / 4);
	arg.real = arg.real / 20;
	if (arg.real < 0)
		arg.real = -arg.real;
	while (arg.real < 0.25)
		arg.real = arg.real + 0.125;
	while (arg.real > 0.5)
		arg.real = arg.real - 0.25;
	new.real = arg.real;
	return (new);
}

static int			get_j_divergence(t_complex c, t_complex j_arg, \
					int iterations)
{
	int				i;
	t_complex		z;
	double			tmp;
	t_complex		new_j_arg;

	i = -1;
	z.real = c.real;
	z.im = c.im;
	new_j_arg = new_julia_argument(j_arg);
	while (++i < iterations)
	{
		tmp = (z.real * z.real) - (z.im * z.im) + (new_j_arg.real / 1);
		z.im = (-3.7 * (z.real * z.im)) + (new_j_arg.im / 1);
		z.real = tmp;
		if (((z.real * z.real) + (z.im * z.im)) > 4)
			return (i);
	}
	return (i);
}

void				julia_brain(t_hook_arg *harg, t_point pix, \
					t_point origin, double limit)
{
	t_complex		c;
	t_rgb			color;
	int				divergence;
	t_fractal		*f;

	f = (t_fractal *)harg->data;
	color.r = 0;
	color.g = (char)255;
	color.b = 0;
	color.trans = 0;
	c.real = ((double)pix.x / limit) / f->zoom;
	c.im = ((double)pix.y / limit) / f->zoom;
	c.real = c.real + f->center.x;
	c.im = c.im + f->center.y;
	divergence = get_j_divergence(c, f->julia_arg, f->max_iterations);
	color = fractal_color(harg, divergence);
	ftx_img_pixel_put(harg->i, origin.x + pix.x, origin.y + pix.y, color);
}
