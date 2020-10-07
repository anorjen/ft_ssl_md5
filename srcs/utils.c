/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:19:19 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 19:35:14 by anorjen          ###   ########.fr       */
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

// uint32_t		b_to_l_endian(uint32_t a)
// {
// 	uint32_t	b;
// 	uint8_t		*aa;
// 	uint8_t		bb[4];
// 	int			i;

// 	aa = (uint8_t*)&a;
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		bb[i] = ((aa[i] & 0xf) << 4) | ((aa[i] & 0xf0) >> 4);
// 	}
// 	memcpy(&b, bb, 4);
// 	return (b);
// }

uint32_t		l_to_b_endian(uint32_t a)
{
	uint8_t		*aa;
	uint8_t		tmp;

	aa = (uint8_t*)&a;
	tmp = aa[0];
	aa[0] = aa[3];
	aa[3] = tmp;
	tmp = aa[1];
	aa[1] = aa[2];
	aa[2] = tmp;
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
