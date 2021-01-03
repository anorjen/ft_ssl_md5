/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:35:53 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/02 10:40:59 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

uint8_t	*stdin_read_eof(size_t *count)
{
	uint8_t	*buffer;
	uint8_t	*newbuf;
	ssize_t	r;

	if ((buffer = ft_memalloc(1024)) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	*count = 0;
	r = 1;
	while (r != 0)
	{
		if ((r = read(0, &buffer[*count], 1024 - (*count % 1024))) == -1)
			ft_fatal_error("Read ERROR!", 0);
		*count += r;
		if ((r) && (*count) && (*count % 1024 == 0))
		{
			if ((newbuf = ft_memalloc(*count + 1024)) == NULL)
				ft_fatal_error("Malloc ERROR!", 0);
			ft_memcpy(newbuf, buffer, *count);
			free(buffer);
			buffer = newbuf;
			r = 1;
		}
	}
	return (buffer);
}

uint8_t	*stdin_read_line(size_t *count)
{
	uint8_t	*buffer;
	ssize_t	r;

	if ((buffer = ft_memalloc(128)) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	*count = 0;
	r = 1;
	while (r != 0)
	{
		if ((r = read(0, &buffer[*count], 1)) == -1)
			ft_fatal_error("Read ERROR!", 0);
		if ((buffer[*count] == '\n') || (buffer[*count] == '\r'))
		{
			buffer[*count] = 0;
			break ;
		}
		*count += r;
		if (*count > 127)
			break ;
	}
	return (buffer);
}
