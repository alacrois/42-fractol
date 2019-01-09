/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 14:24:07 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 00:00:17 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				init_t_fractal(t_fractal *f)
{
	f->max_iterations = ITERATIONS;
	f->old_zoom = 0.67;
	f->zoom = 0.67;
	f->z_event = false;
	f->vary_argument = true;
	f->center.x = 0;
	f->center.y = 0;
	if (f->type == 0)
		f->center.x = -0.75;
	else if (f->type == 6)
	{
		f->center.x = -1;
		f->center.y = -0.5;
	}
	f->colors.rf = RED_FACTOR * (f->color_arg % 2) + 1;
	f->colors.gf = GREEN_FACTOR * (f->color_arg % 4) + 1;
	f->colors.bf = BLUE_FACTOR * (f->color_arg % 3) + 1;
	f->colors.rgbf = RGB_FACTOR * (f->color_arg % 2) + 1;
	f->colors.bounded = 1;
}

static void			usage(char *s)
{
	ft_putendl(s);
	ft_putendl("usage : ./fractol [012345678] [color argument]");
	ft_putendl("0 : Mandelbrot\n1 : Mega Mandelbrot\n2 : Julia");
	ft_putendl("3 : Julia Brain\n4 : Julia WTF\n5 : Tricorn");
	ft_exit("6 : Burning_ship\n7 : Snowflake\n8 : Newton");
}

static t_hook_arg	*init_env(t_fractal *f)
{
	t_hook_arg		*harg;

	harg = (t_hook_arg *)malloc(sizeof(t_hook_arg));
	if (harg == NULL)
		ft_exit("Error : malloc error");
	harg->e = (t_env *)ft_memalloc(sizeof(t_env));
	harg->i = (t_img *)malloc(sizeof(t_img));
	if (harg->i == NULL || harg->e == NULL)
		ft_exit("Error : malloc error");
	harg->e->mlx = mlx_init();
	harg->e->win = mlx_new_window(harg->e->mlx, WIN_SIZE_X, WIN_SIZE_Y, \
					WIN_TITLE);
	harg->i->img_p = mlx_new_image(harg->e->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	harg->i->img_str = mlx_get_data_addr(harg->i->img_p, &(harg->i->bpp), \
					&(harg->i->line_size), &(harg->i->endian));
	harg->data = f;
	return (harg);
}

static t_hook_arg	*init(t_fractal *f, int ac, char **av)
{
	t_hook_arg		*harg;

	if (ac == 1)
		usage("Error : argument missing.");
	else if (ac > 3)
		usage("Error : too many arguments.");
	f->type = ft_atoi(av[1]);
	if (ft_isdigit(av[1][0]) == 0 || f->type < 0 || f->type > 8)
		usage("Error : invalid argument.");
	f->print_instructions = true;
	f->color_arg = 1;
	if (ac == 3)
		f->color_arg = ft_atoi(av[2]);
	init_t_fractal(f);
	harg = init_env(f);
	return (harg);
}

int					main(int ac, char **av)
{
	t_hook_arg		*harg;
	t_fractal		f;

	harg = init(&f, ac, av);
	update_window(harg);
	mlx_key_hook(harg->e->win, key_hook, harg);
	mlx_expose_hook(harg->e->win, expose_hook, harg);
	mlx_hook(harg->e->win, 4, (1L << 2), mouse_hook, harg);
	mlx_hook(harg->e->win, 6, (1L << 6), motion_hook, harg);
	mlx_loop_hook(harg->e->mlx, loop_hook, harg);
	mlx_loop(harg->e->mlx);
	return (0);
}
