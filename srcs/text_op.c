/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:26:21 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/02 10:30:09 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				is_valid_hex_key(uint8_t *s)
{
	int	i;

	i = 0;
	s = ft_strtolower(s);
	while (s[i] != 0)
	{
		if ((s[i] >= '0') && (s[i] <= '9'))
			i++;
		else if ((s[i] >= 'a') && (s[i] <= 'f'))
			i++;
		else
			return (0);
	}
	return (1);
}

uint64_t	text_to_ul64(uint8_t *s)
{
	int				i;
	int				j;
	unsigned long	result;
	unsigned char	c;

	i = 0;
	j = 0;
	result = 0;
	while (i < 8)
	{
		if (!s[j])
			j = 0;
		c = s[j++];
		result <<= 8;
		result += c;
		i++;
	}
	return (result);
}

uint64_t	hex_to_ul64(uint8_t *s)
{
	int				i;
	int				j;
	uint64_t	result;
	uint8_t	c;

	s = ft_strtolower(s);
	i = 0;
	j = 0;
	result = 0;
	while (i < 16)
	{
		c = s[j];
		if (s[j])
			j++;
		result <<= 4;
		if ((c >= '0') && (c <= '9'))
			result += (c - '0');
		if ((c >= 'a') && (c <= 'f'))
			result += ((c - 'a') + 10);
		i++;
	}
	return (result);
}

void			ul64hex_to_stdout(uint64_t ul64)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (i < 16)
	{
		c = (ul64 >> (60 - (i * 4))) & 0xf;
		if (c < 10)
			c += '0';
		else
			c += ('a' - 10);
		write(1, &c, 1);
		i++;
	}
}
