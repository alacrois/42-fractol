/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 21:15:09 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/11 18:22:43 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static double		diff(t_complex a, t_complex b)
{
	t_complex		tmp;

	tmp.real = a.real - b.real;
	if (tmp.real < 0)
		tmp.real = -tmp.real;
	tmp.im = a.im - b.im;
	if (tmp.im < 0)
		tmp.im = -tmp.im;
	return (module_sq(tmp));
}

static t_complex	c_multiply(t_complex a, t_complex b)
{
	t_complex		new;

	new.real = (a.real * b.real) - (a.im * b.im);
	new.im = (a.real * b.im) + (a.im * b.real);
	return (new);
}

static t_complex	newton_poly(t_complex a)
{
	t_complex		tmp;
	t_complex		b;

	b.real = -1;
	b.im = 0;
	tmp = complex_sq(a);
	tmp = c_multiply(tmp, a);
	tmp = complex_add(tmp, b);
	return (tmp);
}

static int			get_n_divergence(t_complex c, int iterations)
{
	int				i;
	t_complex		z;
	t_complex		zero;

	zero.real = 0;
	zero.im = 0;
	z = newton_poly(c);
	i = -1;
	while (++i < (iterations / 50))
		z = newton_poly(z);
	return ((((int)diff(z, zero))) % iterations);
}

void				newton(t_hook_arg *harg, t_point pix, t_point origin, \
					double limit)
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
	divergence = get_n_divergence(c, f->max_iterations);
	color = fractal_color(harg, divergence);
	ftx_img_pixel_put(harg->i, origin.x + pix.x, origin.y + pix.y, color);
}
