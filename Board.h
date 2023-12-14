#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

class Board
{
private:

	int m_height;
	int m_width;
	bool** m_gameboard;

	bool index(int x, int y)const
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) return 1;
		else return 0;
	}

public:

	Board(int, int);
	void set_random() const;
	void print_gameboard() const;
	void add_cell(int, int);
	void remove_cell(int, int);
	int check_neighborhood(int, int);
	~Board();
};