/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:44:53 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/11 18:25:27 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double			module_sq(t_complex z)
{
	return ((z.real * z.real) + (z.im * z.im));
}

t_complex		complex_sq(t_complex a)
{
	t_complex	b;

	b.real = (a.real * a.real) - (a.im * a.im);
	b.im = 2 * (a.real * a.im);
	return (b);
}

t_complex		complex_add(t_complex a, t_complex b)
{
	t_complex	c;

	c.real = a.real + b.real;
	c.im = a.im + b.im;
	return (c);
}
