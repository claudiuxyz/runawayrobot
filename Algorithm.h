#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <string>
#include <iostream>
#include "board.h"
class Algorithm
{
public:
    const int c_extraMoves = 0;
    enum Types
    {
        LazzyBacktracking,
        Backtracking,
        AvoidDeadEnds
    };
    virtual bool ApplyAlgorithm() = 0;
    virtual ~Algorithm();
    void SetBoard(Board* board) { m_board = board; }
    std::string GetSolution() const { return m_solutionPath; }
    bool VerifySolution(const Tile * tileToVerify);
    bool VerifySubSolution(std::string s);
    bool VerifySolution2(std::string s);
    void DrawSolution();
protected:
    Board* m_board;
    std::string m_solutionPath;
};

#endif // ALGORITHM_H
