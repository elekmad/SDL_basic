#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define SPEED_RATE 1

SDL_Surface *surface;
SDL_Window *window;
int x=0, xspeed=0, y=0, yspeed=0;
SDL_Event event;

void one_iter(void)
{
    if(x + xspeed < 640 && x + xspeed >= 0)
        x += xspeed;
    if(y + yspeed < 480 && y + yspeed >= 0)
        y += yspeed;
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));//Clear the screen
    SDL_Rect pos = {x,  y, 10, 10};
    if(SDL_FillRect(surface, &pos, SDL_MapRGB(surface->format, 255, 255, 255)) == -1)
    {
        printf("Can't fill rect : %s\n", SDL_GetError());
        return;
    }
    // Check for messages
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                SDL_Quit();
    	    return;
                break;
    	case SDL_KEYUP:
    	case SDL_KEYDOWN:
    		printf("keydown %d\n", event.key.keysym.sym);
    		switch(event.key.keysym.sym)
    		{
                        case SDLK_DOWN:
                            yspeed = (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                            break;
                        case SDLK_UP:
                            yspeed = (event.type == SDL_KEYDOWN ? -SPEED_RATE : 0);
                            break;
                        case SDLK_RIGHT:
                            xspeed = (event.type == SDL_KEYDOWN ? SPEED_RATE : 0);
                            break;
                        case SDLK_LEFT:
                            xspeed = (event.type == SDL_KEYDOWN ? -SPEED_RATE : 0);
                            break;
                        case SDLK_ESCAPE:
                            SDL_Quit();
                            return;
                            break;
    		}
    	        printf("xspeed %d yspeed %d \n", xspeed, yspeed);
    	        break;
        }
    }
    //Update the display
    SDL_UpdateWindowSurface(window);
 
}

int main( int argc, char *argv[ ] )
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    atexit( SDL_Quit );
    window = SDL_CreateWindow("Ma fenêtre de jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0 );
    surface = SDL_GetWindowSurface(window);

    if( surface == NULL )
    {
        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }   
    // Main loop
#ifdef __EMSCRIPTEN__
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(one_iter, 60, 1);
#else
    while (1)
    {
        one_iter();
        // Delay to keep frame rate constant (using SDL)
        SDL_Delay(time_to_next_frame());
    }
#endif

    SDL_Quit();

    return EXIT_SUCCESS;
}
