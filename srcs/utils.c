/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:19:19 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 19:47:05 by anorjen          ###   ########.fr       */
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

uint64_t		rotate_right64(uint64_t x, uint64_t s)
{
	return ((x >> s) | x << (64 - s));
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

// uint64_t		lb_converter64(uint64_t a)
// {
// 	// uint8_t		*aa;

// 	// aa = (uint8_t*)&a;
// 	// ft_swap(&(aa[0]), &(aa[7]));
// 	// ft_swap(&(aa[1]), &(aa[6]));
// 	// ft_swap(&(aa[2]), &(aa[5]));
// 	// ft_swap(&(aa[3]), &(aa[4]));

// 	return ((a << 56) & 0xff00000000000000) | ((a << 40) & 0x00ff000000000000)
// 			| ((a << 24) & 0x0000ff0000000000) | ((a << 8) & 0x000000ff00000000)
// 			| ((a >> 56) & 0x00000000000000ff) | ((a >> 40) & 0x000000000000ff00)
// 			| ((a >> 24) & 0x0000000000ff0000) | ((a >> 8) & 0x00000000ff000000);
// }

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
