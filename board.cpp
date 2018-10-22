#include <stdlib.h>
#include <algorithm>
#include "board.h"
#include "tools.h"
using namespace std;

Board::Board():
    m_insMin(0),
    m_insMax(0),
    m_boardX(0),
    m_boardY(0),
    m_level(0)
{
}

void Board::GetInfoFromString(string input_str)
{
    if(input_str.empty())
    {
        return;
    }
    m_data = splitstr(splitstr(input_str, "&", 0), "=", 1);
    string insMax = splitstr(splitstr(input_str, "&", 1), "=",1);
    string insMin = splitstr(splitstr(input_str, "&", 2), "=",1);
    string boardX = splitstr(splitstr(input_str, "&", 3), "=",1);
    string boardY = splitstr(splitstr(input_str, "&", 4), "=",1);
    string level = splitstr(splitstr(input_str, "&", 5), "=",1);

    m_insMax = atoi(insMax.c_str());
    m_insMin = atoi(insMin.c_str());
    m_boardX = atoi(boardX.c_str());
    m_boardY = atoi(boardY.c_str());
    m_level = atoi(level.c_str());
}

char Board::operator()(int line, int col)
{
    if(line < m_boardY && col < m_boardX)
    {
        return m_data.at(line * m_boardY + col);
    }
    return '\0';
}

Board *Board::GetSubBoard(int originLine, int originColumn, int lines, int columns)
{
    Board* board = new Board();
    for(int i = originLine; i<lines; i++)
    {
        board->m_data.append(m_data.substr(i*columns+originColumn, columns-originColumn));
    }
    return board;
}

Board Board::operator+(const Board &board) const
{
    Board boardRes;
    boardRes.m_data = m_data;
    for(size_t i = 0; i<board.m_data.size(); i++)
    {
        if(board.m_data.at(i) == 'X')
        {
            boardRes.m_data.at(i) = 'X';
        }
    }
    return boardRes;
}

void Board::MergeFromOffset(int offsetRow, int offsetCol, int wide)
{
    for (int i = offsetRow; i <= wide; i++)
    {
        for (int j = offsetCol; j <= wide; j++)
        {
            if ((*this)(i, j) == 'X')
            {
                Mark(Position(i - offsetRow, j - offsetCol), 'D');
            }
        }
    }
}

Tile *Board::CreateTile()
{
    return new Tile(this);
}

ostream& operator<< (ostream &out, Board& board)
{
    out<< "Board info"<<endl;
    out<< "----------"<<endl;
    out<< "Level: "<<board.m_level<<endl;
    out<< "Size: " <<board.m_boardX<<" x "<<board.m_boardY<<endl;
    out<< "Solution min length: "<<board.m_insMin<<endl;
    out<< "Solution max length: "<<board.m_insMax<<endl;
    out<< "Data: "<<endl;
    for(int i = 0; i< board.m_boardY; i++)
    {
        for(int j = 0; j<board.m_boardX;j++)
        {
            out<<board(i,j);
        }
        out<<endl;
    }
    out<<flush;
    return out;
}
ostream& operator<< (ostream &out, Board* board)
{
    out<< *board;
    return out;
}

void Board::ResetAllVisited(Position position)
{
    std::replace(m_data.begin()+position.AsIndex(m_boardX), m_data.end(), 'V', '.');
}

void Board::Mark(Position position, char c)
{
    string replacer(1, c);
    if (position.Line < m_boardY && position.Column < m_boardX) {
        m_data.replace(position.Line * m_boardX + position.Column, 1, replacer);
    } else {
        cerr<<"Mark: Internal error"<<endl;
    }
}

void Board::MarkVisited(Position position)
{
    Mark(position, 'V');
}
