# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/08 20:12:26 by rclanget          #+#    #+#              #
#    Updated: 2017/03/23 17:22:34 by rclanget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so

IDIR		=	inc/

SRC_PATH	=	srcs/
SRC_NAME	=	malloc.c \
				realloc.c \
				free.c \
				ft_singleton.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_print.c \
				ft_putstr_fd.c \
				ft_putnbr_fd.c \
				ft_putchar_fd.c \
				ft_strlen.c \
				ft_get_new_block.c \
				ft_get_free_block.c \
				ft_get_block_in_page.c \
				show_alloc_mem.c

SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ 		=	$(SRC:.c=.o)

FLAGS 		=	-Wall -Wextra -Werror -fPIC

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -shared -o $(NAME) $(OBJ) && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";
	@export LD_LIBRARY_PATH=/home/zipo/workspace/malloc/
	@ln -s libft_malloc_x86_64_Darwin.so libft_malloc.so

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< -I $(IDIR) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f libft_malloc.so

re: fclean all

test: re
	@make re -C test
