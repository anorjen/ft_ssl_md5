/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:00:59 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 12:14:37 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224.h"

t_sha224	*sha224_init(void)
{
	int			i;
	t_sha224	*e;

	if ((e = (t_sha224 *)malloc(sizeof(t_sha224))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	i = -1;
	while (++i < 8)
		e->h[i] = g_sha224_init[i];
	return (e);
}

void		sha224_generate_w(t_sha224 *e)
{
	ssize_t			i;
	uint32_t		s0;
	uint32_t		s1;

	i = -1;
	while (++i < 16)
	{
		if (endian() == SHA224_ENDIAN)
			e->w[i] = e->block[i];
		else
			e->w[i] = lb_converter(e->block[i]);
	}
	i = 15;
	while (++i < 64)
	{
		s0 = rotate_right(e->w[i - 15], 7) ^ rotate_right(e->w[i - 15], 18)
														^ (e->w[i - 15] >> 3);
		s1 = rotate_right(e->w[i - 2], 17) ^ rotate_right(e->w[i - 2], 19)
														^ (e->w[i - 2] >> 10);
		e->w[i] = e->w[i - 16] + s0 + e->w[i - 7] + s1;
	}
}
