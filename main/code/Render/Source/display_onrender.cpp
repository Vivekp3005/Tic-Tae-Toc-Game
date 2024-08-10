#include"display.h"

void display::OnRender(){

    if(game->running == false){
        SDL_Texture * tex;
        SDL_Surface * ima;
        ima = SDL_LoadBMP("images/end.bmp"); 	
        tex = SDL_CreateTextureFromSurface(renderer, ima);
        SDL_Rect fillRect = {0 ,0 ,WIDTH,HEIGHT};
        SDL_RenderCopy(renderer,tex,NULL,&fillRect);
        SDL_RenderPresent(renderer);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
        SDL_RenderClear(renderer);
        game->render(renderer);
        SDL_RenderPresent(renderer);
    }
}

