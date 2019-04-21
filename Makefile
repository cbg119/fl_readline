# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 13:41:11 by cbagdon           #+#    #+#              #
#    Updated: 2019/04/17 16:35:29 by cbagdon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libfl_readline.a

SRC = main.c \
		term.c \
		input.c \
		cursor_movement.c

INCLUDES = includes/ \
		-I ../libft/includes

LFT = -ltermcap

FLAGS = -Wall -Wextra -Werror

OBJECTS = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME):
	@mkdir build
	@gcc $(FLAGS) -I $(INCLUDES) -c $(addprefix src/,$(SRC))
	@mv $(OBJECTS) build/
	@ar -rcs $(NAME) $(addprefix build/,$(OBJECTS))

clean:
	rm -rf build

fclean: clean
	rm -rf $(NAME)

re: fclean all
