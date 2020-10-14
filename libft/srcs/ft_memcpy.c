/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:47:27 by agottlie          #+#    #+#             */
/*   Updated: 2020/10/14 17:58:14 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ALIGN(s) ((uintptr_t)(s) & (sizeof(long) - 1))
#define C_CAST(a,b,c,d) (a)=(unsigned char *)(b),(c)=(unsigned char const *)(d)
#define L_CAST(a,b,c,d) (a)=(long *)(b),(c)=(long const *)(d)

/*
** void	*ft_memcpy(void *destination, const void *source, size_t n)
** {
** 	unsigned char		*dest;
** 	const unsigned char	*src;
**
** 	dest = (unsigned char *)destination;
** 	src = (const unsigned char *)source;
** 	while (n--)
** 		*dest++ = *src++;
** 	return (dest);
** }
*/

void	*ft_memcpy(void *dst, void const *src, size_t len)
{
	unsigned char		*pc_dst;
	unsigned char const	*pc_src;
	long				*pl_dst;
	long const			*pl_src;

	C_CAST(pc_dst, dst, pc_src, src);
	if (len >= sizeof(long) * 2 && ALIGN(src) == ALIGN(dst))
	{
		while (ALIGN(pc_src) != 0)
		{
			*pc_dst++ = *pc_src++;
			--len;
		}
		L_CAST(pl_dst, dst, pl_src, src);
		while (len >= sizeof(long))
		{
			*pl_dst++ = *pl_src++;
			len -= sizeof(long);
		}
		C_CAST(pc_dst, pl_dst, pc_src, pl_src);
	}
	while (len--)
		*pc_dst++ = *pc_src++;
	return (dst);
}
