#ifndef _BODIES_H_
#define _BODIES_H_

#include"SDL.h"

class Bodies{
    public:
    Bodies(double u, double v, double w, double h, int type, SDL_Renderer* renderer);
    ~Bodies();
    void display(SDL_Renderer* renderer);

    double x,y;
    double wid,hei;
    
    private:
    SDL_Texture * texture;
    SDL_Surface * image;
    int type;
};

#endif