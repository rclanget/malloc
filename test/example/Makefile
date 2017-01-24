# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zipo <zipo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/08 20:12:26 by rclanget          #+#    #+#              #
#    Updated: 2017/01/24 12:15:29 by zipo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	test

IDIR		=	inc/

SRC_PATH	=	test_src/
SRC_NAME	= 	*.c
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ 		=	$(SRC:.c=.o)

FLAGS 		=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -c $(NAME) $(OBJ) && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< -I $(IDIR) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
