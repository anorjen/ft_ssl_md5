/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:31:20 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/08 19:01:45 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	process_block(char *ptr, char *str)
{
	ptr[0] = (str[0] >> 2) & 0x3f;
	ptr[1] = ((str[0] << 4) & 0x30) | ((str[1] >> 4) & 0x0f);
	ptr[2] = ((str[1] << 2) & 0x3c) | ((str[2] >> 6) & 0x03);
	ptr[3] = (str[2] & 0x3f);
}

static char	*process(char *str, int size)
{
	int		mod;
	char	*new;
	char	*res;
	char	*ptr;
	int		i;

	if ((mod = (size % 3)) != 0)
	{
		new = ft_strnew(size + (3 - mod));
		ft_memcpy(new, str, size);
		str = new;
		size = size + (3 - mod);
	}
	res = ft_strnew((size / 3) * 4);
	ptr = res;
	i = -1;
	while (++i < size / 3)
	{
		process_block(ptr, &(str[i * 3]));
		ptr += 4;
	}
	if (mod)
		free(str);
	return (res);

}

static void	ft_print_cipher(t_ssl *ssl, char *res, int size)
{
	int		fd;
	char	*values;
	char	*str;
	int		i;
	int		add;

	fd = 1;
	values = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	if (IS_FLAG(ssl->flags, FLAG_O))
	{
		if ((fd = open(ssl->output, O_WRONLY)) == -1)
			ft_error("No such output file!");
	}
	fd = (fd == -1 ? 1 : fd);
	add = (3 - size % 3);
	size =(size + add) / 3 * 4;
	str = ft_strnew(size);
	i = -1;
	while (++i < size - add)
		str[i] = values[(int)res[i]];
	while (add-- > 0)
		str[i++] = '=';
	write(fd, str, size);
	write(fd, "\n", 1);
}

void	base64_encode(t_ssl *ssl)
{
	t_data		*data;
	ssize_t		ret;
	char		buf[900];
	char		*res;

	data = (t_data*)(ssl->datalist->content);
	while ((ret = read_data(data, (uint8_t*)buf, 900)) > 0)
	{
		res = process(buf, ret);
		data->length += ret;
		ft_print_cipher(ssl, res, ret);
	}
}
