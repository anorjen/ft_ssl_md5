/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:07:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:50:16 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	*append_padding_bits(void *input, uint64_t size, int block_size)
{
	uint8_t	*end;

	end = (uint8_t*)(input) + size;
	*end = 0x80;
	++end;
	while ((end - (uint8_t*)(input)) % block_size != (block_size - 8))
	{
		*end = 0x00;
		++end;
	}
	return (end);
}

void	*append_length(void *end, uint64_t size, int endian_type)
{
	uint64_t	length;

	length = size * 8;
	memcpy((void*)(end), &length, 8);
	if (endian() != endian_type)
	{
		ft_swap(end, end + 7);
		ft_swap(end + 1, end + 6);
		ft_swap(end + 2, end + 5);
		ft_swap(end + 3, end + 4);
	}
	end += 8;
	return (end);
}

char	*hash_to_string(uint8_t *hash, int output_size)
{
	char	*hex_char;
	char	*ret;
	size_t	j;
	int		i;

	hex_char = "0123456789abcdef";
	j = 0;
	ret = (char *)malloc(sizeof(char) * (output_size + 1));
	i = -1;
	while (++i < (output_size / 2))
	{
		ret[j++] = hex_char[hash[i] >> 4];
		ret[j++] = hex_char[hash[i] & 0x0F];
	}
	ret[j] = '\0';
	return (ret);
}

void	u32_to_u8(uint8_t *hash, uint32_t h, int i, int endian_type)
{
	if (endian() == endian_type)
	{
		hash[i * 4 + 0] = (uint8_t)(h >> 0);
		hash[i * 4 + 1] = (uint8_t)(h >> 8);
		hash[i * 4 + 2] = (uint8_t)(h >> 16);
		hash[i * 4 + 3] = (uint8_t)(h >> 24);
	}
	else
	{
		hash[i * 4 + 0] = (uint8_t)(h >> 24);
		hash[i * 4 + 1] = (uint8_t)(h >> 16);
		hash[i * 4 + 2] = (uint8_t)(h >> 8);
		hash[i * 4 + 3] = (uint8_t)(h >> 0);
	}
}