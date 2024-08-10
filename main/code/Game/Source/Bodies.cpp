#include"Bodies.h"
#include"defs.h"
#include<math.h>
#include<iostream>

Bodies::Bodies(double u, double v, double w, double h,int type,SDL_Renderer* renderer ): x(u),y(v),wid(w),hei(h), type(type) {
    
    if(type==1){
        image = SDL_LoadBMP("images/X.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    else if(type==2){
        image = SDL_LoadBMP("images/O.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    else{
        image = SDL_LoadBMP("images/board.bmp"); 	
        texture = SDL_CreateTextureFromSurface(renderer, image);
    }
    
}

Bodies::~Bodies(){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}


void Bodies::display(SDL_Renderer* renderer){
    SDL_Rect fillRect = {x ,y ,wid,hei};
    SDL_RenderCopy(renderer,texture,NULL,&fillRect); 
}