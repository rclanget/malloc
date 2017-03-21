# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/08 20:12:26 by rclanget          #+#    #+#              #
#    Updated: 2017/03/21 19:32:31 by rclanget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft_malloc.so

IDIR		=	inc/

SRC_PATH	=	srcs/
SRC_NAME	=	malloc.c \
				realloc.c \
				calloc.c \
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

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< -I $(IDIR) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

test: re
	@make re -C test
