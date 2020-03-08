

SDL_INCS = -I./frameworks/SDL2.framework/Versions/A/Headers \
		     -I./frameworks/SDL2_image.framework/Versions/A/Headers \
			 -I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
			 -I./frameworks/SDL2_mixer.framework/Versions/A/Headers
FRAMEWORKS  = -F./frameworks \
				-rpath ./frameworks \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer
gcc foo.c - I (эти имена) (эти имена)