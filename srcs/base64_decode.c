/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:48:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/15 00:40:02 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define BLOCK_SIZE 1024

static void	process_block(char *ptr, char *str)
{
	ptr[0] = (str[0] << 2 & 0xfc) | (str[1] >> 4 & 0x03);
	ptr[1] = ((str[1] << 4) & 0xf0) | ((str[2] >> 2) & 0x0f);
	ptr[2] = ((str[2] << 6) & 0xc0) | ((str[3]) & 0x3f);
}

static int	get_num(char c)
{
	char	*values;
	int		i;

	values = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	i = -1;
	while (values[++i])
	{
		if (c == values[i])
			return (i);
	}
	return (-1);
}

static void	str_to_nums(char *str, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (str[i] == '=')
			str[i] = 0;
		else
			str[i] = get_num(str[i]);
		if (str[i] == -1)
			ft_fatal_error("Not base64 string!", 0);
	}
}

static char	*process(char *str, int size)
{
	char	*res;
	char	*ptr;
	int		i;

	str_to_nums(str, size);
	res = ft_strnew((size / 4) * 3);
	ptr = res;
	i = -1;
	while (++i < size / 4)
	{
		process_block(ptr, &(str[i * 4]));
		ptr += 3;
	}
	return (res);
}

int	trim_end(char *str, int size)
{
	int	i;

	i = size - 1;
	while (str[i] == '\0' || str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
	{
		--i;
	}
	return (i + 1);
}

void		base64_decode(t_ssl *ssl)
{
	t_data		*data;
	ssize_t		ret;
	char		buf[BLOCK_SIZE];
	char		*res;
	int			fd;

	fd = 1;
	data = (t_data*)(ssl->datalist->content);
	while ((ret = read_data(data, (uint8_t*)buf, BLOCK_SIZE)) > 0)
	{
		if (ret < BLOCK_SIZE)
			ret = trim_end(buf, ret);
		res = process(buf, ret);
		data->length += ret;
		if (fd == 1 && IS_FLAG(ssl->flags, FLAG_O))
		{
			if ((fd = open(ssl->output, O_WRONLY | O_TRUNC | O_CREAT)) == -1)
				ft_fatal_error("No such output file!", 0);
		}
		write(fd, res, ft_strlen(res));
		free(res);
	}
	write (fd, "\n", 1);
	if (IS_FLAG(ssl->flags, FLAG_O))
		close(fd);
}
