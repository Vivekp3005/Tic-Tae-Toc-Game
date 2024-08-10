#include"Bodies.h"
#include<vector>
#include"SDL.h"

#define RESET_TIME 200

class Game{
    public:
    Game(SDL_Renderer* renderer);
    void initialize();
    void generateObs();
    void key_down(SDL_KeyboardEvent* event );
    void render(SDL_Renderer* renderer);
    bool turnX;
    Bodies* board[9];
    int board2[9];
    bool running;
    int possibleWinner;
    int corners[4];
    int sides[4];
    Bodies* screen;

    private:
    SDL_Renderer* renderer;
    double timer = 0;
};