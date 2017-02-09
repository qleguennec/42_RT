# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/02 15:48:09 by bsouchet          #+#    #+#              #
#*   Updated: 2017/02/09 14:23:28 by qle-guen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

CC			= clang

NAME		= libcl.a

FLAGS		= -Wall -Wextra -Werror

DIR_S		= sources

DIR_O		= temporary

HEADER		= include ../libft/include ../libvect/include ../libgnl/include

SOURCES		= cl_init.c \
	cl_krl_build.c \
	cl_krl_exec.c \
	cl_krl_init.c \
	cl_read.c \
	cl_write.c \

SUB_FOLDERS	=

SRCS		= $(addprefix $(DIR_S)/,$(SOURCES))

OBJS		= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

opti:
	@$(MAKE) all -j

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@[ -d $(DIR_O) ] || mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) $(addprefix -I, $(HEADER)) -o $@ -c $<

norme:
	norminette ../fsdl/$(HEADER)
	@echo
	norminette ../fsdl/$(DIR_S)

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all
