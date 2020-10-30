/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:56:59 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/29 18:02:13 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

const uint64_t	g_sha512_224_init[8] = {
	0x8C3D37C819544DA2, 0x73E1996689DCD4D6, 0x1DFAB7AE32FF9C82,
	0x679DD514582F9FCF, 0x0F6D2B697BD44DA8, 0x77E36F7304C48942,
	0x3F9D85A86A1D36C8, 0x1112E6AD91D692A1
};

uint8_t			*sha512_224_calc(t_data *data)
{
	t_sha512	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	e = sha512_init(g_sha512_224_init);
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
	end = sha512_append_padding_bits((void*)place, ret, SHA512_224_BLOCK_SIZE);
	end = sha512_append_length(end, data->length, SHA512_ENDIAN);
	sha512_process(e, place, (end - place));
	free(place);
	return (sha512_finish(e, SHA512_224_OUTPUT_BLOCK_AMOUNT));
}
