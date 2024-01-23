#include "gamecontroller.h"
#include "board.h"
#include <thread>
#include <chrono>

GameController::GameController(Board& brd):m_GameBoard(brd) {};

GameController::~GameController() {};


void GameController::SetState(int x, int y, char sign = '+')
{
    if (sign == '+') m_GameBoard.add_cell(x, y);
    else if (sign == '-') m_GameBoard.remove_cell(x, y);
}

void GameController::StartGame()
{
    while (true)
    {
        NextGeneration();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void GameController::StopGame()
{

}

void GameController::NextGeneration()
{
    m_GameBoard.copy_GameBoard_to_Temp();
    bool** active_states_detector = m_GameBoard.GetGameBoard();
    for (int i = 0; i < m_GameBoard.GetHeight(); i++)
    {
        for (int j = 0; j < m_GameBoard.GetWidth(); j++)
        {
            if (active_states_detector[i][j] == true)
            {
                if (m_GameBoard.check_neighborhood(i, j) != 3 and m_GameBoard.check_neighborhood(i, j) != 2)
                    m_GameBoard.temp_remove_cell(i, j);
            }
            else if (active_states_detector[i][j] == false)
            {
                if (m_GameBoard.check_neighborhood(i, j) == 3)
                    m_GameBoard.temp_add_cell(i, j);
            }
        }
    }
    m_GameBoard.print_temp_gameboard();
    m_GameBoard.reset_array('G');
    m_GameBoard.copy_Temp_to_Gameboard();
    m_GameBoard.reset_array('T');
    //std::cout << std::endl << "=====================" << std::endl << std::endl;
}


