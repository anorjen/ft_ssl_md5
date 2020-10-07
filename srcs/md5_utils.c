/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:29:03 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:49:50 by anorjen          ###   ########.fr       */
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

t_md5		*md5_init(void)
{
	t_md5	*e;

	e = (t_md5 *)malloc(sizeof(t_md5));
	if (endian() == L_ENDIAN)
	{
		e->h[0] = 0x67452301;
		e->h[1] = 0xefcdab89;
		e->h[2] = 0x98badcfe;
		e->h[3] = 0x10325476;
	}
	else
	{
		e->h[0] = 0x01234567;
		e->h[1] = 0x89abcdef;
		e->h[2] = 0xfedcba98;
		e->h[3] = 0x76543210;
	}
	return (e);
}
