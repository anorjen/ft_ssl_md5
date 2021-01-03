/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:33:38 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/15 16:31:05 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define DES_E_READ_SIZE 1008

void		des_ecb_put_eight_bytes(uint8_t *data, uint64_t ul64)
{
	unsigned char	c;
	int				i;

	i = 0;
	while (i < 8)
	{
		c = (ul64 >> (56 - (i * 8))) & 0xff;
		data[i] = c;
		i++;
	}
}

uint64_t	des_ecb_process_block(uint64_t input, uint64_t keys[16])
{
	uint64_t	norme;
	uint64_t	left0;
	uint64_t	right0;
	uint64_t	right1;
	int			i;

	norme = make_ip1(input);
	left0 = (norme >> 32) & 0xffffffff;
	right0 = norme & 0xffffffff;
	i = 0;
	while (i < 16)
	{
		norme = get_s_boxes_value(make_ebit(right0) ^ keys[i]);
		right1 = left0 ^ make_pperm(norme);
		left0 = right0;
		right0 = right1;
		i++;
	}
	return (make_ip2((right1 << 32) + left0));
}

uint64_t	des_ecb_get_eight_bytes(uint8_t *data)
{
	uint64_t	result;
	int			i;

	i = 0;
	result = 0;
	while (i < 8)
	{
		result <<= 8;
		result += data[i];
		i++;
	}
	return (result);
}

void		des_ecb_crypt(uint8_t **input, size_t size, uint64_t mk, int enc)
{
	uint64_t	data;
	uint64_t	keys[16];
	size_t		i;

	make_keys(keys, mk, enc);
	i = 0;
	while (i < size)
	{
		data = des_ecb_get_eight_bytes(*input + i);
		data = des_ecb_process_block(data, keys);
		des_ecb_put_eight_bytes(*input + i, data);
		i += 8;
	}
}

static void	print_cipher(uint8_t *output, ssize_t size)
{
	char	*hex_char;
	char	*ret;
	size_t	j;
	int		i;

	hex_char = "0123456789abcdef";
	j = 0;
	if ((ret = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	i = -1;
	while (++i < size)
	{
		ret[j++] = hex_char[output[i] >> 4];
		ret[j++] = hex_char[output[i] & 0x0F];
	}
	ret[j] = '\0';
	write(1, ret, j);
}

static void	process(t_ssl *ssl, void *input, ssize_t size)
{
	uint8_t	*temp;
	uint8_t	*padded;
	ssize_t	new_size;
	uint8_t	pad_byte;
	uint8_t	*output;

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
	des_ecb_crypt(&temp, size, ssl->master_key, 0);
	// if (IS_FLAG(ssl->flags, FLAG_A))
	// {
	// 	output = base64encode(temp, size);
	// 	free(temp);
	// }
	// else
		output = temp;
	// print_cipher(output, size);
	write(ssl->out_fd, output, size);
	free(output);
}

void		des_ecb_encrypt_input(t_ssl *ssl)
{
	ssize_t			ret;
	uint8_t			buf[DES_E_READ_SIZE];
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
	while ((ret = read_data(data, buf, DES_E_READ_SIZE)) > 0)
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
