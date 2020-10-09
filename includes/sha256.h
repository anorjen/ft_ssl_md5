/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 12:19:39 by anorjen          ###   ########.fr       */
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

typedef struct	s_sha256
{
	uint32_t	h[8];
	uint32_t	hh[8];
	uint32_t	w[64];
	uint32_t	block[SHA256_BLOCK_SIZE / 4];
}				t_sha256;

extern const uint32_t	g_sha256_k[];
extern const uint32_t	g_sha256_init[];


int				sha256(t_data *data);

/*
**	sha256_utils.c
*/

t_sha256			*sha256_init(void);
void				sha256_generate_w(t_sha256 *e);



#endif
