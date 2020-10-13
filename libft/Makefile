# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/24 15:42:48 by anorjen           #+#    #+#              #
#    Updated: 2020/10/13 23:44:16 by anorjen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang
FLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I$(HEADERS_DIRECTORY)

HEADERS_LIST =	ft_printf.h \
				ft_dlist.h \
				libft.h \
				get_next_line.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./srcs/
SOURCES_LIST = 	ft_atoi.c		ft_bzero.c			ft_colorize_str.c	ft_isalnum.c		ft_isalpha.c \
				ft_isascii.c	ft_isdigit.c		ft_isprint.c		ft_itoa.c			ft_lstadd.c \
				ft_lstchange.c	ft_lstdel.c			ft_lstdelone.c		ft_lstiter.c		ft_lstjoin.c \
				ft_lstmap.c		ft_lstnew.c			ft_lstprint.c		ft_make_lst.c		ft_memalloc.c \
				ft_memccpy.c	ft_memchr.c			ft_memcmp.c			ft_memcpy.c			ft_memdel.c \
				ft_memmove.c	ft_memset.c			ft_putchar.c		ft_putchar_fd.c		ft_putendl.c \
				ft_putendl_fd.c	ft_putnbr.c			ft_putnbr_fd.c		ft_putstr.c			ft_putstr_fd.c \
				ft_realloc.c	ft_strcat.c			ft_strchr.c			ft_strclr.c			ft_strcmp.c \
				ft_strcpy.c		ft_strdel.c			ft_strdup.c			ft_strequ.c			ft_striter.c \
				ft_striteri.c	ft_strjoin.c		ft_strlcat.c		ft_strlen.c			ft_strmap.c \
				ft_strmapi.c	ft_strncat.c		ft_strncmp.c		ft_strncpy.c		ft_strnequ.c \
				ft_strnew.c		ft_strnstr.c		ft_strrchr.c		ft_strsplit.c		ft_strstr.c \
				ft_strsub.c		ft_strsubi.c		ft_strtrim.c		ft_strtrim_c.c		ft_tolower.c \
				ft_toupper.c	ft_word_count_c.c	get_next_line.c		ft_write_upper.c

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))


DLIST_SRC_DIRECTORY = ./srcs/dlist/
DLIST_SRC_LIST = 	ft_dlist_addback.c	ft_dlist_addbegin.c	ft_dlist_add.c	ft_dlist_del.c	ft_dlist_delone.c \
					ft_dlist_new.c		ft_dlist_rewind.c	ft_dlist_size.c	ft_dlist_new_elem.c

DLIST_SOURCES = $(addprefix $(DLIST_SRC_DIRECTORY), $(DLIST_SRC_LIST))
DLIST_OBJ_DIRECTORY = objects/dlist/
DLIST_OBJ_LIST = $(patsubst %.c, %.o, $(DLIST_SRC_LIST))
DLIST_OBJECTS	= $(addprefix $(DLIST_OBJ_DIRECTORY), $(DLIST_OBJ_LIST))


PRINTF_SRC_DIRECTORY = ./srcs/printf/
PRINTF_SRC_LIST = 	ft_itoa_st.c		ft_ntoa.c		print_floatfuncs.c		print_string_colour.c \
					flag_modifiers.c	ft_itoa_uh.c	ft_printf.c				print_functions.c	print_u.c \
					float_functions.c	ft_itoa_uhh.c	helper_functions.c		print_int2.c		searchers.c \
					ft_fldtoa_funcs.c	ft_itoa_ui.c	print_int.c				utilities2.c \
					ft_ftoa.c			ft_itoa_uim.c	ntoa_ox_modificators.c	print_ld.c			utilities.c \
					ft_itoa_im.c		ft_itoa_ull.c	print_char.c			print_oxp.c			validators.c \
					ft_itoa_ll.c		ft_ldtoa.c		print_float.c			print_string.c		zero_cases_xop.c

PRINTF_SOURCES = $(addprefix $(PRINTF_SRC_DIRECTORY), $(PRINTF_SRC_LIST))
PRINTF_OBJ_DIRECTORY = objects/printf/
PRINTF_OBJ_LIST = $(patsubst %.c, %.o, $(PRINTF_SRC_LIST))
PRINTF_OBJECTS	= $(addprefix $(PRINTF_OBJ_DIRECTORY), $(PRINTF_OBJ_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(HEADERS) $(DLIST_OBJECTS) $(PRINTF_OBJECTS) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS) $(DLIST_OBJECTS) $(PRINTF_OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@mkdir -p $(DLIST_OBJ_DIRECTORY)
	@mkdir -p $(PRINTF_OBJ_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o: $(SOURCES_DIRECTORY)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(DLIST_OBJ_DIRECTORY)%.o: $(DLIST_SRC_DIRECTORY)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(PRINTF_OBJ_DIRECTORY)%.o: $(PRINTF_SRC_DIRECTORY)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
