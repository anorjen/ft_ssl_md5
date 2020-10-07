/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 14:31:50 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

const uint32_t	g_k[64] = {

	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t	g_w[64];

static void			*append_padding_bits(void *input, uint64_t size)
{
	uint8_t	*end;

	end = (uint8_t*)(input) + size;
	*end = 0x80;
	++end;
	while ((end - (uint8_t*)(input)) % SHA256_BLOCK_SIZE != (SHA256_BLOCK_SIZE - 8))
	{
		*end = 0x00;
		++end;
	}
	return (end);
}

static void			*append_length(void *end, uint64_t size)
{
	uint64_t	length;

	length = size * 8;
	memcpy((void*)(end), &length, 8);
	if (endian() == L_ENDIAN)
	{
		ft_swap(end, end + 7);
		ft_swap(end + 1, end + 6);
		ft_swap(end + 2, end + 5);
		ft_swap(end + 3, end + 4);
	}
	end += 8;
	return (end);
}

static t_sha256			*sha256_init(void)
{
	t_sha256	*e;

	e = (t_sha256 *)malloc(sizeof(t_sha256));
	// if (endian() == B_ENDIAN)
	// {
	// 	e->h0 = 0x6a09e667UL;
	// 	e->h1 = 0xbb67ae85UL;
	// 	e->h2 = 0x3c6ef372UL;
	// 	e->h3 = 0xa54ff53aUL;
	// 	e->h4 = 0x510e527fUL;
	// 	e->h5 = 0x9b05688cUL;
	// 	e->h6 = 0x1f83d9abUL;
	// 	e->h7 = 0x5be0cd19UL;
	// }
	// else
	// {
	// 	e->h0 = l_to_b_endian(0x6a09e667UL);
	// 	e->h1 = l_to_b_endian(0xbb67ae85UL);
	// 	e->h2 = l_to_b_endian(0x3c6ef372UL);
	// 	e->h3 = l_to_b_endian(0xa54ff53aUL);
	// 	e->h4 = l_to_b_endian(0x510e527fUL);
	// 	e->h5 = l_to_b_endian(0x9b05688cUL);
	// 	e->h6 = l_to_b_endian(0x1f83d9abUL);
	// 	e->h7 = l_to_b_endian(0x5be0cd19UL);
	// }
	e->h0 = 0x6a09e667UL;
		e->h1 = 0xbb67ae85UL;
		e->h2 = 0x3c6ef372UL;
		e->h3 = 0xa54ff53aUL;
		e->h4 = 0x510e527fUL;
		e->h5 = 0x9b05688cUL;
		e->h6 = 0x1f83d9abUL;
		e->h7 = 0x5be0cd19UL;
	return (e);
}

static void			generate_w(t_sha256 *e)
{
	ssize_t			i;
	uint32_t		s0;
	uint32_t		s1;

	// memcpy(&(g_w), (void*)(e->block), SHA256_BLOCK_SIZE);
	i = -1;
	while (++i < 16)
	{
		g_w[i] = l_to_b_endian(e->block[i]);
	}
	i = 15;
	while (++i < 64)
	{
		s0 = rotate_right(g_w[i-15], 7) ^ rotate_right(g_w[i-15], 18) ^ (g_w[i-15] >> 3);
		s1 = rotate_right(g_w[i-2], 17) ^ rotate_right(g_w[i-2], 19) ^ (g_w[i-2] >> 10);
		g_w[i] = g_w[i-16] + s0 + g_w[i-7] + s1;
	}
}

static void			process_block(t_sha256 *e)
{
	ssize_t			i;
	uint32_t		temp1;
	uint32_t		temp2;

	generate_w(e);
	i = -1;
	while (++i < 64)
	{
		temp1 = e->h + (rotate_right(e->e, 6) ^ rotate_right(e->e, 11)
									^ rotate_right(e->e, 25)) + ((e->e & e->f)
									^ (~(e->e) & e->g)) + g_k[i] + g_w[i];
		temp2 = (rotate_right(e->a, 2) ^ rotate_right(e->a, 13)
							^ rotate_right(e->a, 22))
							+ ((e->a & e->b) ^ (e->a & e->c) ^ (e->b & e->c));
		e->h = e->g;
		e->g = e->f;
		e->f = e->e;
		e->e = e->d + temp1;
		e->d = e->c;
		e->c = e->b;
		e->b = e->a;
		e->a = temp1 + temp2;
	}
}

static void			process(t_sha256 *e, void *input, uint64_t size)
{
	uint8_t	*temp;
	uint8_t	*end;

	temp = (uint8_t*)(input);
	end = temp + size;
	while (temp != end)
	{
		e->a = e->h0;
		e->b = e->h1;
		e->c = e->h2;
		e->d = e->h3;
		e->e = e->h4;
		e->f = e->h5;
		e->g = e->h6;
		e->h = e->h7;
		memcpy(&(e->block), (void*)(temp), SHA256_BLOCK_SIZE);
		process_block(e);
		e->h0 += e->a;
		e->h1 += e->b;
		e->h2 += e->c;
		e->h3 += e->d;
		e->h4 += e->e;
		e->h5 += e->f;
		e->h6 += e->g;
		e->h7 += e->h;
		temp += 64;
	}
}

static uint8_t			*finish(t_sha256 *e)
{
	uint8_t	*hash;

	hash = (uint8_t*)malloc(32);
	hash[0] = (uint8_t)((e->h0) >> 24);
	hash[1] = (uint8_t)((e->h0) >> 16);
	hash[2] = (uint8_t)((e->h0) >> 8);
	hash[3] = (uint8_t)((e->h0) >> 0);

	hash[4] = (uint8_t)((e->h1) >> 24);
	hash[5] = (uint8_t)((e->h1) >> 16);
	hash[6] = (uint8_t)((e->h1) >> 8);
	hash[7] = (uint8_t)((e->h1) >> 0);

	hash[8] = (uint8_t)((e->h2) >> 24);
	hash[9] = (uint8_t)((e->h2) >> 16);
	hash[10] = (uint8_t)((e->h2) >> 8);
	hash[11] = (uint8_t)((e->h2) >> 0);

	hash[12] = (uint8_t)((e->h3) >> 24);
	hash[13] = (uint8_t)((e->h3) >> 16);
	hash[14] = (uint8_t)((e->h3) >> 8);
	hash[15] = (uint8_t)((e->h3) >> 0);

	hash[16] = (uint8_t)((e->h4) >> 24);
	hash[17] = (uint8_t)((e->h4) >> 16);
	hash[18] = (uint8_t)((e->h4) >> 8);
	hash[19] = (uint8_t)((e->h4) >> 0);

	hash[20] = (uint8_t)((e->h5) >> 24);
	hash[21] = (uint8_t)((e->h5) >> 16);
	hash[22] = (uint8_t)((e->h5) >> 8);
	hash[23] = (uint8_t)((e->h5) >> 0);

	hash[24] = (uint8_t)((e->h6) >> 24);
	hash[25] = (uint8_t)((e->h6) >> 16);
	hash[26] = (uint8_t)((e->h6) >> 8);
	hash[27] = (uint8_t)((e->h6) >> 0);

	hash[28] = (uint8_t)((e->h7) >> 24);
	hash[29] = (uint8_t)((e->h7) >> 16);
	hash[30] = (uint8_t)((e->h7) >> 8);
	hash[31] = (uint8_t)((e->h7) >> 0);

	// memcpy(&hash[0], &(e->h0), 4);
	// memcpy(&hash[4], &(e->h1), 4);
	// memcpy(&hash[8], &(e->h2), 4);
	// memcpy(&hash[12], &(e->h3), 4);
	// memcpy(&hash[16], &(e->h4), 4);
	// memcpy(&hash[20], &(e->h5), 4);
	// memcpy(&hash[24], &(e->h6), 4);
	// memcpy(&hash[28], &(e->h7), 4);
	free(e);
	return (hash);
}

static char			*sha256_to_string(uint8_t *hash)
{
	char	*hex_char;
	uint8_t	*outbuf;
	char	*ret;
	size_t	j;
	int		i;

	hex_char = "0123456789abcdef";
	j = 0;
	ret = (char *)malloc(sizeof(char) * 64);
	outbuf = (uint8_t *)malloc(32);
	i = -1;
	while (++i < 32)
	{
		ret[j++] = hex_char[(hash[i] >> 4) & 0x0F];
		ret[j++] = hex_char[hash[i] & 0x0F];
	}
	ret[j] = '\0';
	return (ret);
}

static uint8_t			*sha256_calc(t_data *data)
{
	t_sha256		*e;
	ssize_t		ret;
	uint8_t		buf[64];
	uint8_t		*place;
	uint8_t		*end;

	e = sha256_init();
	while ((ret = read_data(data, buf, SHA256_BLOCK_SIZE)) == SHA256_BLOCK_SIZE)
	{
		process(e, buf, SHA256_BLOCK_SIZE);
		data->length += SHA256_BLOCK_SIZE;
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

int				sha256(t_data *data)
{
	uint8_t	*hash;

	hash = sha256_calc(data);
	if (hash == NULL)
		return (1);
	data->hash = sha256_to_string(hash);
	free(hash);
	return (0);
}
