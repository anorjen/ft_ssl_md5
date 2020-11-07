/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:50:29 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/07 22:21:32 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_common.h"

static ssize_t	read_stdin(t_data *data, uint8_t *buf, ssize_t size)
{
	ssize_t	length;

	length = read(0, buf, size);
	if (length == -1)
	{
		data->state = 1;
		data->error = "Reading stdin ERROR!";
	}
	else
	{
		if (IS_FLAG(g_ssl->flags, FLAG_P))
		{
			write(1, buf, length);
			if (length < size)
				write(1, "\n", 1);
		}
	}
	return (length);
}

static ssize_t	read_string(t_data *data, uint8_t *buf)
{
	ssize_t		length;
	static void	*pos;

	if (pos == NULL)
		pos = (void*)data->name;
	length = ft_strlen((char*)pos);
	length = (length <= 64 ? length : 64);
	ft_memcpy((void*)(buf), (void*)(data->name), length);
	pos += length;
	return (length);
}

static ssize_t	read_file(t_data *data, uint8_t buf[], ssize_t size)
{
	ssize_t	length;

	if (data->fd == -1)
	{
		data->fd = open(data->name, O_RDONLY);
		if (data->fd == -1)
		{
			data->state = 1;
			data->error = "No such file!";
			return (-1);
		}
	}
	length = read(data->fd, buf, size);
	if (length == -1)
	{
		data->state = 1;
		data->error = "Reading file ERROR!";
	}
	if (length < size)
		close(data->fd);
	return (length);
}

ssize_t			read_data(t_data *data, uint8_t *buf, ssize_t size)
{
	ssize_t	length;

	length = -1;
	if (size <= 0)
		return (-1);
	if (data->type == (t_input)IN_STDIN)
	{
		length = read_stdin(data, buf, size);
	}
	else if (data->type == (t_input)IN_STRING)
	{
		length = read_string(data, buf);
	}
	else if (data->type == (t_input)IN_FILE)
	{
		length = read_file(data, buf, size);
	}
	return (length);
}
