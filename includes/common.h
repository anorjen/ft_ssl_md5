/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:00:14 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 18:42:44 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define L_ENDIAN 0
# define B_ENDIAN 1

# include <sys/stat.h>
# include <fcntl.h>

# include "ft_dlist.h"

typedef enum	e_input
{
	IN_STDIN = 1,
	IN_STRING = 2,
	IN_FILE = 3
}				t_input;

typedef struct	s_ssl
{
	int			r_flag;
	int			q_flag;
	int			p_flag;
	int			s_flag;
	t_dlist		*datalist;
	char		*hash_type;
}				t_ssl;

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

t_ssl	*g_ssl;

ssize_t	read_data(t_data *data, uint8_t buf[], ssize_t size);

/*
** ft_error.c
*/

void	ft_error(char *message);
void	ft_fatal_error(char *message, int is_free);
void	usage(void);
void	ft_clean(void);


/*
** ft_data.c
*/

t_data	*new_data(char *name, int type);
void	del_data(void *data);

/*
** utils.c
*/

uint32_t		rotate_left(uint32_t x, uint32_t s);
uint32_t		rotate_right(uint32_t x, uint32_t s);
int				endian(void);
void			ft_swap(uint8_t *one, uint8_t *two);
uint32_t		l_to_b_endian(uint32_t a);


#endif
