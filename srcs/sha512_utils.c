/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:00:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 19:11:13 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void	*sha512_append_padding_bits(void *input, uint64_t size, int block_size)
{
	uint8_t	*end;

	end = (uint8_t*)(input) + size;
	*end = 0x80;
	++end;
	while ((end - (uint8_t*)(input)) % block_size != (block_size - 16))
	{
		*end = 0x00;
		++end;
	}
	return (end);
}

void	*sha512_append_length(void *end, uint64_t size, int endian_type)
{
	__uint128_t	length;

	length = (size * 8);
	ft_memcpy((void*)(end), &length, 16);
	if (endian() != endian_type)
	{
		ft_swap(end, end + 15);
		ft_swap(end + 1, end + 14);
		ft_swap(end + 2, end + 13);
		ft_swap(end + 3, end + 12);
		ft_swap(end + 4, end + 11);
		ft_swap(end + 5, end + 10);
		ft_swap(end + 6, end + 9);
		ft_swap(end + 7, end + 8);
	}
	end += 16;
	return (end);
}

void	sha512_generate_w(uint64_t w[], uint64_t block[])
{
	size_t	i;

	i = -1;
	while (++i < 16)
		w[i] = (endian() == SHA512_ENDIAN ? block[i] : LB_CONV64(block[i]));
	i = 15;
	while (++i < 80)
		w[i] = w[i - 16] + SHA512_D0(w[i - 15]) + w[i - 7]
												+ SHA512_D1(w[i - 2]);
}
