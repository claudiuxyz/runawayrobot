#ifndef GAMEOP_H
#define GAMEOP_H

#include <string>
#include <iostream>
#include <list>
#include "board.h"
#include "tile.h"
#include "Algorithm.h"

class GameOp{
public:

    GameOp();
    ~GameOp();
    void SetAlgorithm(Algorithm::Types algorithm);
    bool FindSolution();
    bool VerifySolution(std::string s);
    bool GetBoardInfoFromFile();
    std::string GetSolution() const { return m_algorithm->GetSolution(); }
    int GetCurrentLevel() const { return m_board->GetLevel(); }
    void PrintBoard() const { std::cout<<m_board; }

private:
    Board* m_board;
    Algorithm* m_algorithm;
    std::string m_solution;
    std::string m_solutionPath;
};

#endif // GAMEOP_H
