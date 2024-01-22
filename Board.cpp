#include "Board.h"
#include "GameController.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>



Board::Board(int width, int height, int depth) : m_width(width), m_height(height), m_depth(depth)
{
	allocate_gameboard(width, height, depth);

}


Board::~Board()
{
	deallocate_gameboard();
}


bool Board::check_index(int x, int y) const
{
	return (x >= 0 && x < m_width&& y >= 0 && y < m_height);
}


void Board::allocate_gameboard(int width, int height, int depth)
{
	if (m_gameboard == nullptr)
	{
		m_gameboard = new bool** [width];
		for (int i = 0; i < width; i++)
		{
			m_gameboard[i] = new bool* [height];
			for (int j = 0; j < height; j++)
				m_gameboard[i][j] = new bool[depth];
		}
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < depth; k++)
				m_gameboard[i][j][k] = false;
		}
	}
}



void Board::deallocate_gameboard()
{
	if (m_gameboard != nullptr)
	{
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				delete[] m_gameboard[i][j];
			}
			delete[] m_gameboard[i];
		}
		delete[] m_gameboard;
	}
}


void Board::set_random() const
{
	std::mt19937 range(std::random_device{}());
	std::uniform_int_distribution<int> value(0, 1);
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			for (int k = 0; k < m_depth; k++)
				m_gameboard[i][j][k] = value(range);
		}
	}
}


void Board::print_gameboard(int depth) const
{
	if (depth == 0)
	{
		for (int k = 0; k <= 0; ++k)
		{
			for (int i = 0; i < m_width; ++i)
			{
				for (int j = 0; j < m_height; ++j)
				{
					std::cout << m_gameboard[i][j][k] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}
	else
	{
		for (int k = 1; k == 1; ++k)
		{
			for (int i = 0; i < m_width; ++i)
			{
				for (int j = 0; j < m_height; ++j)
				{
					std::cout << m_gameboard[i][j][k] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}
}


void Board::add_cell(int x, int y, int z)
{
	if (check_index(x, y))
		m_gameboard[x][y][z] = true;
	else
		std::cout << "invalid cell index" << std::endl;
}

void Board::remove_cell(int x, int y, int z)
{
	if (check_index(x, y))
		m_gameboard[x][y][z] = false;
	else
		std::cout << "invalid cell index" << std::endl;
}


int Board::check_neighborhood(int x, int y, int z)
{
	if (check_index(x, y) == true)
	{
		int counter_of_true_states = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (check_index(x + i, y + j) == true)
				{
					if (m_gameboard[x + i][y + j][z] == true && (j || i) != 0)
						counter_of_true_states++;
				}
				else
					continue;
			}
		}
		return counter_of_true_states;
	}
}


void Board::reset_array(char sign)
{
	if (sign == 'F')
	{
		for (int k = 0; k <= 0; k++)
		{
			for (int i = 0; i < m_width; i++)
			{
				for (int j = 0; j < m_height; j++)
				{

					m_gameboard[i][j][k] = false;
				}
			}
		}
	}
	else if(sign == 'S')
	{
		for (int k = 0; k == 1; k++)
		{
			for (int i = 0; i < m_width; i++)
			{
				for (int j = 0; j < m_height; j++)
				{

					m_gameboard[i][j][k] = false;
				}
			}
		}
	}
}


int Board::GetHeight() { return m_height; };
int Board::GetWidth() { return m_width; };
bool*** Board::GetGameBoard() { return m_gameboard; };