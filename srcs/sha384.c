/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:54:19 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/29 18:02:08 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

const uint64_t	g_sha384_init[8] = {
	0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17,
	0x152fecd8f70e5939, 0x67332667ffc00b31, 0x8eb44a8768581511,
	0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4
};

uint8_t			*sha384_calc(t_data *data)
{
	t_sha512	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	e = sha512_init(g_sha384_init);
	while ((ret = read_data(data, buf, READ_BLOCK_SIZE)) == READ_BLOCK_SIZE)
	{
		sha512_process(e, buf, READ_BLOCK_SIZE);
		data->length += READ_BLOCK_SIZE;
	}
	if (ret == -1)
		return (NULL);
	data->length += ret;
	if ((place = (uint8_t*)malloc(ret + 150)) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	ft_memcpy((void*)(place), (void*)(buf), ret);
	end = sha512_append_padding_bits((void*)place, ret, SHA384_BLOCK_SIZE);
	end = sha512_append_length(end, data->length, B_ENDIAN);
	sha512_process(e, place, (end - place));
	free(place);
	return (sha512_finish(e, SHA384_OUTPUT_BLOCK_AMOUNT));
}
