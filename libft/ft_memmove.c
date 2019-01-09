/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:35:08 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:24:37 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	void	*tmp;

	i = 0;
	if (dst == NULL || src == NULL)
		return (NULL);
	tmp = ft_memalloc(len);
	if (tmp == NULL)
		return (NULL);
	while (i < len)
	{
		*((char *)tmp + i) = *((char *)src + i);
		i++;
	}
	i = 0;
	while (i < len)
	{
		*((char *)dst + i) = *((char *)tmp + i);
		i++;
	}
	ft_memdel(&tmp);
	return (dst);
}
