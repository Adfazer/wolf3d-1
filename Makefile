INCS = -I./includes

FLAGS = -Wall -Wextra -Werror

NAME = 1

SDL_INCS = -I./frameworks/SDL2.framework/Versions/A/Headers

		     #-I./frameworks/SDL2_image.framework/Versions/A/Headers \
			 #-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
			 #-I./frameworks/SDL2_mixer.framework/Versions/A/Headers
FRAMEWORKS  = -F./frameworks \
				-rpath ./frameworks \
				-framework SDL2 # -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer
all:
	gcc $(FLAGS) src/1.c $(INCS) $(SDL_INCS) $(FRAMEWORKS) -o $(NAME)