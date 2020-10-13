/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 12:08:50 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"
# include "common.h"

# define SHA256_ENDIAN B_ENDIAN
# define SHA256_BLOCK_SIZE 64
# define SHA256_OUTPUT_SIZE 64
# define SHA256_OUTPUT_BLOCK_AMOUNT 8

# define SHA224_BLOCK_SIZE 64
# define SHA224_OUTPUT_SIZE 56
# define SHA224_OUTPUT_BLOCK_AMOUNT 7

# define SHA256_CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define SHA256_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHA256_S0(x) (ROTR32(x, 2) ^ ROTR32(x, 13) ^ ROTR32(x, 22))
# define SHA256_S1(x) (ROTR32(x, 6) ^ ROTR32(x, 11) ^ ROTR32(x, 25))
# define SHA256_D0(x) (ROTR32(x, 7) ^ ROTR32(x, 18) ^ ((x) >> 3))
# define SHA256_D1(x) (ROTR32(x, 17) ^ ROTR32(x, 19) ^ ((x) >> 10))

typedef struct	s_sha256
{
	uint32_t	h[8];
	uint32_t	hh[8];
	uint32_t	w[64];
	uint32_t	block[16];
}				t_sha256;

extern const uint32_t	g_sha256_k[];
extern const uint32_t	g_sha256_init[];
extern const uint32_t	g_sha224_init[];

uint8_t			*sha224_calc(t_data *data);

uint8_t			*sha256_calc(t_data *data, const t_hash *hash_handler);

void			sha256_generate_w(uint32_t w[], uint32_t block[]);


#endif
