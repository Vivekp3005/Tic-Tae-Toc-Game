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

    possibleWinner;
    corners[0] = 0;
    corners[1] = 2;
    corners[2] = 6;
    corners[3] = 8;
    sides[0] = 1;
    sides[1] = 3;
    sides[2] = 5;
    sides[3] = 7;

    //Add Screen
    Bodies* B1 = new Bodies(0,0,WIDTH,HEIGHT,3,renderer);
    screen = B1;

    turnX = true;
}
#define compareBoxes(box1, box2, box3) ((board[box1] == board[box2]) && (board[box2] == board[box3]) && (board[box1] != 0)) //Checkes if three items are the same, and makes sure they're not 0's.
#define numberToLetter(x) ((x > 0) ? (x == 1) ? 'X' : 'O' : ' ') //Takes the number and turns it into the letter or space.

int getWinner(int board[9]) {
	//Finds winner of game, if there is no winner, returns 0.
	int winner = 0;
	for (int x = 0; x < 3; x++) {
		if (compareBoxes(3*x, 3*x+1, 3*x+2)) { //Chekcs rows.
			winner = board[3*x];
			break;
		} else if (compareBoxes(x, x+3, x+6)) { //Checks columns.
			winner = board[x];
			break;

		} else if (compareBoxes(2*x, 4, 8-2*x) && (x < 2)) { //Checks diagonals. Doesn't check if x == 2.
			winner = board[4];
			break;
		}
	}
	return winner;
}
bool gameOver(int board[9]){
	//Checks if game is over, and announces who won, or if it was a tie.
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

int willWin(int board[9], int player) {
	//Checks if a given player could win in the next plank.
	for (int x = 0; x < 9; x++) {
		int tempBoard[9];
		memcpy(tempBoard, board, 36);
		if (board[x] > 0) continue;
		tempBoard[x] = player;
		if(getWinner(tempBoard) == player) return x;
	}
	return -1;
}

int exceptionalCase(int board[9]) {
	//Finds bords that are exceptions to how the algorithm works.
	int cases[2][9] = {{1,0,0,0,2,0,0,0,1}, {0,1,0,1,2,0,0,0,0}}; //Boards that don't work with algorithm.
	int answers[2][4] = {{3,3,3,3}, {2,8,6,0}};
	int rotatedBoard[9] = {6,3,0,7,4,1,8,5,2};
	int newBoard[9];
	int tempBoard[9];
	for(int x = 0; x < 9; x++) {
		newBoard[x] = board[x];
	}
	for (int caseIndex = 0; caseIndex < 2; caseIndex++) {
		for(int rotation = 0; rotation < 4; rotation++) {
			for (int x = 0; x < 9; x++) 
				tempBoard[x] = newBoard[x];
			
			int match = 0;
			//Rotates board so it works with different versions of the same board.
			for (int box = 0; box < 9; box++) {
				newBoard[box] = tempBoard[rotatedBoard[box]];
			}

			for (int x = 0; x < 9; x++) {
				if (newBoard[x] == cases[caseIndex][x]) match++;
				else break;
			}
			if (match == 9) return answers[caseIndex][rotation];
		}
	}
	return -1;
}

int getSpace(int board[9], int spaces[4]) {
	//Gets a random corner or side that's not taken.
	bool isSpaceEmpty = false;
	int y;
	for (int x = 0; x < 4; x++) {
		if (board[spaces[x]] == 0) {
			isSpaceEmpty = true;
			break;
		}
	}
	if (isSpaceEmpty) {
		do {
			y = rand() % 4;
		} while (board[spaces[y]] != 0);
		return spaces[y];
	}
	return -1;
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

void Game::generateObs(){
    // Add Obstacle
    if(!turnX) {
        if (gameOver(board2) > 0) {
			running = false;
            outputBoard(board2);
		}

        //Player O decides which move they'll do.
	    bool good = false;
	    for (int x = 2; x > 0; x--){
	    	possibleWinner = willWin(board2, x);
	    	if (possibleWinner != -1) {
                fillBoard(possibleWinner, board, renderer);
	    		board2[possibleWinner] = 2;
	    		good = true;
	    		break;
	    	}
	    }
	    if (good);
	    else if (board2[4] == 0) {
            fillBoard(4,board, renderer);
            board2[4] = 2; //Middle.
        }
	    else if (exceptionalCase(board2) > -1) {
            fillBoard(exceptionalCase(board2),board, renderer); 
            board2[exceptionalCase(board2)] = 2; //Exception board2s.
        }
	    else if (getSpace(board2, corners) != -1) {
            fillBoard(getSpace(board2, corners), board, renderer);
            board2[getSpace(board2, corners)] = 2; //Corners
        }
	    else {
            fillBoard(getSpace(board2, sides), board, renderer);
            board2[getSpace(board2, sides)] = 2; //Sides
        }
    
        turnX = true;
    
        if(gameOver(board2)) {
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
                }
                break;

            case SDL_SCANCODE_2: 
                if(board[1] == nullptr) {
                    Bodies* body = new Bodies(165,90,50,50,1,renderer);
                    board[1] = body;
                    board2[1] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_3:
                if(board[2] == nullptr) {
                    Bodies* body = new Bodies(280,90,50,50,1,renderer);
                    board[2] = body;
                    board2[2] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_4: 
                if(board[3] == nullptr) {
                    Bodies* body = new Bodies(40,165,50,50,1,renderer);
                    board[3] = body;
                    board2[3] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_5:
                if(board[4] == nullptr) {
                    Bodies* body = new Bodies(165,165,50,50,1,renderer);
                    board[4] = body;
                    board2[4] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_6: 
                if(board[5] == nullptr) {
                    Bodies* body = new Bodies(280,165,50,50,1,renderer);
                    board[5] = body;
                    board2[5] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_7:
                if(board[6] == nullptr) {
                    Bodies* body = new Bodies(40,235,50,50,1,renderer);
                    board[6] = body;
                    board2[6] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_8: 
                if(board[7] == nullptr) {
                    Bodies* body = new Bodies(165,235,50,50,1,renderer);
                    board[7] = body;
                    board2[7] = 1;
                    turnX = false;
                }
                break;

            case SDL_SCANCODE_9: 
                if(board[8] == nullptr) {
                    Bodies* body = new Bodies(280,235,50,50,1,renderer);
                    board[8] = body;
                    board2[8] = 1;
                    turnX = false;
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