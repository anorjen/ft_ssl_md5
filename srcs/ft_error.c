/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:49:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/07 22:13:14 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_common.h"

void	ft_error(char *message)
{
	write(2, "ft_ssl: ", 8);
	if (g_ssl && g_ssl->handler && g_ssl->handler->name)
	{
		write(2, g_ssl->handler->name, ft_strlen(g_ssl->handler->name));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	ft_fatal_error(char *message, int is_free)
{
	write(2, "ft_ssl: ", 8);
	if (g_ssl && g_ssl->handler && g_ssl->handler->name)
	{
		write(2, g_ssl->handler->name, ft_strlen(g_ssl->handler->name));
		write(2, ": ", 2);
	}
	if (message != NULL)
	{
		write(2, message, ft_strlen(message));
		if (is_free)
			free(message);
	}
	write(2, "\n", 1);
	ft_clean();
	exit(1);
}

void	usage(void)
{
	write(1, "usage:\n", 7);
	// write(1,
	// "./ft_ssl [alg] -q|-p|-r|-s [string] [file1] [file2] [...]]\n", 65);
	// write(1, "	-q -- quiet ouput\n", 19);
	// write(1, "	-p -- STDIN to STDOUT\n", 23);
	// write(1, "	-r -- recursive ouput\n", 23);
	// write(1, "	-s -- calc string hash\n", 24);

	write(1, "Standard commands:\nMessage Digest commands:\n\
	md5\n\
	sha256\n\
	sha224\n\
	sha512\n\
	sha384\n\
	sha512-224\n\
	sha512-256\n\
	Cipher commands:\n\
	base64\n\
	des\n\
	des-ecb\n\
	des-cbc\n", 180);
	exit(1);
}

void	ft_clean(void)
{
	if (g_ssl)
	{
		if (g_ssl->datalist)
			ft_dlist_del(&(g_ssl->datalist), del_data);
		free(g_ssl);
	}
}
