#include "../includes/1.h"
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_START_POS_X = 100;
const int SCREEN_START_POS_Y = 100;

int main (void) {
    
   


    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        printf("error\n");
        return 1;
    }    
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Hello, SDL 2!", 100, 
                                100, SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);
    if (!window)
        printf("window error\n");

    SDL_Surface* screen_surface = NULL;

   
    
    if (window == NULL) {
        return 1;
    }

    screen_surface = SDL_GetWindowSurface(window);
    
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0, 255, 0));
        SDL_UpdateWindowSurface(window);    

        //SDL_Delay(5000);
         bool isquit = false;
SDL_Event event;
while (!isquit) {
    if (SDL_PollEvent( & event)) {
        if (event.type == SDL_QUIT) {
            isquit = true;
        }
    }
}

        SDL_DestroyWindow(window);

        SDL_Quit();

    return 0;
}
