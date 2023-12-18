# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 13:36:27 by aschmitt          #+#    #+#              #
#    Updated: 2023/12/18 16:40:07 by aschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

# Directories
INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/

# Compielr and Flags
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I
RM				= rm -f

# Source Files
SRC =	$(SRC_DIR)pipex.c $(SRC_DIR)ft_split.c $(SRC_DIR)aux.c $(SRC_DIR)aux2.c

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))
# Build rules
all: 			$(NAME)

$(NAME): 		$(OBJ)
				@$(CC) -o $(NAME) $(OBJ)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)

fclean: 		clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
