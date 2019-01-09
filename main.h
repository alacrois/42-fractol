/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:37:43 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 02:11:08 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <pthread.h>

# define VERBOSE false
# define WIN_SIZE_X 1024
# define WIN_SIZE_Y WIN_SIZE_X
# define WIN_TITLE "fractol"
# define THREADS_NB 8
# define DRAW_COLOR 0x00FF00
# define RED_FACTOR 1.4
# define GREEN_FACTOR 1.6
# define COLOR_CHANGE_FACTOR 1.15
# define BLUE_FACTOR 1.4
# define RGB_FACTOR 1.5
# define PI (3.141592653589793)
# define ITERATIONS 100
# define ITERATIONS_MIN 5
# define ITERATIONS_MAX 1000
# define ZOOM_FACTOR 0.2
# define ZOOM_IN (1 + ZOOM_FACTOR)
# define ZOOM_OUT (1 - ZOOM_FACTOR)

typedef struct			s_thread
{
	t_hook_arg			*harg;
	int					th_index;
}						t_thread;

typedef struct			s_complex
{
	double				real;
	double				im;
}						t_complex;

typedef struct			s_snowflake
{
	t_dpoint			p;
	t_point				pixel;
	t_bool				on_screen;
	struct s_snowflake	*prev;
	struct s_snowflake	*next;
}						t_snowflake;

typedef struct			s_colors
{
	double				rf;
	double				gf;
	double				bf;
	double				rgbf;
	int					bounded;
}						t_colors;

typedef struct			s_fractal
{
	int					thread_index;
	int					color_arg;
	int					max_iterations;
	t_bool				print_instructions;
	t_colors			colors;
	int					button;
	t_bool				z_event;
	t_bool				vary_argument;
	int					type;
	t_dpoint			center;
	double				old_zoom;
	double				zoom;
	t_point				mouse;
	t_point				old_mouse;
	t_complex			julia_arg;
}						t_fractal;

void					s_link(t_snowflake *a, t_snowflake *b);
void					snowflake_init(t_hook_arg *harg, t_snowflake **a, \
						t_snowflake **b, t_snowflake **c);
void					get_s_points(t_hook_arg *harg, t_snowflake *a, \
						t_snowflake *b);
void					free_s_points(t_snowflake *a);
t_bool					adjacent(t_snowflake *sf_a, t_snowflake *sf_b);
t_bool					on_screen(t_point p);
void					snowflake(t_hook_arg *harg);

t_complex				complex_add(t_complex a, t_complex b);
t_complex				complex_sq(t_complex a);
double					module_sq(t_complex z);
t_complex				newton_function(t_fractal *f, t_complex a);

t_rgb					fractal_color(t_hook_arg *harg, int d);
double					get_angle(t_dpoint origin, t_dpoint target);

int						expose_hook(t_hook_arg *harg);
int						key_hook(int keycode, t_hook_arg *harg);
int						mouse_hook(int button, int x, int y, t_hook_arg *harg);
int						motion_hook(int x, int y, t_hook_arg *harg);
int						loop_hook(t_hook_arg *harg);

void					print_infos(t_hook_arg *harg);
void					update_window(t_hook_arg *harg);

void					julia(t_hook_arg *harg, t_point pix, t_point origin, \
						double limit);
void					julia_brain(t_hook_arg *harg, t_point pix, \
						t_point origin, double limit);
void					julia_wtf(t_hook_arg *harg, t_point pix, \
						t_point origin, double limit);
void					mandelbrot(t_hook_arg *harg, t_point pix, \
						t_point origin, double limit);
void					mega_mandelbrot(t_hook_arg *harg, t_point pix, \
						t_point origin, double limit);
void					tricorn(t_hook_arg *harg, t_point pix, t_point origin, \
						double limit);
void					burning_ship(t_hook_arg *harg, t_point pix, \
						t_point origin, double limit);
void					newton(t_hook_arg *harg, t_point pix, t_point origin, \
						double limit);
void					vary_colors(t_colors *c, int k);
void					movement(t_hook_arg *harg, int k);

void					init_t_fractal(t_fractal *f);
#endif
