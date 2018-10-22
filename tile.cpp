#include "tile.h"

using namespace std;
Tile::Tile(Board* board):
    m_face('.')
{
    m_board = board;
}

void Tile::SetPath(string path)
{
    m_path = path;
    PathToPosition();
    m_face = (*m_board)(m_position.Line, m_position.Column);
}

void Tile::SetPosition(int row, int col)
{
    m_position.Line = 0;
    m_position.Column = 0;
    m_path.clear();
    for(int i = 0; i<row;i++)
    {
        GoDown();
    }
    for(int i = 0; i<col;i++)
    {
        GoRight();
    }
}

bool Tile::Next(char direction)
{
    if(direction == 'R')
    {
        return GoRight();
    }

    if(direction == 'D')
    {
        return GoDown();
    }
    return false;
}

bool Tile::GoRight()
{
    if(m_position.Column < m_board->GetBoardY())
    {
        m_path += 'R';
        m_position.Column++;
        m_face = (*m_board)(m_position.Line, m_position.Column);
        return true;
    } else
    {
        return false;
    }
}

bool Tile::GoDown()
{
    if(m_position.Line < m_board->GetBoardX())
    {
        m_path += 'D';
        m_position.Line++;
        m_face = (*m_board)(m_position.Line, m_position.Column);
        return true;
    }
    else
    {
        return false;
    }
}

bool Tile::DropLastDirection()
{
    if (m_path.size()!=0)
    {
        m_path = m_path.substr(0, m_path.size()-1);
        SetPath(m_path);
        return true;
    }
    else
    {
        return false;
    }
}

bool Tile::DropAllCheckedDirections()
{
    if(m_path.back() == 'D')
    {
        while(m_path.size()>=1 && m_path.back() == 'D')
        {

            m_path = m_path.substr(0, m_path.size()-1);
        }
    }

    if(m_path.size()>=1){
        m_path = m_path.substr(0, m_path.size()-1);
    }


//    while(m_path.size()>=2 && m_path.back() == 'D')
//    {

//        m_path = m_path.substr(0, m_path.size()-2);
//    }
    SetPath(m_path);
    return true;
}

void Tile::PathToPosition()
{
    m_position.Line = 0;
    m_position.Column = 0;
    for (unsigned int pos = 0; pos < m_path.size(); pos++){
        if(m_path[pos] == 'R') {
            m_position.Column++;
        } else {
            m_position.Line++;
        }
    }
}

Tile::TileType Tile::GetType()
{
    if(m_position.Line >= m_board->GetBoardY() || m_position.Column >= m_board->GetBoardX())
    {
        return Exit;
    }
    if(m_face == '.')
    {
//        if(m_position.Line + 1 >= m_board->GetBoardY() || m_position.Column + 1 >= m_board->GetBoardX())
//        {
//            return Exit;
//        }
//        else
//        {
            return Empty;
//        }
    }
    if(m_face == 'X')
    {
        return Wall;
    }
    if(m_face == 'V')
    {
//        if(m_position.Line + 1 >= m_board->GetBoardY() || m_position.Column + 1 >= m_board->GetBoardX())
//        {
//            return Exit;
//        }
//        else
//        {
            return Visited;
//        }
    }
    if(m_face == 'D')
    {
        return DeadEnd;
    }
    return Wall;
}

void Tile::SetType(Tile::TileType type)
{
    if(type == DeadEnd)
    {
    }
    if(type == Visited)
    {
        m_board->MarkVisited(m_position);
    }
}
