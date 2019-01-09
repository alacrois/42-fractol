/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snowflake_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:31:32 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/05 17:19:41 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_dpoint	rotate_240(t_dpoint a, t_dpoint origin)
{
	t_dpoint	b;
	double		dist;
	double		angle;

	angle = get_angle(origin, a) - ((2 * PI) / 3);
	dist = (a.x - origin.x) * (a.x - origin.x) + \
			(a.y - origin.y) * (a.y - origin.y);
	dist = sqrt(dist);
	b.x = origin.x + cos(angle) * dist;
	b.y = origin.y + sin(angle) * dist;
	return (b);
}

static t_dpoint	between(t_dpoint a, t_dpoint b, double distance)
{
	t_dpoint	gap;
	t_dpoint	p;

	gap.x = b.x - a.x;
	gap.y = b.y - a.y;
	p.x = a.x + ((double)distance * gap.x);
	p.y = a.y + ((double)distance * gap.y);
	return (p);
}

static void		get_pix_coordinates(t_hook_arg *harg, t_snowflake *a)
{
	int			limit;
	t_fractal	*f;

	f = ((t_fractal *)harg->data);
	limit = (WIN_SIZE_Y / 2) - 1;
	a->pixel.x = (WIN_SIZE_X / 2) + \
				(((-f->center.x / 2) + a->p.x) * limit) * f->zoom;
	a->pixel.y = (WIN_SIZE_Y / 2) - \
				(((f->center.y / 2) + a->p.y) * limit) * f->zoom;
	a->on_screen = on_screen(a->pixel);
}

void			snowflake_init(t_hook_arg *harg, t_snowflake **a, \
				t_snowflake **b, t_snowflake **c)
{
	(*a) = (t_snowflake *)malloc(sizeof(t_snowflake));
	(*c) = (t_snowflake *)malloc(sizeof(t_snowflake));
	(*b) = (t_snowflake *)malloc(sizeof(t_snowflake));
	if ((*a) == NULL || (*b) == NULL || (*c) == NULL)
		ft_exit("malloc error");
	(*a)->p.x = 0;
	(*a)->p.y = 1;
	(*b)->p.x = cos((11 * PI) / 6);
	(*b)->p.y = sin((11 * PI) / 6);
	(*c)->p.x = cos((7 * PI) / 6);
	(*c)->p.y = sin((7 * PI) / 6);
	s_link(*a, *b);
	s_link(*b, *c);
	s_link(*c, *a);
	(*a)->on_screen = true;
	(*b)->on_screen = true;
	(*c)->on_screen = true;
	get_pix_coordinates(harg, *a);
	get_pix_coordinates(harg, *b);
	get_pix_coordinates(harg, *c);
}

void			get_s_points(t_hook_arg *harg, t_snowflake *a, t_snowflake *b)
{
	t_snowflake	*new_a;
	t_snowflake	*new_b;
	t_snowflake	*new_c;
	double		one_third;
	double		two_third;

	snowflake_init(harg, &new_a, &new_b, &new_c);
	s_link(a, new_a);
	s_link(new_a, new_b);
	s_link(new_b, new_c);
	s_link(new_c, b);
	one_third = (double)1 / (double)3;
	two_third = (double)2 / (double)3;
	new_a->p = between(a->p, b->p, one_third);
	new_c->p = between(a->p, b->p, two_third);
	new_b->p = rotate_240(a->p, new_a->p);
	get_pix_coordinates(harg, new_a);
	get_pix_coordinates(harg, new_b);
	get_pix_coordinates(harg, new_c);
}
