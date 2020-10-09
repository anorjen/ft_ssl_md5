/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 12:20:56 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
# define SHA224_H

# define SHA224_ENDIAN B_ENDIAN
# define SHA224_BLOCK_SIZE 64
# define SHA224_OUTPUT_SIZE 56


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"

typedef struct	s_sha224
{
	uint32_t	h[8];
	uint32_t	hh[8];
	uint32_t	w[64];
	uint32_t	block[SHA224_BLOCK_SIZE / 4];
}				t_sha224;

extern const uint32_t	g_sha256_k[];

extern const uint32_t	*g_sha224_k;
extern const uint32_t	g_sha224_init[];


int				sha224(t_data *data);

/*
**	sha224_utils.c
*/

t_sha224			*sha224_init(void);
void				sha224_generate_w(t_sha224 *e);



#endif
