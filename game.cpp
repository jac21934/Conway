#include "game.h"



ConwayGame::ConwayGame(int winX, int winY, int cenX, int cenY){

		timeStep = 100;

		game_state = 1;
		boundaryConditions = 0;

		
		winWidth  = winX;
		winHeight = winY;

		centerX = cenX;
		centerY = cenY;

		int boardWidth = winWidth - 2;
		int boardHeight = winHeight - 2;
		
		int buffX = centerX + 1;   //(COLS - boardWidth)/2;
		int buffY = centerY + 1;   //(LINES - boardHeight)/2;

		
		b = Board(boardWidth, boardHeight, buffX, buffY);


		cursX = centerX + 1;
		cursY = centerY + 1;
		
		//Window Stuff

		initscr();
		raw();
		noecho();
		curs_set(0);
		nodelay(stdscr, TRUE);
		win = newwin(winHeight, winWidth, centerX, centerY);
		box(win, ACS_VLINE, ACS_HLINE);


		nonl();
		// keypad(win, TRUE);
		keypad(stdscr, TRUE);
		mousemask(ALL_MOUSE_EVENTS, NULL);

}


ConwayGame::~ConwayGame(){
		endwin();


}



void ConwayGame::debugInfo(){
		ofstream outFile;
		outFile.open("DEBUG_INFO", ios::out);

		outFile << "[WINDOW]" << endl
						<< "winWidth=" << winWidth << endl
						<< "winHeight=" << winHeight << endl
						<< "centerX=" << centerX << endl
						<< "centerY=" << centerY << endl
						<< "[BOARD]" << endl
						<< "xSize=" << b.get("xSize") << endl
						<< "ySize=" << b.get("ySize") << endl
						<< "xOffset=" << b.get("xOffset") << endl
						<< "yOffset=" << b.get("yOffset") << endl;

		outFile.close();

}

void ConwayGame::moveCursor(int x, int y){


		int bx = x - centerX - 1;
		int by = y - centerY - 1;

		b.move_cursor(bx, by);
		
		cursX = x;
		cursY = y;

}

void ConwayGame::setBoundaryConditions(int bP){
		boundaryConditions = bP;
}

void ConwayGame::processInput(wchar_t c){

		int cx = cursX;
		int cy = cursY;
		
		switch(c){

		case KEY_UP :
				if(cy > centerY + 1){
						cy--;
				}
				break;	

		case KEY_LEFT:
				if( cx > centerX + 1){
						cx--;
				}
				break;
		case KEY_RIGHT:
				if(cx < winWidth - 1){
						cx++;
				}
				break;
		case KEY_DOWN:
				if(cy < winHeight - 1){
						cy++;
				}
				break;

		case KEY_ENTER:
		case KEY_BREAK:
		case '\n':
		case '\r':
				int x = cx - centerX - 1;
				int y = cy - centerY - 1;
				b.set_piece(x, y, !b.get_piece(x, y));
				break;
				
				
		}


		if(cx != cursX || cy !=cursY){
				moveCursor(cx, cy);
		}

}

void ConwayGame::run(){
		wchar_t ch;

		std::chrono::time_point<std::chrono::system_clock> old_time = std::chrono::system_clock::now();
		std::chrono::time_point<std::chrono::system_clock> new_time;
		

			// wrefresh(win);
		while(true) {
				if( (ch = getch()) == CTR_KEY('q')){
						break;
				}
				else if(ch == ERR){
						
				}
				else{

						if(ch == ' '){
								
								// cursor_vis = cursor_vis ? 0 : 1;
								game_state = game_state ? 0 : 1;
								b.toggle_cursor();
								// curs_set(cursor_vis);

								moveCursor(cursX, cursY);
								// move(cursY, cursX);
								
								
						}

						else{

								if(!game_state){
										processInput(ch);

										// move(cursY, cursX);
																		
								}


						}
						// mvprintw(winHeight+1, 0, "Test: %c%s", ch, "   ");
						
				}

								
		


				if( game_state){
						new_time = std::chrono::system_clock::now();

						auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(new_time - old_time);

						if( milliseconds.count() > timeStep){
								step(); 

								old_time = new_time;
						}
						b.refresh_board();						

				}
				else{
						// curs_set(0);
						b.refresh_board();
						moveCursor(cursX, cursY);
						// curs_set(cursor_vis);

				}

				wrefresh(win);

			

			
				
		} 


}


void ConwayGame::step(){

		b.step();

}
