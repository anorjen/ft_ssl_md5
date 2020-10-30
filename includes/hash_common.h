/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:00:14 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/14 18:58:35 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_COMMON_H
# define HASH_COMMON_H

# include <sys/stat.h>
# include <fcntl.h>
# include "ft_dlist.h"
# include "common.h"

typedef struct	s_data
{
	char		*name;
	t_input		type;
	int			fd;
	char		*hash;
	char		*error;
	int			state;
	uint64_t	length;
}				t_data;



typedef struct	s_hash
{
	char		*name;
	char		*(*t_hashfunc)(t_data *data, const struct s_hash *hash);
	int			out_size;
	int			block_size;
	const void	*init;
}				t_hash;

typedef char	*(*t_hashfunc)(t_data *data, t_hash *hash);

ssize_t			read_data(t_data *data, uint8_t buf[], ssize_t size);

/*
** ft_error.c
*/

void			ft_error(char *message);
void			ft_fatal_error(char *message, int is_free);
void			usage(void);
void			ft_clean(void);

/*
** ft_data.c
*/

t_data			*new_data(char *name, int type);
void			del_data(void *data);

/*
** utils.c
*/

int				endian(void);
void			ft_swap(uint8_t *one, uint8_t *two);
uint32_t		lb_conv4(uint32_t a);
uint64_t		lb_conv8(uint64_t a);

/*
** common.c
*/

char			*hash_to_string(uint8_t *hash, int output_size);
void			*append_padding_bits(void *input, uint64_t size,
															int block_size);
void			*append_length(void *end, uint64_t size, int endian_type);
void			u32_to_u8(uint8_t *hash, uint32_t h, int i, int endian_type);
void			u64_to_u8(uint8_t *hash, uint64_t h, int i, int endian_type);

#endif
