/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:22:32 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/29 18:02:19 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

const uint64_t	g_sha512_256_init[8] = {
	0x22312194FC2BF72C, 0x9F555FA3C84C64C2, 0x2393B86B6F53B151,
	0x963877195940EABD, 0x96283EE2A88EFFE3, 0xBE5E1E2553863992,
	0x2B0199FC2C85B8AA, 0x0EB72DDC81C52CA2
};

uint8_t			*sha512_256_calc(t_data *data)
{
	t_sha512	*e;
	ssize_t		ret;
	uint8_t		buf[READ_BLOCK_SIZE];
	uint8_t		*place;
	uint8_t		*end;

	e = sha512_init(g_sha512_256_init);
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
	end = sha512_append_padding_bits((void*)place, ret, SHA512_256_BLOCK_SIZE);
	end = sha512_append_length(end, data->length, SHA512_ENDIAN);
	sha512_process(e, place, (end - place));
	free(place);
	return (sha512_finish(e, SHA512_256_OUTPUT_BLOCK_AMOUNT));
}
