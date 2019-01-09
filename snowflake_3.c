/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snowflake_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:42:04 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/04 20:47:53 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			s_link(t_snowflake *a, t_snowflake *b)
{
	a->next = b;
	b->prev = a;
}

t_bool			on_screen(t_point p)
{
	if (p.x < 0 || p.x > (WIN_SIZE_X - 1))
		return (false);
	if (p.y < 0 || p.y > (WIN_SIZE_Y - 1))
		return (false);
	return (true);
}

void			free_s_points(t_snowflake *a)
{
	t_snowflake	*tmp;
	t_snowflake	*p_tmp;
	t_snowflake	*elem;

	elem = a;
	while (elem != NULL)
	{
		p_tmp = elem->prev;
		tmp = elem->next;
		free(elem);
		if (p_tmp != NULL)
			p_tmp->next = NULL;
		if (tmp != NULL)
			tmp->prev = NULL;
		elem = tmp;
	}
}

t_bool			adjacent(t_snowflake *sf_a, t_snowflake *sf_b)
{
	int		dist;
	t_point	a;
	t_point	b;

	a = sf_a->pixel;
	b = sf_b->pixel;
	dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	if (dist <= 2)
		return (true);
	return (false);
}
