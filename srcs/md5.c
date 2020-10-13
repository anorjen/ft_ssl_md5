/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 12:17:53 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

const uint32_t	g_t[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t	g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static void		process_block(t_md5 *e)
{
	ssize_t		i;
	uint32_t	f;

	i = 0;
	while (i < 64)
	{
		if (i >= 0 && i < 16)
			f = ((e->hh[1] & e->hh[2]) | (~(e->hh[1]) & e->hh[3]));
		else if (i >= 16 && i < 32)
			f = ((e->hh[1] & e->hh[3]) | (~(e->hh[3]) & e->hh[2]));
		else if (i >= 32 && i < 48)
			f = (e->hh[1] ^ e->hh[2] ^ e->hh[3]);
		else if (i >= 48 && i < 64)
			f = (e->hh[2] ^ (~(e->hh[3]) | e->hh[1]));
		f = f + e->hh[0] + g_t[i] + e->block[e->g[i]];
		e->hh[0] = e->hh[3];
		e->hh[3] = e->hh[2];
		e->hh[2] = e->hh[1];
		e->hh[1] += ROTL32(f, g_s[i]);
		++i;
	}
}

static void		process(t_md5 *e, void *input, uint64_t size)
{
	uint8_t	*temp;
	uint8_t	*end;
	int		i;

	temp = (uint8_t*)(input);
	end = temp + size;
	while (temp != end)
	{
		memcpy(&(e->block), (void*)(temp), MD5_BLOCK_SIZE);
		i = -1;
		while (++i < 4)
			e->hh[i] = e->h[i];
		process_block(e);
		i = -1;
		while (++i < 4)
			e->h[i] += e->hh[i];
		temp += MD5_BLOCK_SIZE;
	}
}

static uint8_t	*finish(t_md5 *e)
{
	uint8_t	*hash;
	int		i;

	if ((hash = (uint8_t*)malloc(32)) != NULL)
	{
		i = -1;
		while (++i < 4)
		{
			u32_to_u8(hash, e->h[i], i, MD5_ENDIAN);
		}
	}
	free(e);
	return (hash);
}

uint8_t	*md5_calc(t_data *data, const t_hash *hash_handler)
{
	t_md5		*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	(void)hash_handler;
	e = md5_init();
	while ((ret = read_data(data, buf, READ_BLOCK_SIZE)) == READ_BLOCK_SIZE)
	{
		process(e, buf, READ_BLOCK_SIZE);
		data->length += READ_BLOCK_SIZE;
	}
	if (ret == -1)
		return (NULL);
	data->length += ret;
	if ((place = (uint8_t*)malloc(ret + 100)) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	memcpy((void*)(place), (void*)(buf), ret);
	end = append_padding_bits((void*)place, ret, MD5_BLOCK_SIZE);
	end = append_length(end, data->length, MD5_ENDIAN);
	process(e, place, (end - place));
	free(place);
	return (finish(e));
}
