/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 21:31:34 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/11 18:24:10 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static double	d_abs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static int		get_bs_divergence(t_complex c, int iterations)
{
	int			i;
	t_complex	z;
	double		tmp;

	i = -1;
	z.real = 0;
	z.im = 0;
	while (++i < iterations)
	{
		tmp = d_abs((z.real * z.real) - (z.im * z.im)) + c.real;
		z.im = (2 * (d_abs(z.real) * d_abs(z.im))) + c.im;
		z.real = tmp;
		if (((z.real * z.real) + (z.im * z.im)) > 4)
			return (i);
	}
	return (i);
}

void			burning_ship(t_hook_arg *harg, t_point pix, t_point origin, \
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
	divergence = get_bs_divergence(c, f->max_iterations);
	color = fractal_color(harg, divergence);
	ftx_img_pixel_put(harg->i, origin.x + pix.x, origin.y + pix.y, color);
}
