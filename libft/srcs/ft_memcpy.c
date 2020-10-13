/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:47:27 by agottlie          #+#    #+#             */
/*   Updated: 2020/10/13 23:32:59 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;

	dest = (unsigned char *)destination;
	src = (const unsigned char *)source;
	while (n--)
		*dest++ = *src++;
	return (dest);
}
