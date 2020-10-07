/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 14:27:01 by anorjen          ###   ########.fr       */
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

static void			*append_padding_bits(void *input, uint64_t size)
{
	uint8_t	*end;

	end = (uint8_t*)(input) + size;
	*end = 0x80;
	++end;
	while ((end - (uint8_t*)(input)) % MD5_BLOCK_SIZE != (MD5_BLOCK_SIZE - 8))
	{
		*end = 0x00;
		++end;
	}
	return (end);
}

static void			*append_length(void *end, uint64_t size)
{
	uint64_t length;

	length = size * 8;
	memcpy((void*)(end), &length, 8);
	if (endian() == B_ENDIAN)
	{
		ft_swap(end, end + 7);
		ft_swap(end + 1, end + 6);
		ft_swap(end + 2, end + 5);
		ft_swap(end + 3, end + 4);
	}
	end += 8;
	return (end);
}

static t_md5			*md5_init(void)
{
	t_md5	*e;

	e = (t_md5 *)malloc(sizeof(t_md5));
	if (endian() == L_ENDIAN)
	{
		e->a = 0x67452301;
		e->b = 0xefcdab89;
		e->c = 0x98badcfe;
		e->d = 0x10325476;
	}
	else
	{
		e->a = 0x01234567;
		e->b = 0x89abcdef;
		e->c = 0xfedcba98;
		e->d = 0x76543210;
	}
	return (e);
}

static void			process_block(t_md5 *e)
{
	ssize_t		i;
	t_md5_utils	util;

	i = 0;
	while (i < 64)
	{
		if (i >= 0 && i < 16)
			util = func_f(e->bb, e->cc, e->dd, i);
		else if (i >= 16 && i < 32)
			util = func_g(e->bb, e->cc, e->dd, i);
		else if (i >= 32 && i < 48)
			util = func_h(e->bb, e->cc, e->dd, i);
		else if (i >= 48 && i < 64)
			util = func_i(e->bb, e->cc, e->dd, i);
		util.f = util.f + e->aa + g_t[i] + e->block[util.g];
		e->aa = e->dd;
		e->dd = e->cc;
		e->cc = e->bb;
		e->bb += rotate_left(util.f, g_s[i]);
		++i;
	}
}

static void			process(t_md5 *e, void *input, uint64_t size)
{
	uint8_t	*temp;
	uint8_t	*end;

	temp = (uint8_t*)(input);
	end = temp + size;
	while (temp != end)
	{
		memcpy(&(e->block), (void*)(temp), MD5_BLOCK_SIZE);
		e->aa = e->a;
		e->bb = e->b;
		e->cc = e->c;
		e->dd = e->d;
		process_block(e);
		e->a += e->aa;
		e->b += e->bb;
		e->c += e->cc;
		e->d += e->dd;
		temp += 64;
	}
}

static uint8_t			*finish(t_md5 *e)
{
	uint8_t	*hash;

	hash = (uint8_t*)malloc(16);
	memcpy(&hash[0], &(e->a), 4);
	memcpy(&hash[4], &(e->b), 4);
	memcpy(&hash[8], &(e->c), 4);
	memcpy(&hash[12], &(e->d), 4);
	free(e);
	return (hash);
}

static char			*md5_to_string(uint8_t *hash)
{
	char	*hex_char;
	char	*ret;
	size_t	j;
	int		i;

	hex_char = "0123456789abcdef";
	j = 0;
	ret = (char *)malloc(sizeof(char) * 32);
	i = -1;
	while (++i < 16)
	{
		ret[j++] = hex_char[hash[i] >> 4];
		ret[j++] = hex_char[hash[i] & 0x0F];
	}
	ret[j] = '\0';
	return (ret);
}

static uint8_t			*md5_calc(t_data *data)
{
	t_md5		*e;
	ssize_t		ret;
	uint8_t		buf[64];
	uint8_t		*place;
	uint8_t		*end;

	e = md5_init();
	while ((ret = read_data(data, buf, MD5_BLOCK_SIZE)) == MD5_BLOCK_SIZE)
	{
		process(e, buf, MD5_BLOCK_SIZE);
		data->length += MD5_BLOCK_SIZE;
	}
	if (ret == -1)
		return (NULL);
	data->length += ret;
	place = (uint8_t*)malloc(ret + 100);
	memcpy((void*)(place), (void*)(buf), ret);
	end = append_padding_bits((void*)place, ret);
	end = append_length(end, data->length);
	process(e, place, (end - place));
	free(place);
	return (finish(e));
}

int				md5(t_data *data)
{
	uint8_t	*hash;

	hash = md5_calc(data);
	if (hash == NULL)
		return (1);
	data->hash = md5_to_string(hash);
	free(hash);
	return (0);
}
