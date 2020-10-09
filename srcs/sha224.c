/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 13:16:58 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224.h"

const uint32_t	*g_sha224_k = g_sha256_k;

const uint32_t	g_sha224_init[8] = {
	0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
};

static t_sha224		*sha224_init(void)
{
	int			i;
	t_sha224	*e;

	if ((e = (t_sha224 *)malloc(sizeof(t_sha224))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	i = -1;
	while (++i < 8)
		e->h[i] = g_sha224_init[i];
	return (e);
}

static void			process_block(t_sha224 *e)
{
	ssize_t			i;
	uint32_t		temp1;
	uint32_t		temp2;

	sha_generate_w32(e->w, e->block);
	i = -1;
	while (++i < 64)
	{
		temp1 = e->hh[7] + (rotate_right(e->hh[4], 6)
		^ rotate_right(e->hh[4], 11) ^ rotate_right(e->hh[4], 25)) + ((e->hh[4]
		& e->hh[5]) ^ (~(e->hh[4]) & e->hh[6])) + g_sha224_k[i] + e->w[i];
		temp2 = (rotate_right(e->hh[0], 2) ^ rotate_right(e->hh[0], 13)
		^ rotate_right(e->hh[0], 22)) + ((e->hh[0] & e->hh[1])
		^ (e->hh[0] & e->hh[2]) ^ (e->hh[1] & e->hh[2]));
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

static void			process(t_sha224 *e, void *input, uint64_t size)
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
		memcpy(&(e->block), (void*)(temp), SHA224_BLOCK_SIZE);
		process_block(e);
		i = -1;
		while (++i < 8)
			e->h[i] += e->hh[i];
		temp += SHA224_BLOCK_SIZE;
	}
}

static uint8_t		*finish(t_sha224 *e)
{
	uint8_t	*hash;
	int		i;

	if ((hash = (uint8_t*)malloc(28)) != NULL)
	{
		i = -1;
		while (++i < 7)
		{
			u32_to_u8(hash, e->h[i], i, SHA224_ENDIAN);
		}
	}
	free(e);
	return (hash);
}

uint8_t		*sha224_calc(t_data *data)
{
	t_sha224	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	e = sha224_init();
	while ((ret = read_data(data, buf, READ_BLOCK_SIZE)) == READ_BLOCK_SIZE)
	{
		process(e, buf, READ_BLOCK_SIZE);
		data->length += READ_BLOCK_SIZE;
	}
	if (ret == -1)
		return (NULL);
	data->length += ret;
	place = (uint8_t*)malloc(ret + 100);
	memcpy((void*)(place), (void*)(buf), ret);
	end = append_padding_bits((void*)place, ret, SHA224_BLOCK_SIZE);
	end = append_length(end, data->length, SHA224_ENDIAN);
	process(e, place, (end - place));
	free(place);
	return (finish(e));
}
