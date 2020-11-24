/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:00:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/24 13:27:24 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

t_sha256	*sha256_init(const uint32_t sha_init[])
{
	int			i;
	t_sha256	*e;

	if ((e = (t_sha256 *)malloc(sizeof(t_sha256))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	i = -1;
	while (++i < 8)
		e->h[i] = sha_init[i];
	return (e);
}

void		sha256_generate_w(uint32_t w[], uint32_t block[])
{
	size_t	i;

	i = -1;
	while (++i < 16)
		w[i] = (endian() == SHA256_ENDIAN ? block[i] : lb_conv4(block[i]));
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + SHA256_D0(w[i - 15]) + w[i - 7]
												+ SHA256_D1(w[i - 2]);
}
