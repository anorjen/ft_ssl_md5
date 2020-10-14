/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:07:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/14 18:30:37 by anorjen          ###   ########.fr       */
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
	if (endian() != endian_type)
	{
		length = lb_conv8(length);
	}
	ft_memcpy((void*)(end), &length, 8);
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
	if ((ret = (char *)malloc(sizeof(char) * (output_size + 1))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
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

void	u64_to_u8(uint8_t *hash, uint64_t h, int i, int endian_type)
{
	if (endian() == endian_type)
	{
		hash[i * 8 + 0] = (uint8_t)(h >> 0);
		hash[i * 8 + 1] = (uint8_t)(h >> 8);
		hash[i * 8 + 2] = (uint8_t)(h >> 16);
		hash[i * 8 + 3] = (uint8_t)(h >> 24);
		hash[i * 8 + 4] = (uint8_t)(h >> 32);
		hash[i * 8 + 5] = (uint8_t)(h >> 40);
		hash[i * 8 + 6] = (uint8_t)(h >> 48);
		hash[i * 8 + 7] = (uint8_t)(h >> 56);
	}
	else
	{
		hash[i * 8 + 0] = (uint8_t)(h >> 56);
		hash[i * 8 + 1] = (uint8_t)(h >> 48);
		hash[i * 8 + 2] = (uint8_t)(h >> 40);
		hash[i * 8 + 3] = (uint8_t)(h >> 32);
		hash[i * 8 + 4] = (uint8_t)(h >> 24);
		hash[i * 8 + 5] = (uint8_t)(h >> 16);
		hash[i * 8 + 6] = (uint8_t)(h >> 8);
		hash[i * 8 + 7] = (uint8_t)(h >> 0);
	}
}
