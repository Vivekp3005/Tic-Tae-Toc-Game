#include"Game.h"
#include"Bodies.h"
#include"defs.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;

Game::Game(SDL_Renderer* rendereer){
    running = true;
    timer= 0;
    renderer = rendereer;
    SDL_Texture * text;
    SDL_Surface * imag;
    imag = SDL_LoadBMP("images/onetap.game.tictactoe.sc0.2024-07-24-11-29-01.bmp"); 	
    text = SDL_CreateTextureFromSurface(renderer, imag);
    SDL_Rect fillRect = {0 ,0 ,WIDTH,HEIGHT};
    SDL_RenderCopy(renderer,text,NULL,&fillRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyTexture(text);
    SDL_FreeSurface(imag);
    initialize();
}

void Game::initialize(){
    //Clear the list of bodies
    for(int i=0;i<9;i++) board[i] = nullptr;
    for(int i=0;i<9;i++) board2[i] = 0;

    //Add Screen
    Bodies* B1 = new Bodies(0,0,WIDTH,HEIGHT,3,renderer);
    screen = B1;

    turnX = true;
    moveIndex = 0;
}
#define compareBoxes(box1, box2, box3) ((board[box1] == board[box2]) && (board[box2] == board[box3]) && (board[box1] != 0))
#define numberToLetter(x) ((x > 0) ? (x == 1) ? 'X' : 'O' : ' ')

int getWinner(int board[9]) {
	int winner = 0;
	for (int x = 0; x < 3; x++) {
		if (compareBoxes(3*x, 3*x+1, 3*x+2)) {
			winner = board[3*x];
			break;
		} else if (compareBoxes(x, x+3, x+6)) {
			winner = board[x];
			break;

		} else if (compareBoxes(2*x, 4, 8-2*x) && (x < 2)) {
			winner = board[4];
			break;
		}
	}
	return winner;
}
bool gameOverFinal(int board[9]){
	int winner = getWinner(board);
	if (winner > 0) {
		cout << numberToLetter(winner) << " wins!"<< endl;
		return true;
	} 
	for (int x = 0; x < 9; x++) {
		if (board[x] == 0) return false;
	}
	cout << "Tie!\n\n";
	return true;
}

void outputBoard(int board[9]) {
	for(int line = 0; line < 3; line++){
		for (int box = 0; box < 3; box++) {
			cout << numberToLetter(board[3*line+box]) << ((box < 2) ? '|' : '\n');
		}
		cout << ((line < 2) ? "-----\n" : "\n");
	}
}

void fillBoard(int possibleWinner, Bodies* board[], SDL_Renderer* renderer) { 
    if(possibleWinner == 0) {
        Bodies* body = new Bodies(40,90,50,50,2,renderer);
        board[0] = body;
    }
    else if(possibleWinner == 1) {
        Bodies* body = new Bodies(165,90,50,50,2,renderer);
        board[1] = body;
    }
    else if(possibleWinner == 2) {
        Bodies* body = new Bodies(280,90,50,50,2,renderer);
        board[2] = body;
    }
    else if(possibleWinner == 3) {
        Bodies* body = new Bodies(40,165,50,50,2,renderer);
        board[3] = body;
    }
    else if(possibleWinner == 4) {
        Bodies* body = new Bodies(165,165,50,50,2,renderer);
        board[4] = body;
    }
    else if(possibleWinner == 5) {
        Bodies* body = new Bodies(280,165,50,50,2,renderer);
        board[5] = body;
    }
    else if(possibleWinner == 6) {
        Bodies* body = new Bodies(40,235,50,50,2,renderer);
        board[6] = body;
    }
    else if(possibleWinner == 7) {
        Bodies* body = new Bodies(165,235,50,50,2,renderer);
        board[7] = body;
    }
    else if(possibleWinner == 8) {
        Bodies* body = new Bodies(280,235,50,50,2,renderer);
        board[8] = body;
    }

}

bool rowCrossed(int board[9]) { 
	for (int i=0; i<3; i++) { 
		if (board[3*i] == board[(3*i)+1] && 
			board[(3*i)+1] == board[(3*i)+2] && 
			board[3*i] != 0) 
			return (true); 
	} 
	return(false); 
} 

bool columnCrossed(int board[9]) { 
	for (int i=0; i<3; i++) { 
		if (board[i] == board[3+i] && 
			board[3+i] == board[6+i] && 
			board[i] != 0) 
			return (true); 
	} 
	return(false); 
} 

bool diagonalCrossed(int board[9]) { 
	if (board[0] == board[4] && 
		board[4] == board[8] && 
		board[0] != 0) 
		return(true); 
		
	if (board[2] == board[4] && 
		board[4] == board[6] && 
		board[2] != 0) 
		return(true); 

	return(false); 
} 

bool gameOver(int board[9]) { 
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) ); 
}

