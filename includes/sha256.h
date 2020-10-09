/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 20:50:26 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# define SHA256_ENDIAN B_ENDIAN
# define SHA256_BLOCK_SIZE 64
# define SHA256_OUTPUT_SIZE 64


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"

# define ROTR32(x, s) (((x) >> (s)) | ((x) << (32 - (s))))
# define SHA256_CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define SHA256_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHA256_S0(x) (ROTR32(x, 2) ^ ROTR32(x, 13) ^ ROTR32(x, 22))
# define SHA256_S1(x) (ROTR32(x, 6) ^ ROTR32(x, 11) ^ ROTR32(x, 25))
# define SHA256_D0(x) (ROTR32(x, 7) ^ ROTR32(x, 18) ^ ((x) >> 3))
# define SHA256_D1(x) (ROTR32(x, 17) ^ ROTR32(x, 19) ^ ((x) >> 10))

# define LB_CONV32(a) ((((a) << 24) & 0xff000000) | (((a) << 8) & 0x00ff0000) \
					| (((a) >> 24) & 0x000000ff) | (((a) >> 8) & 0x0000ff00))

typedef struct	s_sha256
{
	uint32_t	h[8];
	uint32_t	hh[8];
	uint32_t	w[64];
	uint32_t	block[16];
}				t_sha256;

extern const uint32_t	g_sha256_k[];
extern const uint32_t	g_sha256_init[];


uint8_t			*sha256_calc(t_data *data);
t_sha256		*sha256_init(const uint32_t sha_init[]);
void			sha256_process_block(t_sha256 *e);
void			sha256_process(t_sha256 *e, void *input, uint64_t size);
uint8_t			*sha256_finish(t_sha256 *e, size_t block_amount);

void			sha256_generate_w(uint32_t w[], uint32_t block[]);


#endif
