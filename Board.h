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
    int m_depth;
    bool*** m_gameboard;

    bool check_index(int x, int y)const;
    void allocate_gameboard(int width, int height, int depth);
    void deallocate_gameboard();

public:
    Board(int, int, int);
    ~Board();

    void set_random() const;
    void print_gameboard(int) const;
    void add_cell(int, int, int);
    void remove_cell(int, int, int);
    int check_neighborhood(int, int, int);
    void copy_GameBoard_to_Temp();
    void copy_Temp_to_Gameboard();
    void reset_array(char);
    int GetHeight();
    int GetWidth();
    bool*** GetGameBoard();
};