/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:35:41 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 02:05:40 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				expose_hook(t_hook_arg *harg)
{
	update_window(harg);
	return (0);
}

int				key_hook(int keycode, t_hook_arg *harg)
{
	t_fractal	*f;

	f = (t_fractal *)harg->data;
	if (keycode == 53)
		exit(0);
	if (keycode == 49 && f->vary_argument == true)
		f->vary_argument = false;
	else if (keycode == 49 && f->vary_argument == false)
		f->vary_argument = true;
	movement(harg, keycode);
	if (keycode == 24)
		f->max_iterations = f->max_iterations * 1.1 + 1;
	else if (keycode == 27)
		f->max_iterations = f->max_iterations * 0.9 - 1;
	if (f->max_iterations > ITERATIONS_MAX)
		f->max_iterations = ITERATIONS_MAX;
	if (f->max_iterations < ITERATIONS_MIN)
		f->max_iterations = ITERATIONS_MIN;
	if (keycode == 36)
		f->print_instructions = true;
	vary_colors(&(f->colors), keycode);
	update_window(harg);
	return (0);
}

int				mouse_hook(int button, int x, int y, t_hook_arg *harg)
{
	t_fractal	*f;

	f = ((t_fractal *)harg->data);
	if (button == 4 && f->z_event == false)
		f->zoom = ZOOM_IN * f->zoom;
	else if (button == 5 && f->z_event == false)
		f->zoom = ZOOM_OUT * f->zoom;
	else if (button == 3)
	{
		init_t_fractal(f);
		update_window(harg);
	}
	if (f->zoom < 0.67)
		f->zoom = 0.67;
	if (button == 4 || button == 5)
	{
		f->mouse.x = x;
		f->mouse.y = y;
		f->z_event = true;
	}
	return (0);
}

int				motion_hook(int x, int y, t_hook_arg *harg)
{
	t_fractal	*f;

	f = ((t_fractal *)harg->data);
	f->mouse.x = x;
	f->mouse.y = y;
	return (0);
}

int				loop_hook(t_hook_arg *harg)
{
	t_fractal	*f;

	f = (t_fractal *)harg->data;
	if (f->old_zoom != f->zoom)
	{
		update_window(harg);
		f->old_zoom = f->zoom;
	}
	if (f->vary_argument == true && f->type >= 2 && f->type <= 4 && \
		(f->mouse.x != f->old_mouse.x || f->mouse.y != f->old_mouse.y))
	{
		update_window(harg);
		f->old_mouse = f->mouse;
	}
	f->z_event = false;
	return (0);
}
