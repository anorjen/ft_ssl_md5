/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_decript.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:35:47 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/15 16:48:05 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define DES_D_READ_SIZE 1024

void	des_ecb_decrypt_input(t_ssl *ssl, void *input, ssize_t size)
{
	uint8_t	*temp;
	uint8_t	*padded;
	ssize_t	new_size;
	uint8_t	pad_byte;
	uint8_t	*output;

	// if (IS_FLAG(ssl->flags, FLAG_A))
	// {
	// 	*output = base64decode(*input, size);
	// 	free(*input);
	// 	*input = *output;
	// }
	temp = (uint8_t*)input;
	if (size % 8 != 0)
	{
		new_size = ((size / 8) + 1) * 8;
		pad_byte = new_size - size;
		if ((padded = (uint8_t*)malloc(sizeof(uint8_t) * (new_size + 1))) == NULL)
			ft_fatal_error("Malloc ERROR!", 0);
		ft_memcpy(padded, temp, size);
		temp = padded;
		while (size < new_size)
			(temp)[size++] = pad_byte;
	}
	ecb_crypto(&temp, size, ssl->master_key, 1);
	pad_byte = temp[size - 1];
	if ((pad_byte >= 1) && (pad_byte <= 8))
	{
		new_size = size - pad_byte;
		while ((temp[new_size] == pad_byte) && (new_size < size))
			new_size++;
		if (new_size == size)
			size -= pad_byte;
	}
	*output = *(uint8_t*)input;
}

void		des_ecb_decrypt_input(t_ssl *ssl)
{
	ssize_t			ret;
	uint8_t			buf[DES_D_READ_SIZE];
	t_data			*data;

	if (IS_FLAG(ssl->flags, FLAG_I))
		ft_dlist_addback(&(ssl->datalist), ft_dlist_new_elem(
			new_data(ssl->input, (t_input)IN_FILE), sizeof(t_data), 1));
	else
		ft_dlist_addback(&(ssl->datalist), ft_dlist_new_elem(
			new_data(0, (t_input)IN_STDIN), sizeof(t_data), 1));
	data = (t_data *)(ssl->datalist->content);
	if (IS_FLAG(ssl->flags, FLAG_O))
		ssl->out_fd = open(ssl->output, O_WRONLY | O_CREAT | O_TRUNC,
															S_IREAD | S_IWRITE);
	while ((ret = read_data(data, buf, DES_D_READ_SIZE)) > 0)
	{
		process(ssl, buf, ret);
		data->length += ret;
	}
	write(1, "\n", 1);
	if (IS_FLAG(ssl->flags, FLAG_O))
		close(ssl->out_fd);

	// if (ret == -1)
	// 	return (NULL);
}
