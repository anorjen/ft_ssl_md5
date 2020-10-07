/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:00:59 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/07 19:01:26 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_u32_to_u8(uint8_t *hash, uint32_t h, int i)
{
	if (endian() == B_ENDIAN)
	{
		hash[i * 4 + 0] = (uint8_t)(h >> 0);
		hash[i * 4 + 1] = (uint8_t)(h >> 8);
		hash[i * 4 + 2] = (uint8_t)(h >> 16);
		hash[i * 4 + 3] = (uint8_t)(h >> 24);
	}
	else
	{
		hash[i * 4 + 0] = (uint8_t)(h >> 24);
		hash[i * 4 + 1] = (uint8_t)(h >> 16);
		hash[i * 4 + 2] = (uint8_t)(h >> 8);
		hash[i * 4 + 3] = (uint8_t)(h >> 0);
	}
}
