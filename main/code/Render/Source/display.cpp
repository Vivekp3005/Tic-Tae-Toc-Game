#include "display.h"
 
display::display() {
    window = NULL;
    renderer  = NULL;
    game = NULL;
    running = true;
}
 
int display::OnExecute() {
    if(OnInit()==false){
        return -1;
    }
    SDL_Event Event;

    while(running){
        
        OnEvent(&Event);
        OnLoop();
        OnRender();
        SDL_Delay(16);
    }

    OnCleanup();

    return 0;
}
 
