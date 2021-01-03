/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:20:12 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/15 16:36:23 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		des_ecb(t_ssl *ssl)
{
	ssl->master_key = des_ecb_get_key(ssl);
	if (IS_FLAG(ssl->flags, FLAG_P))
		des_ecb_print_key(ssl->master_key);
	if (IS_FLAG(ssl->flags, FLAG_D))
		des_ecb_decrypt_input(ssl);
	else
		des_ecb_encrypt_input(ssl);
}
