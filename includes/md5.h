/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 16:42:28 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_ENDIAN L_ENDIAN
# define MD5_BLOCK_SIZE 64
# define MD5_OUTPUT_SIZE 32

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"

typedef struct	s_md5
{
	uint32_t	h[4];
	uint32_t	hh[4];
	uint32_t	block[16];
}				t_md5;

typedef struct	s_md5_utils
{
	uint32_t	f;
	uint8_t		g;
}				t_md5_utils;

extern const uint32_t	g_t[];
extern const uint32_t	g_s[];

uint8_t			*md5_calc(t_data *data);

/*
**	md5_utils.c
*/

t_md5_utils	func_f(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_g(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_h(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_i(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5		*md5_init(void);


#endif
