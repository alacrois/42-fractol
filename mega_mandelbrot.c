/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 21:39:33 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/11 21:39:34 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		get_mm_divergence(t_complex c, int iterations)
{
	int			i;
	t_complex	z;
	double		tmp;

	i = -1;
	z.real = 0;
	z.im = 0;
	while (++i < iterations)
	{
		tmp = (z.real * z.real) - (z.im * z.im) + c.real;
		z.im = (2 * (z.real * z.im)) + c.im;
		z.real = tmp;
		z = complex_sq(z);
		if (((z.real * z.real) + (z.im * z.im)) > 4)
			return (i);
	}
	return (i);
}

void			mega_mandelbrot(t_hook_arg *harg, t_point pix, t_point origin, \
				double limit)
{
	t_complex	c;
	t_rgb		color;
	int			divergence;
	t_fractal	*f;

	f = (t_fractal *)harg->data;
	color.r = 0;
	color.g = (char)255;
	color.b = 0;
	color.trans = 0;
	c.real = ((double)pix.x / limit) / f->zoom;
	c.im = ((double)pix.y / limit) / f->zoom;
	c.real = c.real + f->center.x;
	c.im = c.im + f->center.y;
	divergence = get_mm_divergence(c, f->max_iterations);
	color = fractal_color(harg, divergence);
	ftx_img_pixel_put(harg->i, origin.x + pix.x, origin.y + pix.y, color);
}
