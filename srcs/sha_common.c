/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_common.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:00:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 13:13:02 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha_common.h"

void	sha_generate_w32(uint32_t w[], uint32_t block[])
{
	size_t			i;
	uint32_t		s0;
	uint32_t		s1;

	i = -1;
	while (++i < 16)
	{
		if (endian() == SHA_ENDIAN)
			w[i] = block[i];
		else
			w[i] = lb_converter(block[i]);
	}
	i = 15;
	while (++i < 64)
	{
		s0 = rotate_right(w[i - 15], 7) ^ rotate_right(w[i - 15], 18)
														^ (w[i - 15] >> 3);
		s1 = rotate_right(w[i - 2], 17) ^ rotate_right(w[i - 2], 19)
														^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
}

void	sha_generate_w64(uint64_t w[], uint64_t block[])
{
	size_t			i;
	uint32_t		s0;
	uint32_t		s1;

	i = -1;
	while (++i < 16)
	{
		if (endian() == SHA_ENDIAN)
			w[i] = block[i];
		else
			w[i] = lb_converter(block[i]);
	}
	i = 15;
	while (++i < 80)
	{
		s0 = rotate_right(w[i - 15], 7) ^ rotate_right(w[i - 15], 18)
														^ (w[i - 15] >> 3);
		s1 = rotate_right(w[i - 2], 17) ^ rotate_right(w[i - 2], 19)
														^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
}
