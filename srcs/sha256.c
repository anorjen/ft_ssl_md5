/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/24 13:28:07 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

const uint32_t	g_sha256_k[64] = {
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

const uint32_t	g_sha256_init[8] = {
	0x6a09e667UL, 0xbb67ae85UL, 0x3c6ef372UL, 0xa54ff53aUL,
	0x510e527fUL, 0x9b05688cUL, 0x1f83d9abUL, 0x5be0cd19UL
};

const uint32_t	g_sha224_init[8] = {
	0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
};

static void			sha256_process_block(t_sha256 *e)
{
	ssize_t			i;
	uint32_t		temp1;
	uint32_t		temp2;

	sha256_generate_w(e->w, e->block);
	i = -1;
	while (++i < 64)
	{
		temp1 = e->hh[7] + SHA256_S1(e->hh[4])
		+ SHA256_CH(e->hh[4], e->hh[5], e->hh[6]) + g_sha256_k[i] + e->w[i];
		temp2 = SHA256_S0(e->hh[0]) + SHA256_MAJ(e->hh[0], e->hh[1], e->hh[2]);
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

static void			sha256_process(t_sha256 *e, void *input, uint64_t size)
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
		ft_memcpy(&(e->block), (void*)(temp), SHA256_BLOCK_SIZE);
		sha256_process_block(e);
		i = -1;
		while (++i < 8)
			e->h[i] += e->hh[i];
		temp += SHA256_BLOCK_SIZE;
	}
}

static uint8_t		*sha256_finish(t_sha256 *e, size_t block_amount)
{
	uint8_t	*hash;
	size_t	i;

	if ((hash = (uint8_t*)malloc(block_amount * sizeof(uint32_t))) != NULL)
	{
		i = -1;
		while (++i < block_amount)
		{
			u32_to_u8(hash, e->h[i], i, SHA256_ENDIAN);
		}
	}
	free(e);
	return (hash);
}

static uint8_t		*align_block(uint8_t *block, ssize_t block_size,
										ssize_t full_size, ssize_t *align_size)
{
	uint8_t		*place;
	uint8_t		*end;

	if ((place = (uint8_t*)malloc(block_size + 100)) == NULL)
		return (NULL);
	ft_memcpy((void*)(place), (void*)(block), block_size);
	end = append_padding_bits((void*)place, block_size, SHA256_BLOCK_SIZE);
	end = append_length(end, full_size, SHA256_ENDIAN);
	*align_size = end - place;
	return (place);
}

uint8_t				*sha256_calc(t_data *data, const t_hash *hash_handler)
{
	t_sha256	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	ssize_t		align_size;

	e = sha256_init(hash_handler->init_h);
	while ((ret = read_data(data, buf, READ_BLOCK_SIZE)) == READ_BLOCK_SIZE)
	{
		sha256_process(e, buf, READ_BLOCK_SIZE);
		data->length += READ_BLOCK_SIZE;
	}
	if (ret == -1)
	{
		free(e);
		return (NULL);
	}
	data->length += ret;
	if ((place = align_block(buf, ret, data->length, &align_size)) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	sha256_process(e, place, align_size);
	free(place);
	return (sha256_finish(e, hash_handler->block_amount));
}
