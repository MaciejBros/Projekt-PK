#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#pragma once

class Board;

class GameController
{
private:
    Board &m_GameBoard;
    bool m_start = false;
    bool m_stop = false;
    bool m_NextGeneration = false;
public:
    GameController(Board&);
    ~GameController();
    void SetState(int, int, char);
    void StartGame();
    void StopGame();

    void NextGeneration();

};

#endif // GAMECONTROLLER_H
