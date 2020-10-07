/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:19:19 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 18:48:59 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint32_t		rotate_left(uint32_t x, uint32_t s)
{
	return ((x << s) | (x >> (32 - s)));
}

uint32_t		rotate_right(uint32_t x, uint32_t s)
{
	return ((x >> s) | x << (32 - s));
}

void			ft_swap(uint8_t *one, uint8_t *two)
{
	uint8_t	buf;

	buf = *one;
	*one = *two;
	*two = buf;
}

uint32_t		lb_converter(uint32_t a)
{
	uint8_t		*aa;

	aa = (uint8_t*)&a;
	ft_swap(&(aa[0]), &(aa[3]));
	ft_swap(&(aa[1]), &(aa[2]));
	return (a);
}

int				endian(void)
{
	uint32_t	i;
	uint8_t		*p;

	i = 1;
	p = (uint8_t*)&i;
	if (*p == 1)
		return (L_ENDIAN);
	else
		return (B_ENDIAN);
}
