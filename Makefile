# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/08 20:12:26 by rclanget          #+#    #+#              #
#    Updated: 2017/01/24 14:05:12 by zipo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft_malloc.so

IDIR		=	inc/

SRC_PATH	=	srcs/
SRC_NAME	=	block.c check_adress.c free.c ft_bzero.c ft_memcpy.c ft_print.c\
				ft_put_fd.c malloc.c page.c realloc.c show_alloc_mem.c

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
