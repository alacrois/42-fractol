/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:08:56 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 00:02:39 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			movement(t_hook_arg *harg, int k)
{
	t_fractal	*f;

	f = (t_fractal *)harg->data;
	if (f->type < 2 || f->type > 4 || f->vary_argument == false)
	{
		if (k == 123)
			f->center.x = f->center.x - (0.125 / f->zoom);
		if (k == 124)
			f->center.x = f->center.x + (0.125 / f->zoom);
		if (k == 125)
			f->center.y = f->center.y + (0.125 / f->zoom);
		if (k == 126)
			f->center.y = f->center.y - (0.125 / f->zoom);
	}
}

static void		print_instructions(t_fractal *f)
{
	if (f->print_instructions == false)
		return ;
	ft_putstr("=================================== FRACTOL COMMANDS");
	ft_putstr(" ===================================\n");
	ft_putstr("========================== Zoom in/out on point: mouse ");
	ft_putstr("wheel ===========================\n");
	ft_putstr("================ Enable/disable variation of argument");
	ft_putstr(" : spacebar [Julia] ===============\n");
	ft_putstr("======================  Change maximum iteration (+/-)");
	ft_putstr(" : '+' / '-' =====================\n");
	ft_putstr("=============== Keys to change color variables rf, gf, bf & ");
	ft_putstr("rgbf (+/-) : ===============\n");
	ft_putstr("================= rf('1'/'2'), gf('3'/'4'), bf('5'/'6'), ");
	ft_putstr("rgbf('7'/'8') =================\n");
	ft_putstr("===================== Press [TAB] to bound / unbound ");
	ft_putstr("color changes =====================\n");
	ft_putstr("=================== Press [return] to print these ");
	ft_putstr("instructions again ===================\n");
	ft_putstr("========================================================");
	ft_putstr("================================\n\n");
	f->print_instructions = false;
}

void			print_infos(t_hook_arg *harg)
{
	t_fractal	*f;

	f = (t_fractal *)harg->data;
	print_instructions(f);
	if (VERBOSE == true && (f->type < 2 || f->type > 4 || \
							f->vary_argument == false))
	{
		ft_putstr("(int)f->zoom = ");
		ft_putstr_free(ft_itoa((int)f->zoom));
		ft_putstr(" && f->max_iterations = ");
		ft_putstr_free(ft_itoa(f->max_iterations));
		ft_putstr("\n");
	}
}
