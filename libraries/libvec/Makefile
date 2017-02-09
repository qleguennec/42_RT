# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/02 15:48:09 by bsouchet          #+#    #+#              #
#    Updated: 2017/01/07 21:00:28 by bsouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

NAME		= libvec.a

FLAGS		= -Wall -Wextra -Werror -O2

DIR_S		= sources

DIR_O		= temporary

HEADER		= include

SOURCES		= vec3/create.c \
			  vec3/operation.c \
			  vec3/transform.c \
			  vec3/unit.c \
			  vec4/create.c \
			  vec4/operation.c \
			  vec4/transform.c \
			  vec4/unit.c

SUB_FOLDERS	= vec3 vec4

BUILD_DIR	= $(addprefix $(DIR_O)/,$(SUB_FOLDERS))

SRCS		= $(addprefix $(DIR_S)/,$(SOURCES))

OBJS		= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

opti:
	@$(MAKE) all -j

all: temporary $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

temporary: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

$(DIR_O)/%.o: $(DIR_S)/%.c
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ../libvec/$(HEADER)
	@echo
	norminette ../libvec/$(DIR_S)

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all
