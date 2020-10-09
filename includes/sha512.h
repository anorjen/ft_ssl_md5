/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 21:20:48 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# define SHA512_ENDIAN B_ENDIAN
# define SHA512_BLOCK_SIZE 128
# define SHA512_OUTPUT_SIZE 128

# define ROTR64(x, s) (((x) >> (s)) | ((x) << (64 - (s))))
# define SHA512_CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define SHA512_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHA512_S0(x) (ROTR64(x, 28) ^ ROTR64(x, 34) ^ ROTR64(x, 39))
# define SHA512_S1(x) (ROTR64(x, 14) ^ ROTR64(x, 18) ^ ROTR64(x, 41))
# define SHA512_D0(x) (ROTR64(x, 1) ^ ROTR64(x, 8) ^ ((x) >> 7))
# define SHA512_D1(x) (ROTR64(x, 19) ^ ROTR64(x, 61) ^ ((x) >> 6))

# define LB_CONV64(a) (((a) << 56) & 0xff00000000000000) | (((a) << 40) & 0x00ff000000000000) \
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
t_sha512		*sha512_init(const uint64_t sha_init[]);
void			sha512_process_block(t_sha512 *e);
void			sha512_process(t_sha512 *e, void *input, uint64_t size);
uint8_t			*sha512_finish(t_sha512 *e, size_t block_amount);
void			sha512_generate_w(uint64_t w[], uint64_t block[]);
void			*sha512_append_padding_bits(void *input, uint64_t size, int block_size);
void			*sha512_append_length(void *end, uint64_t size, int endian_type);

#endif
