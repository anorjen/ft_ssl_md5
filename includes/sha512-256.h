/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512-256.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 21:50:03 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_256_H
# define SHA512_256_H

# define SHA512_256_ENDIAN B_ENDIAN
# define SHA512_256_BLOCK_SIZE 128
# define SHA512_256_OUTPUT_SIZE 64

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"
# include "sha512.h"

extern const uint64_t	g_sha512_256_init[];

uint8_t			*sha512_256_calc(t_data *data);

#endif
