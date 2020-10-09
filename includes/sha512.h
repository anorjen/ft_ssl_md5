/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 19:45:38 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# define SHA512_ENDIAN B_ENDIAN
# define SHA512_BLOCK_SIZE 128
# define SHA512_OUTPUT_SIZE 128

# define ROTR(x, s) (((x) >> (s)) | ((x) << (64 - (s))))
# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define S0(x) (ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
# define S1(x) (ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
# define D0(x) (ROTR(x, 1) ^ ROTR(x, 8) ^ ((x) >> 7))
# define D1(x) (ROTR(x, 19) ^ ROTR(x, 61) ^ ((x) >> 6))

# define LB_CONV(a) (((a) << 56) & 0xff00000000000000) | (((a) << 40) & 0x00ff000000000000) \
				| (((a) << 24) & 0x0000ff0000000000) | (((a) << 8) & 0x000000ff00000000) \
				| (((a) >> 56) & 0x00000000000000ff) | (((a) >> 40) & 0x000000000000ff00) \
				| (((a) >> 24) & 0x0000000000ff0000) | (((a) >> 8) & 0x00000000ff000000)

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"
# include "sha_common.h"

typedef struct	s_sha512
{
	uint64_t	h[8];
	uint64_t	hh[8];
	uint64_t	w[80];
	uint64_t	block[16];
}				t_sha512;

extern const uint64_t	g_sha512_k[];
extern const uint64_t	g_sha512_init[];


uint8_t			*sha512_calc(t_data *data);

#endif
