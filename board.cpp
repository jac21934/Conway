#include "board.h"

Board::Board(int x, int y, int xOff, int yOff){
		display_cursor = 0;
		boundaryCondition = 1;

		
		xSize = x;
		ySize = y;
		xOffset = xOff;
		yOffset = yOff;

		cX = 0;
		cY = 0;

		
		bvec = vector< vector<bool> >(xSize, vector<bool>(ySize, 0));

		assert(bvec.size() == unsigned(xSize));
		for(int i = 0; i < xSize; i++){
				assert(bvec[i].size() == unsigned(ySize));
		}

}

Board::Board(){
		


}

Board::~Board(){


}


void Board::move_cursor(int x, int y){
		cX = x;
		cY = y;

}

void Board::toggle_cursor(){
		display_cursor = !display_cursor;
}

void Board::info(){
		
		printf("xSize: %d\n", xSize);
		printf("ySize: %d\n", ySize);				
		printf("xOffset: %d\n", xOffset);
		printf("yOffset: %d\n", yOffset);
}

bool Board::get_piece(int x, int y){
		return bvec[x][y];

}

string Board::get(string var){

		if( var == "xSize")  return to_string(xSize);
		else if( var == "ySize") return to_string(ySize);
		else if( var == "xOffset")return to_string(xOffset);
		else if( var == "yOffset")return to_string(xOffset);


		return "";
}

void Board::print(){
		for(int i = 0; i < xSize; i++){
				for(int j = 0; j < ySize;j++){
						printf("%c ", bvec[i][j] ? '+': ' ');
				}
				printf("\n");
		}

}

void Board::set_piece(int x, int y, bool c){
		if( x < xSize && y < ySize){
				bvec[x][y] = c;
		}
		
}

void Board::refresh_board(){

		for(int i = 0; i < xSize; i++){
				for(int j = 0; j < ySize; j++){
						int x = i + xOffset;
						int y = j + yOffset;
						if( display_cursor 
								&& (i == cX && j == cY)
								){
								mvaddch(y, x, bvec[i][j] ? '+' | A_STANDOUT  : '.' | A_STANDOUT );
						}
						else{
								mvaddch(y, x, bvec[i][j] ? '+' : '.' ); //sends character in bvec to screen
						}
				}
		}
}


void Board::step(){

		vector< vector<bool> >buffvec(xSize, vector<bool>(ySize, 0));
		
		for(int i = 0; i < xSize; i++){
				for(int j = 0; j < ySize; j++){

						buffvec[i][j] = check_cell(i, j, bvec[i][j]);
												
				}
		}

		bvec = buffvec;

}


bool Board::check_cell(int x, int y, bool orig){
		int live = 0;
				

		if(boundaryCondition == 0){ //hard walls

				//orthoganol directions
				if(x > 0){
						live += bvec[x - 1][y];
				}

				if(x <  xSize - 1){
						live += bvec[x + 1][y];
				}
				if( y > 0 ){
						live += bvec[x][y-1];
				}
				if(y < ySize - 1){
						live += bvec[x][y+1];
				}

				//diagonal directions
		
				if( (x > 0) && (y > 0)){
						live += bvec[x - 1][y - 1];
				}

				if( (x > 0) && (y < ySize - 1)){
						live += bvec[x - 1][y + 1];
				
				}

				if( (x < xSize - 1) && (y < ySize - 1)){
						live += bvec[x + 1][y + 1];
				}

				if( (x < xSize - 1) && (y > 0)){
						live += bvec[x + 1][y - 1];
				}
		}

		else if(boundaryCondition == 1){ //periodic boundary

				int xp =  (x + 1) % xSize;
				int yp =  (y + 1) % ySize;

				int xm = ( x-1 < 0) ? xSize - 1 : x - 1;
				int ym = ( y-1 < 0) ? ySize - 1 : y - 1;
				
				//orthoganol directions
				live += bvec[xm][y];
				live += bvec[xp][y];
				live += bvec[x][yp];
				live += bvec[x][ym];
				
				
				//diagonal directions
				live += bvec[xm][ym];
				live += bvec[xm][yp];
				live += bvec[xp][yp];
				live += bvec[xp][ym];
						

		}

		
		//checking if cell lives of dies
		if( orig){
				
				if(live < 2){   // live cell with < 2 neighbors dies
						return 0;
				}
				
				if( live > 3){ //live cell with > 3 neighbors dies
						return 0;
				}

				if( live == 2 || live == 3){
						return 1;
				}
				
		}

		else{

				if( live == 3){ //dead cell with 3 neighbors lives
						return 1;
				}
				else{
						return 0;
				}

		}

}
