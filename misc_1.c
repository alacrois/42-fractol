/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:15:41 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 01:05:08 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			vary_colors(t_colors *c, int k)
{
	if (k == 18)
		c->rf = c->rf * COLOR_CHANGE_FACTOR;
	else if (k == 19)
		c->rf = c->rf / COLOR_CHANGE_FACTOR;
	else if (k == 20)
		c->gf = c->gf * COLOR_CHANGE_FACTOR;
	else if (k == 21)
		c->gf = c->gf / COLOR_CHANGE_FACTOR;
	else if (k == 23)
		c->bf = c->bf * COLOR_CHANGE_FACTOR;
	else if (k == 22)
		c->bf = c->bf / COLOR_CHANGE_FACTOR;
	else if (k == 26)
		c->rgbf = c->rgbf * COLOR_CHANGE_FACTOR;
	else if (k == 28)
		c->rgbf = c->rgbf / COLOR_CHANGE_FACTOR;
	else if (k == 48)
		c->bounded = -c->bounded;
}

static void		bound(int *r, int *g, int *b)
{
	if (*r > 255)
		*r = 255;
	if (*g > 255)
		*g = 255;
	if (*b > 255)
		*b = 255;
}

t_rgb			fractal_color(t_hook_arg *harg, int d)
{
	t_rgb		color;
	int			r;
	int			g;
	int			b;
	t_colors	cf;

	r = 0;
	g = 0;
	b = 0;
	cf = ((t_fractal *)harg->data)->colors;
	if (d < ((t_fractal *)harg->data)->max_iterations)
	{
		r = (cf.rf * d + cf.rf) * cf.rgbf;
		g = (cf.gf * d + cf.gf) * cf.rgbf;
		b = (cf.bf * d + cf.bf) * cf.rgbf;
	}
	if (cf.bounded == 1)
		bound(&r, &g, &b);
	color = ft_rgb(r, g, b, 0);
	return (color);
}

double			get_angle(t_dpoint origin, t_dpoint target)
{
	double		angle;
	t_dpoint	gap;

	gap.x = target.x - origin.x;
	gap.y = target.y - origin.y;
	if (gap.x == 0 && gap.y == 0)
		return (0);
	else if (gap.x == 0 && gap.y > 0)
		return (PI / 2);
	else if (gap.x == 0 && gap.y < 0)
		return ((3 * PI) / 2);
	else if (gap.y == 0 && gap.x > 0)
		return (0);
	else if (gap.y == 0 && gap.x < 0)
		return (PI);
	angle = ft_dabs(atan(gap.y / gap.x));
	if (gap.x > 0 && gap.y > 0)
		return (angle);
	else if (gap.x > 0 && gap.y < 0)
		return ((2 * PI) - angle);
	else if (gap.x < 0 && gap.y > 0)
		return (PI - angle);
	else if (gap.x < 0 && gap.y < 0)
		return (PI + angle);
	return (angle);
}
