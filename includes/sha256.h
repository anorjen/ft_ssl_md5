/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 13:18:18 by anorjen          ###   ########.fr       */
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
# include "sha_common.h"

typedef struct	s_sha256
{
	uint32_t	h[8];
	uint32_t	hh[8];
	uint32_t	w[64];
	uint32_t	block[SHA256_BLOCK_SIZE / 4];
}				t_sha256;

extern const uint32_t	g_sha256_k[];
extern const uint32_t	g_sha256_init[];


uint8_t			*sha256_calc(t_data *data);

#endif
