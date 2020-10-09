/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_common.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:00:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 19:06:19 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha_common.h"

void	sha_generate_w32(uint32_t w[], uint32_t block[])
{
	size_t			i;
	uint32_t		s0;
	uint32_t		s1;

	i = -1;
	while (++i < 16)
	{
		if (endian() == SHA_ENDIAN)
			w[i] = block[i];
		else
			w[i] = lb_converter(block[i]);
	}
	i = 15;
	while (++i < 64)
	{
		s0 = rotate_right(w[i - 15], 7) ^ rotate_right(w[i - 15], 18)
														^ (w[i - 15] >> 3);
		s1 = rotate_right(w[i - 2], 17) ^ rotate_right(w[i - 2], 19)
														^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
}

// void	sha_generate_w64(uint64_t w[], uint64_t block[])
// {
// 	size_t		i;
// 	// uint64_t	s0;
// 	// uint64_t	s1;


// // Delta0(x) = ROTR(x, 1) XOR ROTR(x, 8) XOR SHR(x, 7)
// // Delta1(x) = ROTR(x, 19) XOR ROTR(x, 61) XOR SHR(x, 6)
// // Wt = Wt-16 + Delta0(Wt-15 ) + Wi-7 + Delta1(Wt-2 ), для t = 16..79

// 	i = -1;
// 	while (++i < 16)
// 	{
// 		if (endian() == SHA_ENDIAN)
// 			w[i] = block[i];
// 		else
// 			w[i] = lb_converter64(block[i]);
// 	}
// 	i = 15;
// 	while (++i < 80)
// 	{
// 		// s0 = rotate_right64(w[i - 15], 1) ^ rotate_right64(w[i - 15], 8)
// 		// 												^ (w[i - 15] >> 7);
// 		// s1 = rotate_right64(w[i - 2], 19) ^ rotate_right64(w[i - 2], 61)
// 		// 												^ (w[i - 2] >> 6);
// 		// w[i] = w[i - 16] + s0 + w[i - 7] + s1;
// 		w[i] = w[i - 16] + D0(w[i - 15]) + w[i - 7] + D1(w[i - 2]);
// 	}
// }
