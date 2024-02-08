
#include "board.h"
#include <iostream>
#include <random>
#include <QDebug>
#include "QDebug"


Board::Board(int liczbaWierszy, int liczbaKolumn) : m_numRows(liczbaWierszy), m_numCols(liczbaKolumn)
{
    allocate_gameboard(m_numCols, m_numRows);
    allocate_temp_gameboard(m_numCols, m_numRows);
    qDebug() << "LICZBA KOLUMN: " << m_numCols << "\tLICZBA WIERSZY: " << m_numRows << "\n";
}

Board::Board()
{
    m_numCols= 10;
    m_numRows = 10;
    allocate_gameboard(m_numCols, m_numRows);
    allocate_temp_gameboard(m_numCols, m_numRows);
}

Board::~Board()
{
    deallocate_gameboard();
    deallocate_temp_gameboad();
}

void Board::set_random() const
{
    std::mt19937 range(std::random_device{}());
    std::uniform_int_distribution<int> value(0, 1);
    for (int i = 0; i < m_numRows; i++)
    {
        for (int j = 0; j < m_numCols; j++)
            m_gameboard[i][j] = value(range);
    }
}

void Board::realocateBoard(int cols, int rows)
{
    deallocate_gameboard();
    deallocate_temp_gameboad();
    m_numCols = cols;
    m_numRows = rows;
    allocate_gameboard(cols, rows);
    allocate_temp_gameboard(cols, rows);
}

void Board::print_gameboard() const
{
    for (int i = 0; i < m_numRows; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < m_numCols; j++)
            std::cout << m_gameboard[i][j] << " ";

        std::cout << std::endl;
    }
}

void Board::print_temp_gameboard() const
{
    for (int i = 0; i < m_numRows; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < m_numCols; j++)
            std::cout << m_temp_gameboard[i][j] << " ";

        std::cout << std::endl;
    }
}



void Board::add_cell(int x, int y)
{
    if (check_index(x, y)) m_gameboard[x][y] = true;
    else std::cout << "Add_cell:\t invalid cell index\t x: " << x << " y: " << y << std::endl;
}

void Board::temp_add_cell(int x, int y)
{
    if (check_index(x, y))
    {
        m_temp_gameboard[x][y] = true;
    }
    else std::cout << "Add_temp_cell:\t invalid cell index\t x: " << x << " y: " << y << std::endl;
}

void Board::remove_cell(int x, int y)
{
    if (check_index(x, y)) m_gameboard[x][y] = false;
    else std::cout << "remove_cell:\t invalid cell index\t x: " << x << " y: " << y << std::endl;
}

void Board::temp_remove_cell(int x, int y)
{
    if (check_index(x, y)) m_temp_gameboard[x][y] = false;
    else std::cout << "remove_temp_cell:\t invalid cell index\t x: " << x << " y: " << y << std::endl;
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
            }
        }
        return counter_of_true_states;
    }
    return 0;
}

void Board::copy_GameBoard_to_Temp()
{
    for (int i = 0; i < m_numRows; i++)
    {
        for (int j = 0; j < m_numCols; j++)
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
    for (int i = 0; i < m_numRows; i++)
    {
        for (int j = 0; j < m_numCols; j++)
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
        for (int i = 0; i < m_numRows; i++)
        {
            for (int j = 0; j < m_numCols; j++)
                m_gameboard[i][j] = false;
        }
    }
    else if (sign == 'T')
    {
        for (int i = 0; i < m_numRows; i++)
        {
            for (int j = 0; j < m_numCols; j++)
                m_temp_gameboard[i][j] = false;
        }
    }
}



void Board::NextGeneration()
{
    copy_GameBoard_to_Temp();
    bool** active_states_detector = m_gameboard;
    for (int i = 0; i < m_numRows; i++)
    {
        for (int j = 0; j < m_numCols; j++)
        {
            if (active_states_detector[i][j] == true)
            {
                if (check_neighborhood(i, j) != 3 and check_neighborhood(i, j) != 2)
                    temp_remove_cell(i, j);
            }
            else if (active_states_detector[i][j] == false)
            {
                if (check_neighborhood(i, j) == 3)
                    temp_add_cell(i, j);
            }
        }
    }
    print_temp_gameboard();
    reset_array('G');
    copy_Temp_to_Gameboard();
    reset_array('T');
    std::cout << std::endl << "=====================" << std::endl << std::endl;
}


int Board::GetRows() { return m_numRows; };
int Board::GetCols() { return m_numCols; };
bool** Board::GetGameBoard() { return m_gameboard; };
