# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/17 18:36:33 by tlepeche          #+#    #+#              #
#    Updated: 2016/10/17 18:51:41 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

SRC =	test.c \
		malloc.c \
		free.c \

SRCDIR = src/

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

CC = clang

INC = -I ./includes

LIB = -L libft -lft

RM = rm -rf

FS = -fsanitize=address

C_FLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) -o $(NAME) $^
	@echo ""
	@echo $(PX_STR) : $(EX_STR)
	@echo ""

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(C_FLAGS) $(INC) $< -o $@ 
	@echo $(CC_STR) $*

lft:
	make -C libft

clean:
	@$(RM) $(OBJDIR)
	@echo $(RM_STR) objects

fclean: clean
#	@make fclean -C libft
	@$(RM) $(NAME)
	@echo $(RM_STR) $(NAME)

re: fclean all

NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;33m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
RM_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[CC]$(NO_COLOR)
EX_STR = $(EX_COLOR)$(NAME)$(NO_COLOR)
PX_STR = $(PX_COLOR)Binary compiled successfully$(NO_COLOR)
RM_STR = $(RM_COLOR)Remove$(NO_COLOR)
