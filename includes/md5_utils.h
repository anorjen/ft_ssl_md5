/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:33:28 by anorjen           #+#    #+#             */
/*   Updated: 2020/09/28 15:36:03 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_UTILS_H
# define MD5_UTILS_H
# include "md5_types.h"

t_md5_utils	func_f(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_g(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_h(uint32_t x, uint32_t y, uint32_t z, int i);
t_md5_utils	func_i(uint32_t x, uint32_t y, uint32_t z, int i);

#endif
