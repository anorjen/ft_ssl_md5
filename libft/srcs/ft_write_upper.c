/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_upper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:33:30 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/14 19:00:38 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write_upper(int fd, char *str, size_t size)
{
	size_t	i;
	char	*str_upper;

	if ((str_upper = ft_strnew(size)) != NULL)
	{
		i = -1;
		while (++i < size)
		{
			str_upper[i] = ft_toupper(str[i]);
		}
		write(fd, str_upper, size);
		free(str_upper);
	}
}
