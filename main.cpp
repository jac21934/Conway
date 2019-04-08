#include <curses.h>
#include <assert.h>     /* assert */
#include <vector>
#include "board.h"
#include "game.h"




int main(){


		ConwayGame G(70, 30, 1, 1);

		// G.debugInfo();
		
		G.run();
		
		

		return 0;

}
