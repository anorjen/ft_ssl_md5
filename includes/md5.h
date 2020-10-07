/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 14:25:30 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_BLOCK_SIZE 64

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"

typedef struct	s_md5
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;
	uint32_t	block[MD5_BLOCK_SIZE / 4];
}				t_md5;

typedef struct	s_md5_utils
{
	uint32_t	f;
	uint8_t		g;
}				t_md5_utils;

extern const uint32_t	g_t[];
extern const uint32_t	g_s[];

int			md5(t_data *data);
t_md5_utils	func_f(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_g(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_h(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_i(uint32_t x, uint32_t y, uint32_t z, int i);


#endif
