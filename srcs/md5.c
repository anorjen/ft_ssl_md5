/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/09/30 19:18:13 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int			endian(void)
{
	uint32_t	i = 1;
	uint8_t	*p = (uint8_t*)(&i);

	if (*p == 1)
		return (L_ENDIAN);
	else
		return (B_ENDIAN);
}

void		append_padding_bits(void)
{
	end = (uint8_t*)(input) + saved_length;
	*end = 0x80;
   	 ++end;

	while ((end - (uint8_t*)(input)) % 64 != 56)
	{
		*end = 0x00, ++end;
	}
}

void		ft_swap(uint8_t *one, uint8_t *two)
{
	uint8_t	buf;

	buf = *one;
	*one = *two;
	*two = buf;
}

void		append_length(void)
{
	uint64_t length = saved_length * 8;
	memcpy((void*)(end), &length, 8);

	if (endian() == B_ENDIAN) {
		ft_swap(end, end + 7);
		ft_swap(end + 1, end + 6);
		ft_swap(end + 2, end + 5);
		ft_swap(end + 3, end + 4);
	}
	end += 8;
}

t_md5		*md5_init(void)
{
	t_md5	*e;

	uint8_t _a[4] = { 0x01, 0x23, 0x45, 0x67 };
	uint8_t _b[4] = { 0x89, 0xab, 0xcd, 0xef };
	uint8_t _c[4] = { 0xfe, 0xdc, 0xba, 0x98 };
	uint8_t _d[4] = { 0x76, 0x54, 0x32, 0x10 };

	e = (t_md5 *)malloc(sizeof(t_md5));
	e->a = *(uint32_t*)(&_a);
	e->b = *(uint32_t*)(&_b);
	e->c = *(uint32_t*)(&_c);
	e->d = *(uint32_t*)(&_d);
	return (e);
}

uint32_t	rotate_left(uint32_t x, uint32_t s)
{
	return ((x << s) | (x >> (32 - s)));
}

void		process_block(t_md5 *e)
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
		util.f = util.f + e->aa + t[i] + g_block[util.g];
		e->aa = e->dd;
		e->dd = e->cc;
		e->cc = e->bb;
		e->bb += rotate_left(util.f, s[i]);
		++i;
	}
}

void		process(t_md5 *e)
{
	uint8_t*	temp;

	temp = (uint8_t*)(input);
	while (temp != end)
	{
		memcpy(&g_block, (void*)(temp), 64);
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

uint8_t		*finish(t_md5 *e)
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

uint8_t		*MD5(void* original_input, uint64_t size)
{
	t_md5	*e;
	uint8_t	*place;

	place = (uint8_t*)malloc(size + 100);
	memcpy((void*)(place), original_input, size);
	input = (void*)(place);
	saved_length = size;
	append_padding_bits();
	append_length();
	e = md5_init();
	process(e);
	free(place);
	return (finish(e));
}

char		*md5_to_string(uint8_t *hash) {
	char	*hex_char = "0123456789abcdef";
	char	*ret;
	size_t	j;

	j = 0;
	ret = (char *)malloc(sizeof(char) * 32);
	for (int i = 0; i < 16; ++i) {
		ret[j++] = hex_char[hash[i] >> 4];
		ret[j++] = hex_char[hash[i] & 0x0F];
	}
	ret[j] = '\0';
	return (ret);
}

t_md5		*md5_calc()
{
	
}

int			ft_md5(t_data *data)
{
	uint8_t	*hash;

	hash = md5_calc(data);
	data->hash = md5_to_string(hash);
	return (0);
}
