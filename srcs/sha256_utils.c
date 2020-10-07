/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:00:59 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:49:31 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

t_sha256	*sha256_init(void)
{
	int			i;
	t_sha256	*e;

	if ((e = (t_sha256 *)malloc(sizeof(t_sha256))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	i = -1;
	while (++i < 8)
		e->h[i] = g_h_init[i];
	return (e);
}

void		generate_w(t_sha256 *e)
{
	ssize_t			i;
	uint32_t		s0;
	uint32_t		s1;

	i = -1;
	while (++i < 16)
	{
		g_w[i] = lb_converter(e->block[i]);
	}
	i = 15;
	while (++i < 64)
	{
		s0 = rotate_right(g_w[i - 15], 7) ^ rotate_right(g_w[i - 15], 18)
														^ (g_w[i - 15] >> 3);
		s1 = rotate_right(g_w[i - 2], 17) ^ rotate_right(g_w[i - 2], 19)
														^ (g_w[i - 2] >> 10);
		g_w[i] = g_w[i - 16] + s0 + g_w[i - 7] + s1;
	}
}
