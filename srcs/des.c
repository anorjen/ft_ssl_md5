/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:28:48 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/30 16:48:05 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint64_t	make_ip1(uint64_t m)
{
	uint64_t	result;
	int			i;

	i = 0;
	result = 0;
	while (i < 64)
	{
		result <<= 1;
		result += (m >> (64 - g_ip1_table[i])) & 1;
		i++;
	}
	return (result);
}

uint64_t	make_ebit(uint64_t r0)
{
	uint64_t	result;
	uint64_t	tmp;
	int			i;

	i = 0;
	result = 0;
	while (i < 48)
	{
		tmp = (r0 >> (32 - g_ebit_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}

uint64_t	get_s_boxes_value(uint64_t xor0)
{
	int			i;
	int			row;
	int			col;
	uint64_t	tmp;
	uint64_t	result;

	i = 0;
	result = 0;
	while (i < 8)
	{
		tmp = (xor0 >> (42 - (i * 6))) & 0x3f;
		row = ((tmp >> 5) << 1) + (tmp & 1);
		col = (tmp >> 1) & 0xf;
		tmp = g_s_boxes[i][row * 16 + col];
		result <<= 4;
		result += tmp;
		i++;
	}
	return (result);
}

uint64_t	make_pperm(uint64_t sb0)
{
	int			i;
	uint64_t	tmp;
	uint64_t	result;

	i = 0;
	result = 0;
	while (i < 32)
	{
		tmp = (sb0 >> (32 - g_pperm_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}

uint64_t	make_ip2(uint64_t rxlx)
{
	int				i;
	uint64_t	tmp;
	uint64_t	result;

	i = 0;
	result = 0;
	while (i < 64)
	{
		tmp = (rxlx >> (64 - g_ip2_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}
