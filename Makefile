# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 13:36:27 by aschmitt          #+#    #+#              #
#    Updated: 2024/02/15 14:07:39 by aschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I
RM				= rm -f

SRC =	$(SRC_DIR)pipex.c $(SRC_DIR)ft_split.c $(SRC_DIR)aux.c $(SRC_DIR)aux2.c $(SRC_DIR)command.c

OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

G = "\033[32m"
X = "\033[0m"

all: 			$(NAME)

bonus:			$(NAME)

$(NAME): 		$(OBJ)
				@echo $(G)Compiling [$(SRC)]$(X) 
				@$(CC) -o $(NAME) $(OBJ)
				@echo $(G)Compiling [$(NAME)]$(X)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@echo $(G)Delete [Obj]$(X)
				@$(RM) -r $(OBJ_DIR)

fclean: 		clean
				@echo $(G)Delete [$(NAME)]$(X)
				@$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
