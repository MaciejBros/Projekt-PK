#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
   //main to chyba narazie tylko do testów 
	Board gameboard(25, 25);
	cout << "print" << endl;
	gameboard.print_gameboard();

	cout << "\n\n\n\n\n\n";

	gameboard.set_random();
	cout << "random" << endl;
	gameboard.print_gameboard();

	gameboard.remove_cell(1, 0);
	gameboard.remove_cell(1, 1);
	gameboard.remove_cell(1, 2);
	gameboard.remove_cell(1, 3);
	gameboard.remove_cell(1, 4);
	gameboard.remove_cell(1, 5);
	gameboard.remove_cell(1, 6);
	gameboard.remove_cell(1, 7);
	gameboard.remove_cell(1, 8);
	gameboard.remove_cell(1, 9);
	gameboard.remove_cell(1, 10);
	gameboard.remove_cell(1, 11);
	gameboard.remove_cell(1, 12);
	gameboard.remove_cell(1, 13);
	gameboard.remove_cell(1, 14);
	gameboard.remove_cell(1, 15);
	gameboard.remove_cell(1, 16);
	gameboard.remove_cell(1, 17);
	gameboard.remove_cell(1, 18);
	gameboard.remove_cell(1, 19);
	gameboard.remove_cell(1, 20);
	gameboard.remove_cell(1, 21);
	gameboard.remove_cell(1, 22);
	gameboard.remove_cell(1, 23);
	gameboard.remove_cell(1, 24);

	cout << "\n\n\n\n\n\n";

	gameboard.add_cell(0, 24);
	gameboard.add_cell(0, 23);
	gameboard.add_cell(0, 22);
	gameboard.add_cell(0, 21);
	gameboard.add_cell(0, 20);
	gameboard.add_cell(0, 19);
	gameboard.add_cell(0, 18);
	gameboard.add_cell(0, 17);
	gameboard.add_cell(0, 16);
	gameboard.add_cell(0, 15);
	gameboard.add_cell(0, 14);
	gameboard.add_cell(0, 13);
	gameboard.add_cell(0, 12);
	gameboard.add_cell(0, 11);
	gameboard.add_cell(0, 10);
	gameboard.add_cell(0, 9);
	gameboard.add_cell(0, 8);
	gameboard.add_cell(0, 7);
	gameboard.add_cell(0, 6);
	gameboard.add_cell(0, 5);
	gameboard.add_cell(0, 4);
	gameboard.add_cell(0, 3);
	gameboard.add_cell(0, 2);
	gameboard.add_cell(0, 1);
	gameboard.add_cell(0, 0);

	cout << "add delete" << endl;
	gameboard.print_gameboard();




}