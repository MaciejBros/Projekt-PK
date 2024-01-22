#include "Board.h"
//#include "GameController.h"
#include <iostream>

using namespace std;

int main()
{
	Board gameboard(5, 5, 2);

	//zwykly print
	//gameboard.print_gameboard();


	//ustawianie z lapy
	gameboard.add_cell(0, 0, 0);
	gameboard.add_cell(1, 1, 0);
	gameboard.add_cell(2, 2, 0);
	gameboard.add_cell(3, 3, 0);
	gameboard.add_cell(4, 4, 0);

	gameboard.print_gameboard(0);


	cout << gameboard.check_neighborhood(2, 2, 0) << "\n\n";



	//resecik
	gameboard.reset_array('F');

	gameboard.print_gameboard(0);



	gameboard.add_cell(0, 0, 1);
	gameboard.add_cell(1, 1, 1);
	gameboard.add_cell(2, 2, 1);
	gameboard.add_cell(3, 3, 1);
	gameboard.add_cell(4, 4, 1);
	gameboard.add_cell(0, 4, 1);
	gameboard.add_cell(1, 3, 1);
	gameboard.add_cell(3, 1, 1);
	gameboard.add_cell(4, 0, 1);

	gameboard.print_gameboard(1);

	cout << gameboard.check_neighborhood(2, 2, 1) << "\n\n";



	//resecik
	gameboard.reset_array('S');

	gameboard.print_gameboard(0);
	


}