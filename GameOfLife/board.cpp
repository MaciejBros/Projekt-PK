
#include "board.h"
#include <iostream>
#include <random>
#include <QDebug>
#include "QDebug"


Board::Board(int height, int width) : m_height(height), m_width(width)
{
    allocate_gameboard(width, height);
    allocate_temp_gameboard(width, height);
}

Board::Board()
{
    m_height = 17;
    m_width = 19;
    allocate_gameboard(m_width, m_height);
    allocate_temp_gameboard(m_width, m_height);
}

Board::~Board()
{
    deallocate_gameboard();
    deallocate_temp_gameboad();
}

void Board::set_random()
{
    int rng;
    std::mt19937 range(std::random_device{}());
    std::uniform_int_distribution<int> value(0, 1);
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            m_gameboard[i][j] = value(range);
            rng = value(range);
            emit boardUpdated(i,j,rng);
        }
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

void Board::print_temp_gameboard() const
{
    for (int i = 0; i < m_width; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < m_height; j++)
            std::cout << m_temp_gameboard[i][j] << " ";

        std::cout << std::endl;
    }
}



void Board::add_cell(int x, int y)
{
    if (check_index(x, y)) m_gameboard[x][y] = true;
    else std::cout << "invalid cell index" << std::endl;
}

void Board::temp_add_cell(int x, int y)
{
    if (check_index(x, y)) m_temp_gameboard[x][y] = true;
    else std::cout << "invalid cell index" << std::endl;
}

void Board::remove_cell(int x, int y)
{
    if (check_index(x, y)) m_gameboard[x][y] = false;
    else std::cout << "invalid cell index" << std::endl;
}

void Board::temp_remove_cell(int x, int y)
{
    if (check_index(x, y)) m_temp_gameboard[x][y] = false;
    else std::cout << "invalid cell index" << std::endl;
}



int Board::check_neighborhood(int x, int y)
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
                    if (m_gameboard[x + i][y + j] == true and (j or i) != 0) counter_of_true_states++;
                }
                else
                    continue;
            }
        }
        return counter_of_true_states;
    }
    return NULL;
}

void Board::copy_GameBoard_to_Temp()
{
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            if (m_gameboard[i][j] == true)
                temp_add_cell(i, j);
            else
                temp_remove_cell(i, j);
        }
    }
}

void Board::copy_Temp_to_Gameboard()
{
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            if (m_temp_gameboard[i][j] == true)
                add_cell(i, j);
            else
                remove_cell(i, j);
        }
    }
}

void Board::reset_array(char sign = 'G')
{
    if (sign == 'G')
    {
        for (int i = 0; i < m_width; i++)
        {
            for (int j = 0; j < m_height; j++)
                m_gameboard[i][j] = false;
        }
    }
    else if (sign == 'T')
    {
        for (int i = 0; i < m_width; i++)
        {
            for (int j = 0; j < m_height; j++)
                m_temp_gameboard[i][j] = false;
        }
    }
}

int Board::GetHeight() { return m_height; };
int Board::GetWidth() { return m_width; };
bool** Board::GetGameBoard() { return m_gameboard; };
