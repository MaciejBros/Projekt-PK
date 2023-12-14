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
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

public:

	Board(int height, int width) : m_width(width), m_height(height)
	{
		m_gameboard = new bool* [width];
			for (int i = 0; i < width; i++)
			{
				m_gameboard[i] = new bool[height];
			}

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					m_gameboard[i][j] = 0;
				}
			}
	}


	void set_random() const
	{
		std::mt19937 range(std::random_device{}());

		std::uniform_int_distribution<int> value(0, 1);

		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				m_gameboard[i][j] = value(range);
			}
		}
	}


	void print_gameboard() const
	{
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				std::cout << m_gameboard[i][j];
			}
			std::cout << std::endl;
		}
	}


	void add_cell(int x, int y)
	{
		if (index(x, y))
		{
			m_gameboard[x][y] = 1;
		}
		else
		{
			std::cout << "invalid cell index" << std::endl;
		}
	}


	void remove_cell(int x, int y)
	{
		if (index(x, y))
		{
			m_gameboard[x][y] = 0;
		}
		else
		{
			std::cout << "invalid cell index" << std::endl;
		}
	}


	~Board()
	{
		for (int i = 0; i < m_width; i++)
		{
			delete[] m_gameboard[i];
		}
		delete[] m_gameboard;
	}
};