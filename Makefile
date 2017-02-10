# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/07 22:13:23 by bsouchet          #+#    #+#              #
#*   Updated: 2017/02/10 08:03:57 by qle-guen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

C			= clang

NAME		= rt

FLAGS		= -Wall -Wextra -Werror -O2

OPENCL_F	= -framework OpenCL

SDL2_F		= -framework SDL2 -framework SDL2_ttf -framework SDL2_image  -F ./frameworks/

SDL2_P		= -rpath @loader_path/frameworks/

SDL2_I		= -I ./frameworks/SDL2.framework/Headers

SDL2_TTF_I	= -I ./frameworks/SDL2_ttf.framework/Headers

SDL2_IMG_I	= -I ./frameworks/SDL2_image.framework/Headers

FSDL		= libraries/fsdl

LIBFT		= libraries/libft

LIBGNL		= libraries/libgnl

LIBVECT		= libraries/libvect

LIBCL		= libraries/libcl

LIBFMT		= libraries/libfmt

DIR_S		= sources

DIR_O		= temporary

IMG_DIR		= saved_images

HEADER		= include \
		  libraries/libft/include \
		  libraries/libvect/include \
		  libraries/libgnl/include \
		  libraries/libcl/include \
		  libraries/libfmt/include


SOURCES		= main.c \
			  parser/init_global_stuctures.c \
			  parser/clear_buffer.c \
			  parser/check_balises.c \
			  parser/check_elements.c \
			  parser/get_numbers.c \
			  parser/get_informations.c \
			  parser/assign_values.c \
			  parser/add_elements.c \
			  gui/init_structure.c \
			  gui/draw_elements.c \
			  gui/draw_info_and_state.c \
			  gui/draw_outliner.c \
			  gui/draw_panels.c \
			  gui/draw_scene_parameters.c \
			  gui/save_to_png.c \
			  handle/elements.c \
			  handle/events.c \
			  handle/errors.c \
			  handle/mouse.c \
			  handle/keyboard.c \
			  handle/buttons.c \
			  handle/linked_lists.c \
			  handle/threads.c \
			  handle/info_bar.c \
			  handle/outliner.c \
			  handle/special_mode.c \
			  renderer/init_renderer.c \
			  renderer/start_renderer.c \
			  misc/verbose_mode.c \
			  misc/free_elements.c \
			  cl_build/rt_cl_init.c \
			  cl_build/rt_cl_exec.c

SUB_FOLDERS	= gui handle misc parser renderer cl cl_build

BUILD_DIR	= $(addprefix $(DIR_O)/,$(SUB_FOLDERS))

SRCS		= $(addprefix $(DIR_S)/,$(SOURCES))

OBJS		= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

opti:
	@$(MAKE) all -j

all: temporary $(NAME)

$(NAME): $(OBJS)
	@make -C $(FSDL)
	@make -C $(LIBFT)
	@make -C $(LIBVECT)
	@make -C $(LIBGNL)
	@make -C $(LIBCL)
	@make -C $(LIBFMT)
	@$(CC) $(FLAGS) -L $(LIBFT) -lft -L $(FSDL) -lfsdl -lpthread -L $(LIBVECT) -lvect -L $(LIBFMT) -lfmt -L $(LIBGNL) -lgnl -L $(LIBCL) -lcl -o $@ $^ $(OPENCL_F) $(SDL2_P) $(SDL2_F) $(SDL2_I) $(SDL2_TTF_I) $(SDL2_IMG_I)

temporary: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

$(DIR_O)/%.o: $(DIR_S)/%.c
	@$(CC) $(FLAGS) $(addprefix -I, $(HEADER)) -c -o $@ $<

norme:
	@make norme -C $(LIBFT)
	@make norme -C $(LIBVECT)
	@make norme -C $(LIBGNL)
	@make norme -C $(LIBCL)
	@make norme -C $(LIBFMT)
	@echo
	norminette ./$(HEADER)
	@echo
	norminette ./$(DIR_S)

clean:
	@rm -f $(OBJS)
	@make clean -C $(FSDL)
	@make clean -C $(LIBFT)
	@make clean -C $(LIBVECT)
	@make clean -C $(LIBGNL)
	@make clean -C $(LIBCL)
	@make clean -C $(LIBFMT)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(FSDL)
	@make fclean -C $(LIBFT)
	@make fclean -C $(LIBVECT)
	@make fclean -C $(LIBGNL)
	@make fclean -C $(LIBCL)
	@make fclean -C $(LIBFMT)

delimg: fclean
	@rm -rf $(IMG_DIR)

re: fclean
	@$(MAKE) all -j

.PHONY: all, temporary, norme, clean, fclean, re
