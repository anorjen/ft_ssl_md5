/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:19:19 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 12:03:33 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void			ft_swap(uint8_t *one, uint8_t *two)
{
	uint8_t	buf;

	buf = *one;
	*one = *two;
	*two = buf;
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
