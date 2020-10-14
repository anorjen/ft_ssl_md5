/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:19:19 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/14 19:10:39 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void		ft_swap(uint8_t *one, uint8_t *two)
{
	uint8_t	buf;

	buf = *one;
	*one = *two;
	*two = buf;
}

int			endian(void)
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

uint32_t	lb_conv4(uint32_t a)
{
	return (((a << 24) & 0xff000000) | ((a << 8) & 0x00ff0000)
			| ((a >> 24) & 0x000000ff) | ((a >> 8) & 0x0000ff00));
}

uint64_t	lb_conv8(uint64_t a)
{
	return (
	((a << 56) & 0xff00000000000000) | ((a << 40) & 0x00ff000000000000)
	| ((a << 24) & 0x0000ff0000000000) | ((a << 8) & 0x000000ff00000000)
	| ((a >> 56) & 0x00000000000000ff) | ((a >> 40) & 0x000000000000ff00)
	| ((a >> 24) & 0x0000000000ff0000) | ((a >> 8) & 0x00000000ff000000));
}
