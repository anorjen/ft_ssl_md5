/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 12:01:35 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"
# include "common.h"

# define MD5_ENDIAN L_ENDIAN
# define MD5_BLOCK_SIZE 64
# define MD5_OUTPUT_SIZE 32
# define MD5_OUTPUT_BLOCK_AMOUNT 4

typedef struct	s_md5
{
	uint32_t	h[4];
	uint32_t	hh[4];
	uint32_t	block[16];
	uint8_t		g[64];
}				t_md5;

extern const uint32_t	g_t[];
extern const uint32_t	g_s[];

uint8_t		*md5_calc(t_data *data, const t_hash *hash_handler);

/*
**	md5_utils.c
*/

t_md5		*md5_init(void);


#endif
