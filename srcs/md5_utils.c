/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:29:03 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:00:39 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

t_md5_utils	func_f(uint32_t x, uint32_t y, uint32_t z, int i)
{
	t_md5_utils	util;

	util.f = ((x & y) | (~x & z));
	util.g = i;
	return (util);
}

t_md5_utils	func_g(uint32_t x, uint32_t y, uint32_t z, int i)
{
	t_md5_utils	util;

	util.f = ((x & z) | (~z & y));
	util.g = (5 * i + 1) % 16;
	return (util);
}

t_md5_utils	func_h(uint32_t x, uint32_t y, uint32_t z, int i)
{
	t_md5_utils	util;

	util.f = (x ^ y ^ z);
	util.g = (3 * i + 5) % 16;
	return (util);
}

t_md5_utils	func_i(uint32_t x, uint32_t y, uint32_t z, int i)
{
	t_md5_utils	util;

	util.f = (y ^ (~z | x));
	util.g = (7 * i) % 16;
	return (util);
}

void	md5_u32_to_u8(uint8_t *hash, uint32_t h, int i)
{
	if (endian() == L_ENDIAN)
	{
		hash[i * 4 + 0] = (uint8_t)(h >> 0);
		hash[i * 4 + 1] = (uint8_t)(h >> 8);
		hash[i * 4 + 2] = (uint8_t)(h >> 16);
		hash[i * 4 + 3] = (uint8_t)(h >> 24);
	}
	else
	{
		hash[i * 4 + 0] = (uint8_t)(h >> 24);
		hash[i * 4 + 1] = (uint8_t)(h >> 16);
		hash[i * 4 + 2] = (uint8_t)(h >> 8);
		hash[i * 4 + 3] = (uint8_t)(h >> 0);
	}
}
