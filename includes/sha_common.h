/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_common.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 12:56:23 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 13:13:12 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_COMMON_H
# define SHA_COMMON_H

# include "common.h"

# define SHA_ENDIAN B_ENDIAN

void	sha_generate_w32(uint32_t w[], uint32_t block[]);
void	sha_generate_w64(uint64_t w[], uint64_t block[]);

#endif
