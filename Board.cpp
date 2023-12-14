#include "Board.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>



Board::Board(int height, int width) : m_width(width), m_height(height)
{
	m_gameboard = new bool* [width];
	for (int i = 0; i < width; i++)
		m_gameboard[i] = new bool[height];

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
			m_gameboard[i][j] = false;
	}
}

Board::~Board()
{
	for (int i = 0; i < m_width; i++)
		delete[] m_gameboard[i];

	delete[] m_gameboard;
}

void Board::set_random() const
{
	std::mt19937 range(std::random_device{}());
	std::uniform_int_distribution<int> value(0, 1);
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
				m_gameboard[i][j] = value(range);
		}
}


void Board::print_gameboard() const
{
	for (int i = 0; i < m_width; i++)
	{
		std::cout << "\t";
		for (int j = 0; j < m_height; j++)
			std::cout << m_gameboard[i][j] << " ";
		
		std::cout << std::endl;
	}
}


void Board::add_cell(int x, int y)
{
	if (index(x, y)) m_gameboard[x][y] = true;
	else std::cout << "invalid cell index" << std::endl;
}


void Board::remove_cell(int x, int y)
{
	if (index(x, y)) m_gameboard[x][y] = false;
	else std::cout << "invalid cell index" << std::endl;
}

int Board::check_neighborhood(int x, int y)
{
	int counter_of_true_states = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
			if (m_gameboard[x + i][y + j] == true and (j or i) != 0) counter_of_true_states++;
	}
	std::cout << counter_of_true_states;
	return counter_of_true_states;
}

