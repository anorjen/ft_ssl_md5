/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:38:03 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

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
	uint32_t	block[SHA256_BLOCK_SIZE / 4];
}				t_sha256;

extern const uint32_t	g_k[];
extern const uint32_t	g_h_init[];
uint32_t				g_w[64];


int				sha256(t_data *data);

/*
**	sha256_utils.c
*/

t_sha256			*sha256_init(void);
void				generate_w(t_sha256 *e);



#endif
