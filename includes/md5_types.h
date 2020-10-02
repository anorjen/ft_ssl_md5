/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:34:49 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/01 12:17:13 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_TYPES_H
# define MD5_TYPES_H
# include <stdint.h>

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
	uint32_t	block[16];
}				t_md5;

typedef struct	s_md5_utils
{
	uint32_t	f;
	uint8_t		g;
}				t_md5_utils;

#endif
