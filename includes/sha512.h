/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/24 13:18:37 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"
# include "common.h"

# define SHA512_ENDIAN B_ENDIAN
# define SHA512_BLOCK_SIZE 128
# define SHA512_OUTPUT_SIZE 128
# define SHA512_OUTPUT_BLOCK_AMOUNT 8

# define SHA384_BLOCK_SIZE 128
# define SHA384_OUTPUT_SIZE 96
# define SHA384_OUTPUT_BLOCK_AMOUNT 6

# define SHA512_224_BLOCK_SIZE 128
# define SHA512_224_OUTPUT_SIZE 56
# define SHA512_224_OUTPUT_BLOCK_AMOUNT 4

# define SHA512_256_BLOCK_SIZE 128
# define SHA512_256_OUTPUT_SIZE 64
# define SHA512_256_OUTPUT_BLOCK_AMOUNT 4

# define SHA512_CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define SHA512_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHA512_S0(x) (ROTR64(x, 28) ^ ROTR64(x, 34) ^ ROTR64(x, 39))
# define SHA512_S1(x) (ROTR64(x, 14) ^ ROTR64(x, 18) ^ ROTR64(x, 41))
# define SHA512_D0(x) (ROTR64(x, 1) ^ ROTR64(x, 8) ^ ((x) >> 7))
# define SHA512_D1(x) (ROTR64(x, 19) ^ ROTR64(x, 61) ^ ((x) >> 6))

typedef struct	s_sha512
{
	uint64_t	h[8];
	uint64_t	hh[8];
	uint64_t	w[80];
	uint64_t	block[16];
}				t_sha512;

extern const uint64_t	g_sha512_k[];
extern const uint64_t	g_sha512_init[];
extern const uint64_t	g_sha384_init[];
extern const uint64_t	g_sha512_224_init[];
extern const uint64_t	g_sha512_256_init[];

uint8_t			*sha512_256_calc(t_data *data);
uint8_t			*sha512_224_calc(t_data *data);
uint8_t			*sha384_calc(t_data *data);

uint8_t			*sha512_calc(t_data *data, const t_hash *hash_handler);
t_sha512		*sha512_init(const uint64_t sha_init[]);

/*
** sha512_utils.c
*/

void			sha512_generate_w(uint64_t w[], uint64_t block[]);
void			*sha512_append_padding_bits(void *input, uint64_t size,
															int block_size);
void			*sha512_append_length(void *end, uint64_t size,
															int endian_type);

#endif
