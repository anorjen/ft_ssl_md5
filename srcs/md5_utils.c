/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:29:03 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 12:16:38 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static void	generate_g(t_md5 *e)
{
	int	i;

	i = -1;
	while (++i < 64)
	{
		if (i >= 0 && i < 16)
			e->g[i] = i;
		else if (i >= 16 && i < 32)
			e->g[i] = (5 * i + 1) % 16;
		else if (i >= 32 && i < 48)
			e->g[i] = (3 * i + 5) % 16;
		else if (i >= 48 && i < 64)
			e->g[i] = (7 * i) % 16;
	}
}

t_md5		*md5_init(void)
{
	t_md5	*e;

	if ((e = (t_md5 *)malloc(sizeof(t_md5))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	generate_g(e);
	if (endian() == L_ENDIAN)
	{
		e->h[0] = 0x67452301;
		e->h[1] = 0xefcdab89;
		e->h[2] = 0x98badcfe;
		e->h[3] = 0x10325476;
	}
	else
	{
		e->h[0] = 0x01234567;
		e->h[1] = 0x89abcdef;
		e->h[2] = 0xfedcba98;
		e->h[3] = 0x76543210;
	}
	return (e);
}
