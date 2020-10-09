/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:00:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 20:53:22 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_generate_w(uint32_t w[], uint32_t block[])
{
	size_t	i;

	i = -1;
	while (++i < 16)
		w[i] = (endian() == SHA256_ENDIAN ? block[i] : LB_CONV32(block[i]));
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + SHA256_D0(w[i - 15]) + w[i - 7]
												+ SHA256_D1(w[i - 2]);
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
