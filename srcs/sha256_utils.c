/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:00:13 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 18:59:22 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_generate_w(uint32_t w[], uint32_t block[])
{
	size_t	i;

	i = -1;
	while (++i < 16)
		w[i] = (endian() == SHA256_ENDIAN ? block[i] : LB_CONV32(block[i]));
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + SHA256_D0(w[i - 15]) + w[i - 7]
												+ SHA256_D1(w[i - 2]);
}
