/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:55:37 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 21:30:42 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_H
# define SHA384_H

# define SHA384_ENDIAN B_ENDIAN
# define SHA384_BLOCK_SIZE 128
# define SHA384_OUTPUT_SIZE 96

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"
# include "common.h"
# include "sha512.h"

extern const uint64_t	g_sha384_init[];

uint8_t			*sha384_calc(t_data *data);

#endif
