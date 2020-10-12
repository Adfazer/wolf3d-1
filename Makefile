
#	gcc $(FLAGS) $(SRC_PATH) $(INCS) $(SDL_INCS) $(FRAMEWORKS) -o $(NAME)




# WE RESPECT NORM! FFFFFF
# 'ALL SOURCE FILES YOU NEED TO COMPILE YOUR PROJECT
#  MUST BE EXPLICITLY NAMED IN YOUR MAKEFILE'
#
#ALL_C_ASM = $(wildcard $(SRCDIR_ASM)/*.c)
#ALL_C_CW = $(wildcard $(SRCDIR_CW)/*.c)

#printf '        %s \\\n' *.c


ALL_C = main.c \
		map.c \
		error.c \
		sdl.c \
		init.c \
		debug_print.c \
		aux.c \
		load_textures.c \
		distance.c \
		pseudo_3d.c \
		draw.c \
		music.c \
		render_fps.c

SRCDIR = ./src
OBJDIR = ./objs
ALL_OBJ = $(ALL_C:%.c=%.o)
OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = wolf3d

INCLUDES = ./includes/wolf3d.h ./includes/const.h


LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = -g -ffast-math -O3 #-Wall -Wextra -Werror -ffast-math -O3 

SDL_INCS =	-I./frameworks/SDL2.framework/Versions/A/Headers \
			-I./frameworks/SDL2_image.framework/Versions/A/Headers \
			-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \
			-I./frameworks/SDL2_ttf.framework/Versions/A/Headers
			 
FRAMEWORKS  = -F./frameworks \
				-rpath ./frameworks \
				-framework SDL2 \
				-framework SDL2_ttf \
				-framework SDL2_image \
				-framework SDL2_mixer

all: $(LIBFT) $(OBJDIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $@ $(SDL_INCS) $(FRAMEWORKS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIR)
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/includes -c $< -o $@ 

$(OBJDIR):
	/bin/mkdir -p $(OBJDIR)

$(LIBFT): lib

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(COMP_LIB) fclean

re: fclean all

.PHONY: lib clean fclean all re
