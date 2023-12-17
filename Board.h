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
	bool** m_temp_gameboard;
	bool check_index(int x, int y)const
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) return true;
		else return false;
	}

	void allocate_gameboard(int width, int height)
	{
		if (m_gameboard == nullptr)
		{
			m_gameboard = new bool* [width];
			for (int i = 0; i < width; i++)
				m_gameboard[i] = new bool[height];
		}

		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
				m_gameboard[i][j] = false;
		}
	}

	void allocate_temp_gameboard(int width, int height)
	{
		if (m_temp_gameboard == nullptr)
		{
			m_temp_gameboard = new bool* [width];
			for (int i = 0; i < width; i++)
				m_temp_gameboard[i] = new bool[height];
		}

		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
				m_temp_gameboard[i][j] = false;
		}
	}

	void deallocate_gameboard()
	{
		if (m_gameboard != nullptr)
		{
			for (int i = 0; i < m_width; i++)
				delete[] m_gameboard[i];

			delete[] m_gameboard;
		}
	}

	void deallocate_temp_gameboad()
	{
		if (m_temp_gameboard != nullptr)
		{
			for (int i = 0; i < m_width; i++)
				delete[] m_temp_gameboard[i];

			delete[] m_temp_gameboard;
		}
	}
public:

	Board(int, int);
	void set_random() const;
	void print_gameboard() const;
	void print_temp_gameboard() const;
	void add_cell(int, int);
	void temp_add_cell(int, int);
	void remove_cell(int, int);
	void temp_remove_cell(int, int);
	void copy_GameBoard_to_Temp();
	void copy_Temp_to_Gameboard();
	void reset_array(char);
	int check_neighborhood(int, int);
	int GetHeight();
	int GetWidth();
	bool** GetGameBoard();
	~Board();
};