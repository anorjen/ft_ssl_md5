/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:51:51 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/29 18:01:54 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

const uint32_t	g_sha224_init[8] = {
	0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
};

uint8_t				*sha224_calc(t_data *data)
{
	t_sha256	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	e = sha256_init(g_sha224_init);
	while ((ret = read_data(data, buf, READ_BLOCK_SIZE)) == READ_BLOCK_SIZE)
	{
		sha256_process(e, buf, READ_BLOCK_SIZE);
		data->length += READ_BLOCK_SIZE;
	}
	if (ret == -1)
		return (NULL);
	data->length += ret;
	if ((place = (uint8_t*)malloc(ret + 100)) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	ft_memcpy((void*)(place), (void*)(buf), ret);
	end = append_padding_bits((void*)place, ret, SHA224_BLOCK_SIZE);
	end = append_length(end, data->length, B_ENDIAN);
	sha256_process(e, place, (end - place));
	free(place);
	return (sha256_finish(e, SHA224_OUTPUT_BLOCK_AMOUNT));
}