int minimax(int board[9], int depth, bool isAI){
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true) {
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else {
		if(depth < 9) {
			if(isAI == true) {
				bestScore = -999;
				for(int i=0; i<3; i++) {
					for(int j=0; j<3; j++) {
						if (board[(3*i)+j] == 0) {
							board[(3*i)+j] = 2;
							score = minimax(board, depth + 1, false);
							board[(3*i)+j] = 0;
							if(score > bestScore) {
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else {
				bestScore = 999;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (board[(3*i)+j] == 0) {
							board[(3*i)+j] = 1;
							score = minimax(board, depth + 1, true);
							board[(3*i)+j] = 0;
							if (score < bestScore) {
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

int bestMove(int board[9], int moveIndex){
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[(3*i) + j] == 0) {
				board[(3*i) + j] = 2;
				score = minimax(board, moveIndex+1, false);
				board[(3*i) + j] = 0;
				if(score > bestScore) {
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

void Game::generateObs(){
    // Add Obstacle
    if(!turnX) {
        if (gameOverFinal(board2) > 0) {
			running = false;
            outputBoard(board2);
		}

        int n = bestMove(board2, moveIndex);
        fillBoard(n, board, renderer);
		board2[n] = 2; 
		turnX = true;
        moveIndex++;
    
        if(gameOverFinal(board2)) {
            running = false;
            outputBoard(board2);
        }

    }
}

void Game::key_down(SDL_KeyboardEvent* event ){

    if(event->repeat==0){
        // Press any key to restart game
        if(!running){ 
            running = true;
            initialize();
        }
        switch (event->keysym.scancode){
            case SDL_SCANCODE_1:
                if(board[0] == nullptr) {
                    Bodies* body = new Bodies(40,90,50,50,1,renderer);
                    board[0] = body;
                    board2[0] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_2: 
                if(board[1] == nullptr) {
                    Bodies* body = new Bodies(165,90,50,50,1,renderer);
                    board[1] = body;
                    board2[1] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_3:
                if(board[2] == nullptr) {
                    Bodies* body = new Bodies(280,90,50,50,1,renderer);
                    board[2] = body;
                    board2[2] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_4: 
                if(board[3] == nullptr) {
                    Bodies* body = new Bodies(40,165,50,50,1,renderer);
                    board[3] = body;
                    board2[3] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_5:
                if(board[4] == nullptr) {
                    Bodies* body = new Bodies(165,165,50,50,1,renderer);
                    board[4] = body;
                    board2[4] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_6: 
                if(board[5] == nullptr) {
                    Bodies* body = new Bodies(280,165,50,50,1,renderer);
                    board[5] = body;
                    board2[5] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_7:
                if(board[6] == nullptr) {
                    Bodies* body = new Bodies(40,235,50,50,1,renderer);
                    board[6] = body;
                    board2[6] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_8: 
                if(board[7] == nullptr) {
                    Bodies* body = new Bodies(165,235,50,50,1,renderer);
                    board[7] = body;
                    board2[7] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            case SDL_SCANCODE_9: 
                if(board[8] == nullptr) {
                    Bodies* body = new Bodies(280,235,50,50,1,renderer);
                    board[8] = body;
                    board2[8] = 1;
                    turnX = false;
                    moveIndex++;
                }
                break;

            default:
                break;
            
        }
    }
}

//render
void Game::render(SDL_Renderer* renderer){
    if(running){
        screen->display(renderer);
        for(int i=0;i<9;i++) {
            if(board[i]!=nullptr) {
                board[i]->display(renderer);
            }
        }
    }
}