#ifndef BOARD_H
#define BOARD_H


#include "qdebug.h"
#include "qobject.h"

class Board : public QObject
{
    Q_OBJECT
private:

    int m_numRows;
    int m_numCols;
    bool** m_gameboard;
    bool** m_temp_gameboard;
    bool check_index(int x, int y)const
    {
        if (x >= 0 && x < m_numRows && y >= 0 && y < m_numCols) return true;
        else return false;
    }

    void allocate_gameboard(int numCols, int numRows)
    {
        //if (m_gameboard == nullptr)

            m_gameboard = new bool* [numRows];
            for (int i = 0; i < numRows; i++)
                m_gameboard[i] = new bool[numCols];


        for (int i = 0; i < m_numRows; i++)
        {
            for (int j = 0; j < m_numCols; j++)
                m_gameboard[i][j] = false;
        }
    }

    void allocate_temp_gameboard(int numCols, int numRows)
    {
        //if (m_temp_gameboard == nullptr)

            m_temp_gameboard = new bool* [numRows];
            for (int i = 0; i < numRows; i++)
                m_temp_gameboard[i] = new bool[numCols];


        for (int i = 0; i < m_numRows; i++)
        {
            for (int j = 0; j < m_numCols; j++)
                m_temp_gameboard[i][j] = false;
        }
    }

    void deallocate_gameboard()
    {
        //if (m_gameboard != nullptr)

            for (int i = 0; i < m_numRows; i++)
                delete[] m_gameboard[i];

            delete[] m_gameboard;
            qDebug() << "ZDEALOKOWANO\n";

    }

    void deallocate_temp_gameboad()
    {
        //if (m_temp_gameboard != nullptr)

            for (int i = 0; i < m_numRows; i++)
                delete[] m_temp_gameboard[i];

            delete[] m_temp_gameboard;
            qDebug() << "ZDEALOKOWANO TEMP\n";

    }
public:

    Board(int, int);
    Board();
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
    int GetRows();
    int GetCols();
    bool** GetGameBoard();
    void NextGeneration();
    void realocateBoard(int,int);
    ~Board();
};

#endif // BOARD_H
