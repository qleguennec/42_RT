# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/07 22:13:23 by bsouchet          #+#    #+#              #
#*   Updated: 2017/02/15 16:22:46 by qle-guen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

C			= clang

NAME		= rt

FLAGS		= -Wall -Wextra -Werror -g

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


SOURCES		= \
			cl_build/cl_main_krl_exec.c \
			cl_build/cl_main_krl_init.c \
			cl_build/cl_main_krl_update_buffers.c \
			cl_build/cl_main_krl_update_camera.c \
			cl_build/cpy_cam.c \
			cl_build/cpy_lgt.c \
			cl_build/cpy_obj.c \
			cl_build/cl_copy_image_buffer.c \
			gui/draw_elements.c \
			gui/draw_info_and_state.c \
			gui/draw_outliner.c \
			gui/draw_panels.c \
			gui/draw_scene_parameters.c \
			gui/export_config.c \
			gui/init_structure.c \
			gui/save_to_png.c \
			handle/buttons.c \
			handle/elements.c \
			handle/errors.c \
			handle/events.c \
			handle/info_bar.c \
			handle/keyboard.c \
			handle/linked_lists.c \
			handle/mouse.c \
			handle/outliner.c \
			handle/scene_parameters.c \
			handle/special_mode.c \
			handle/threads.c \
			main.c \
			misc/free_elements.c \
			misc/verbose_mode.c \
			parser/add_elements.c \
			parser/add_elements_parameters.c \
			parser/check_elements.c \
			parser/check_tags.c \
			parser/clear_buffer.c \
			parser/get_informations.c \
			parser/get_numbers.c \
			parser/get_type_elements.c \
			parser/init_global_stuctures.c \
			parser/set_elements_parameters.c \
			renderer/init_renderer.c \
			renderer/scene_init_rendering.c \
			renderer/start_renderer.c \
			test/cl_test_krl.c \

SUB_FOLDERS	= test gui handle misc parser renderer cl_build

BUILD_DIR	= $(addprefix $(DIR_O)/,$(SUB_FOLDERS))

SRCS		= $(addprefix $(DIR_S)/,$(SOURCES))

OBJS		= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

opti:
	@$(MAKE) all

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

r: $(OBJS)
	@$(CC) $(FLAGS) -L $(LIBFT) -lft -L $(FSDL) -lfsdl -lpthread -L $(LIBVECT) -lvect -L $(LIBFMT) -lfmt -L $(LIBGNL) -lgnl -L $(LIBCL) -lcl -o $(NAME) $^ $(OPENCL_F) $(SDL2_P) $(SDL2_F) $(SDL2_I) $(SDL2_TTF_I) $(SDL2_IMG_I)

.PHONY: all, temporary, norme, clean, fclean, re
