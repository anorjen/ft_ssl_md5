/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:29:03 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 12:45:14 by anorjen          ###   ########.fr       */
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
