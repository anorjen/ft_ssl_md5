/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:26:35 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/02 10:48:09 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	des_ecb_hex_key_invalid_format(void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_putstr("non-hex digit\ninvalid hex key value\n");
	exit(0);
}

uint64_t	des_ecb_get_key(t_ssl *ssl)
{
	unsigned char	*str_key;
	unsigned long	size;

	if (ssl->key == NULL)
	{
		ft_putstr("enter des key in hex: ");
		str_key = stdin_read_line(&size);
		if (is_valid_hex_key(str_key))
		{
			ssl->master_key = hex_to_ul64(str_key);
			free(str_key);
			return (ssl->master_key);
		}
		else
			des_ecb_hex_key_invalid_format(str_key);
	}
	else
	{
		if (is_valid_hex_key((uint8_t *)ssl->key))
			return (hex_to_ul64((uint8_t *)ssl->key));
		else
			des_ecb_hex_key_invalid_format(NULL);
	}
	return (0);
}

void	des_ecb_print_key(uint64_t master_key)
{
	ft_putstr("key=");
	ul64hex_to_stdout(master_key);
	ft_putstr("\n");
}
