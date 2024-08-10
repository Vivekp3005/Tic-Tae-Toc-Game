#include"display.h"

void display::OnEvent(SDL_Event* event){
    
    while(SDL_PollEvent(event)){
        switch (event->type){
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:  
                game->key_down(&(event->key));
                break;
                
            default:
                break;
        }
    }
    

}

