# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 11:00:22 by pirichar          #+#    #+#              #
#    Updated: 2023/01/12 10:50:05 by pirichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC			= src
INC			= include
OBJ			= obj
CFILES		= main.c 
HFILES		= colors.h fractol.h keys.h
OFILES		= $(CFILES:.c=.o)
SRCS		= $(addprefix $(SRC)/, $(CFILES))
OBJS		= $(addprefix $(OBJ)/, $(OFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))
LIBS		=	./libft/libft.a
FTMAKE		= cd ./libft && make -s 

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -O3 
RM			= rm -rf

$(OBJ)/%.o:	$(SRC)/%.c
			$(CC) $(CFLAGS) -c $< -o  $@
			$(FTMAKE) 


$(NAME):	$(OBJ) $(OBJS)
			$(CC) $(OBJS) $(LIBS) -lmlx -Lmlx -framework OpenGL -framework AppKit  -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

clean:
			@$(RM) $(OBJS) $(OBJ)
			$(FTMAKE) $@

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norme:
			norminette $(SRCS) $(HEADERS)

	
