/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:32:48 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/30 18:33:49 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

uint64_t	make_pc1(uint64_t k)
{
	uint64_t	result;
	uint64_t	tmp;
	int				i;

	result = 0;
	i = 0;
	while (i < 56)
	{
		tmp = (k >> (64 - g_pc1_table[i])) & 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	result <<= 8;
	return (result);
}

uint64_t	circular_shift_left(uint64_t key, int bits)
{
	uint64_t	result;
	uint64_t	tmp;
	uint64_t	fullbits;

	tmp = bits;
	fullbits = 0;
	while (tmp--)
		fullbits = (fullbits << 1) + 1;
	tmp = (key >> (bits - 1)) & 1;
	result = ((key << 1) + tmp) & fullbits;
	return (result);
}

void			make_half_keys(uint64_t half_keys[16], uint64_t starter)
{
	unsigned char	shift;
	uint64_t	new_half;
	int				i;

	i = 0;
	new_half = 0;
	while (i < 16)
	{
		shift = g_left_shifts[i];
		while (shift--)
		{
			new_half = circular_shift_left(starter, 28);
			starter = new_half;
		}
		half_keys[i] = new_half;
		i++;
	}
}

uint64_t	make_pc2(uint64_t c_half, uint64_t d_half)
{
	uint64_t	before;
	uint64_t	after;
	int		i;

	before = (c_half << 28) + d_half;
	i = 0;
	after = 0;
	while (i < 48)
	{
		after <<= 1;
		after += ((before >> (56 - g_pc2_table[i])) & 1);
		i++;
	}
	return (after);
}

void			make_keys(uint64_t keys[16], uint64_t master_key, int rev)
{
	uint64_t	kp;
	uint64_t	c_half_keys[16];
	uint64_t	d_half_keys[16];
	int				i;

	kp = make_pc1(master_key);
	make_half_keys(c_half_keys, (kp >> 36) & 0xfffffff);
	make_half_keys(d_half_keys, (kp >> 8) & 0xfffffff);
	i = 0;
	while (i < 16)
	{
		kp = i;
		if (rev == 1)
			kp = 15 - i;
		keys[kp] = make_pc2(c_half_keys[i], d_half_keys[i]);
		i++;
	}
}
