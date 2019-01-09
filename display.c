/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:43:26 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 01:42:32 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		draw(t_hook_arg *harg, t_point pix, t_point origin)
{
	int			fractal_type;
	double		limit;

	fractal_type = ((t_fractal *)harg->data)->type;
	limit = (double)((WIN_SIZE_Y / 2) - 1);
	if (fractal_type == 0)
		mandelbrot(harg, pix, origin, limit);
	else if (fractal_type == 1)
		mega_mandelbrot(harg, pix, origin, limit);
	else if (fractal_type == 2)
		julia(harg, pix, origin, limit);
	else if (fractal_type == 3)
		julia_brain(harg, pix, origin, limit);
	else if (fractal_type == 4)
		julia_wtf(harg, pix, origin, limit);
	else if (fractal_type == 5)
		tricorn(harg, pix, origin, limit);
	else if (fractal_type == 6)
		burning_ship(harg, pix, origin, limit);
	else if (fractal_type == 8)
		newton(harg, pix, origin, limit);
	else
		ftx_img_pixel_put(harg->i, origin.x + pix.x, \
		origin.y + pix.y, ft_rgb(0, 0, 0, 0));
}

static void		*draw_fractal_core(void *arg)
{
	t_point		origin;
	t_point		pix;
	int			i;
	t_thread	th;
	t_hook_arg	*harg;

	th = *((t_thread *)arg);
	harg = th.harg;
	origin.x = WIN_SIZE_X / 2;
	origin.y = WIN_SIZE_Y / 2;
	pix.y = -((WIN_SIZE_Y / 2) - 1) - 1;
	while (++pix.y < ((WIN_SIZE_Y / 2) - 1))
	{
		i = -(WIN_SIZE_Y / 2);
		while (i < (WIN_SIZE_Y / 2))
		{
			pix.x = i + th.th_index;
			draw(harg, pix, origin);
			i = i + THREADS_NB;
		}
	}
	pthread_exit(NULL);
}

static void		draw_fractal(t_hook_arg *harg, int fractal_type)
{
	pthread_t	threads[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;

	i = 0;
	while (i < THREADS_NB)
	{
		th_arg[i].harg = harg;
		th_arg[i].th_index = i;
		if (pthread_create(&(threads[i]), NULL, draw_fractal_core, \
			&th_arg[i]) != 0)
			ft_exit("Thread could not be created.");
		i++;
	}
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			ft_exit("Thread could not be joined.");
	}
	if (fractal_type == 7)
		snowflake(harg);
	print_infos(harg);
	mlx_put_image_to_window(harg->e, harg->e->win, harg->i->img_p, 0, 0);
}

void			update_window(t_hook_arg *harg)
{
	t_fractal	*f;
	double		limit;
	t_dpoint	shift;
	double		adjust;

	f = (t_fractal *)harg->data;
	limit = (double)((WIN_SIZE_Y / 2) - 1);
	if (f->z_event == true)
	{
		shift.x = (((double)f->mouse.x - limit) / limit) / f->zoom;
		shift.y = (((double)f->mouse.y - limit) / limit) / f->zoom;
		adjust = ZOOM_FACTOR;
		if (f->type == 7)
			adjust = ZOOM_FACTOR * 2;
		if (f->old_zoom > f->zoom)
			adjust = -adjust;
		f->center.x = f->center.x + (shift.x * adjust);
		f->center.y = f->center.y + (shift.y * adjust);
	}
	if (f->type >= 2 && f->type <= 4 && f->vary_argument == true)
	{
		f->julia_arg.real = ((double)(f->mouse.x - limit) / limit) / f->zoom;
		f->julia_arg.im = ((double)(f->mouse.y - limit) / limit) / f->zoom;
	}
	draw_fractal(harg, f->type);
}
