/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/07/14 20:37:55 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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

void		init_buffer()
{
	uint8_t _a[4] = { 0x01, 0x23, 0x45, 0x67 };
	uint8_t _b[4] = { 0x89, 0xab, 0xcd, 0xef };
	uint8_t _c[4] = { 0xfe, 0xdc, 0xba, 0x98 };
	uint8_t _d[4] = { 0x76, 0x54, 0x32, 0x10 };

	a = *(uint32_t*)(&_a);
	b = *(uint32_t*)(&_b);
	c = *(uint32_t*)(&_c);
	d = *(uint32_t*)(&_d);
}

uint32_t	rotate_left(uint32_t x, uint32_t s)
{
	return ((x << s) | (x >> (32 - s)));
}

void		process_block(uint8_t* adress)
{
    uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;
	ssize_t	i;

	memcpy(&block, (void*)(adress), 64);
	aa = a;
	bb = b;
	cc = c;
	dd = d;

	i = 0;
	while (i < 64)
	{
		uint32_t	F;
		uint8_t		g;

		F = 0;
		g = 0;
		if (i >= 0 && i < 16)
		{
			F = (bb & cc) | (~bb & dd);
			g = i;
		}
		else if (i >= 16 && i < 32)
		{
			F = (dd & bb) | (~dd & cc);
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i < 48)
		{
			F = bb ^ cc ^ dd;
			g = (3 * i + 5) % 16;
		}
		else if (i >= 48 && i < 64)
		{
			F = cc ^ (bb | ~dd);
			g = (7 * i) % 16;
		}
		F = F + aa + t[i] + block[g];
		aa = dd;
		dd = cc;
		cc = bb;
		bb = bb + rotate_left(F, s[i]);
		++i;
	}

	a += aa;
	b += bb;
	c += cc;
	d += dd;
}

void		process(void)
{
	uint8_t*	temp;

	temp = (uint8_t*)(input);
	while (temp != end)
	{
		process_block(temp);
		temp += 64;
	}
}

uint8_t		*finish()
{
    uint8_t	*hash;

	hash = (uint8_t*)malloc(16);
    memcpy(&hash[0], &a, 4);
    memcpy(&hash[4], &b, 4);
    memcpy(&hash[8], &c, 4);
    memcpy(&hash[12], &d, 4);
    return (hash);
}

uint8_t		*MD5(void* original_input, uint64_t size)
{
	uint8_t	*place;

	place = (uint8_t*)malloc(size + 100);
	memcpy((void*)(place), original_input, size);
	input = (void*)(place);
	saved_length = size;
	append_padding_bits();
	append_length();
	init_buffer();
	process();
	free(place);
	return (finish());
}

char		*md5hash_to_string(uint8_t *hash) {
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

int			main()
{
	char	*s;
	char	*hash;

	while (1)
	{
		write(1, "Input: ", 7);
		get_next_line(0, &s);
		write(1, "Hash: ", 7);
		hash = md5hash_to_string(MD5(&s[0], ft_strlen(s)));
		write(1, hash, ft_strlen(hash));
		write(1, "\n", 1);
	}
	return (0);
}
