#ifndef BOARD_H
#define BOARD_H

#include <curses.h>
#include <assert.h>     /* assert */
#include <vector>
#include <string>

using namespace std;

class Board{

public:
		Board(int x, int y, int xOff, int yOff);
		Board();
		~Board();

		void set_piece(int x, int y, bool c);
		void refresh_board();
		void print();
		void info();

		void move_cursor(int x, int y);
		
		bool get_piece(int x, int y);
		
		string get(string var);

		void toggle_cursor();

		bool check_cell(int x, int y, bool orig);

		void step();
		
private:
		int xSize;
		int ySize;
		int xOffset;
		int yOffset;
		vector< vector<bool> > bvec;

		wchar_t empty_char;
		wchar_t fill_char;

		bool display_cursor;
		int cX;
		int cY;


		int boundaryCondition;
		
};


#endif
