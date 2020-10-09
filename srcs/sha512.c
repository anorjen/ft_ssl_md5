/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 19:47:52 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

const uint64_t	g_sha512_k[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

const uint64_t	g_sha512_init[8] = {
	0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b,
	0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f,
	0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
};

static t_sha512	*sha512_init(void)
{
	int			i;
	t_sha512	*e;

	if ((e = (t_sha512 *)malloc(sizeof(t_sha512))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	i = -1;
	while (++i < 8)
		e->h[i] = g_sha512_init[i];
	return (e);
}

static void		*sha512_append_padding_bits(void *input, uint64_t size, int block_size)
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

static void		*sha512_append_length(void *end, uint64_t size, int endian_type)
{
	__uint128_t	length;

	length = (size * 8);
	memcpy((void*)(end), &length, 16);
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

static void		process_block(t_sha512 *e)
{
	ssize_t			i;
	uint64_t		temp1;
	uint64_t		temp2;

	i = -1;
	while (++i < 16)
		e->w[i] = (endian() == SHA_ENDIAN ? e->block[i] : LB_CONV(e->block[i]));
	i = 15;
	while (++i < 80)
		e->w[i] = e->w[i - 16] + D0(e->w[i - 15]) + e->w[i - 7] + D1(e->w[i - 2]);
	i = -1;
	while (++i < 80)
	{
		temp1 = e->hh[7] + S1(e->hh[4]) + CH(e->hh[4], e->hh[5], e->hh[6])
								+ g_sha512_k[i] + e->w[i];
		temp2 = S0(e->hh[0]) + MAJ(e->hh[0], e->hh[1], e->hh[2]);
		e->hh[7] = e->hh[6];
		e->hh[6] = e->hh[5];
		e->hh[5] = e->hh[4];
		e->hh[4] = e->hh[3] + temp1;
		e->hh[3] = e->hh[2];
		e->hh[2] = e->hh[1];
		e->hh[1] = e->hh[0];
		e->hh[0] = temp1 + temp2;
	}
}

static void		process(t_sha512 *e, void *input, uint64_t size)
{
	uint8_t	*temp;
	uint8_t	*end;
	int		i;

	temp = (uint8_t*)(input);
	end = temp + size;
	while (temp != end)
	{
		i = -1;
		while (++i < 8)
			e->hh[i] = e->h[i];
		memcpy(&(e->block), (void*)(temp), SHA512_BLOCK_SIZE);
		process_block(e);
		i = -1;
		while (++i < 8)
			e->h[i] += e->hh[i];
		temp += SHA512_BLOCK_SIZE;
	}
}

static uint8_t	*finish(t_sha512 *e)
{
	uint8_t	*hash;
	int		i;

	if ((hash = (uint8_t*)malloc(64)) != NULL)
	{
		i = -1;
		while (++i < 8)
		{
			u64_to_u8(hash, e->h[i], i, SHA512_ENDIAN);
		}
	}
	free(e);
	return (hash);
}

uint8_t			*sha512_calc(t_data *data)
{
	t_sha512	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	e = sha512_init();
	while ((ret = read_data(data, buf, READ_BLOCK_SIZE)) == READ_BLOCK_SIZE)
	{
		process(e, buf, READ_BLOCK_SIZE);
		data->length += READ_BLOCK_SIZE;
	}
	if (ret == -1)
		return (NULL);
	data->length += ret;
	place = (uint8_t*)malloc(ret + 150);
	memcpy((void*)(place), (void*)(buf), ret);
	end = sha512_append_padding_bits((void*)place, ret, SHA512_BLOCK_SIZE);
	end = sha512_append_length(end, data->length, SHA512_ENDIAN);
	process(e, place, (end - place));
	free(place);
	return (finish(e));
}
