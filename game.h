#ifndef GAME_H
#define GAME_H

#include "board.h"


#include <ncurses.h>
#include <fstream>
#include <chrono>

#define  CTR_KEY(k) ((k) & 0x1f)

class ConwayGame{

public:
		
		void run();
		void step();

		int timeStep;

		
		void debugInfo();

		void processInput(int c);
		void moveCursor(int x, int y);

		void setBoundaryConditions(int bP);
		
		ConwayGame(int winX, int winY, int cenX, int cenY);
		ConwayGame(int winX, int winY, int cenX, int cenY, int bP);
		
		~ConwayGame();

private:

		WINDOW* win;

		int cursor_vis;

		int game_state;
		
		Board b;
		
		int winWidth;
		int winHeight;
		
		int centerX;
		int centerY;


		int cursX;
		int cursY;

		int boundaryConditions;

};



#endif
