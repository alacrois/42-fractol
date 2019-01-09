/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snowflake.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 20:50:34 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/04 19:28:00 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		draw_line(t_hook_arg *harg, t_snowflake *a, t_snowflake *b)
{
	t_rgb		color;

	color.r = (char)255;
	color.g = (char)255;
	color.b = (char)255;
	color.trans = 0;
	if (a->on_screen == true && b->on_screen == true)
		ftx_img_draw_line(harg->i, a->pixel, b->pixel, color);
}

static t_bool	add_points_core(t_hook_arg *harg, t_snowflake **tmp, \
				int check_d, t_bool *any_on_screen)
{
	t_snowflake	*tmp_next;

	if ((*tmp)->on_screen == true)
		*any_on_screen = true;
	tmp_next = (*tmp)->next;
	if (check_d == 0 || (*tmp)->on_screen == true || \
		(*tmp)->next->on_screen == true)
		get_s_points(harg, *tmp, (*tmp)->next);
	*tmp = tmp_next;
	if (check_d == 1 && (*tmp)->on_screen == true && \
		adjacent(*tmp, (*tmp)->next) == true)
		return (true);
	return (false);
}

static void		add_points(t_hook_arg *harg, t_snowflake **sf, int depth, \
				int check_d)
{
	t_snowflake	*tmp;
	int			i;
	t_bool		exit_loop;
	t_bool		depth_max;
	t_bool		any_on_screen;

	tmp = *sf;
	i = -1;
	depth_max = false;
	any_on_screen = true;
	while (++i < depth && depth_max == false)
	{
		if (i > 5 && check_d == 1 && any_on_screen == false)
			return ;
		any_on_screen = false;
		exit_loop = false;
		tmp = *sf;
		while (exit_loop == false)
		{
			if (add_points_core(harg, &tmp, check_d, &any_on_screen) == true)
				depth_max = true;
			if (tmp == *sf)
				exit_loop = true;
		}
	}
}

void			snowflake(t_hook_arg *harg)
{
	t_snowflake	*a;
	t_snowflake	*b;
	t_snowflake	*c;
	t_snowflake *tmp;
	t_fractal	*f;

	f = ((t_fractal *)harg->data);
	snowflake_init(harg, &a, &b, &c);
	add_points(harg, &a, 6, 0);
	add_points(harg, &a, (int)f->zoom, 1);
	tmp = a;
	tmp->prev->next = NULL;
	ftx_img_clear(harg->i, WIN_SIZE_X, WIN_SIZE_Y);
	while (tmp != NULL)
	{
		draw_line(harg, tmp, tmp->prev);
		tmp = tmp->next;
	}
	free_s_points(a);
}
