/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:02:02 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# define SHA256_BLOCK_SIZE 64

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
	uint32_t	block[SHA256_BLOCK_SIZE / 4];
}				t_sha256;

extern const uint32_t	g_k[];

int				sha256(t_data *data);

/*
**	sha256_utils.c
*/

void	sha256_u32_to_u8(uint8_t *hash, uint32_t h, int i);



#endif
