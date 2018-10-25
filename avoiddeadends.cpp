#include "avoiddeadends.h"
#include <string>
#include "tools.h"

using namespace std;
AvoidDeadEnds::AvoidDeadEnds()
{
}

bool AvoidDeadEnds::ApplyAlgorithm()
{
    cout<<m_board;
    MarkDeadEnds();
    bool needProcessing = true;
    PostMarkDeadEnds();
    cout<<m_board;
    m_board->BackupData();
    for(int D = m_board->GetSolLengthMin(); D <= m_board->GetSolLengthMax(); D++)
    {
        for(int offsetRow = 0; offsetRow < D; offsetRow++)
        {
            int offsetCol = D - offsetRow;
            if((*m_board)(offsetRow, offsetCol) == '.')
            {
                m_board->RestoreData();
                m_board->MergeFromOffset(offsetRow, offsetCol, D);
                cout << m_board;
//                MarkDeadEnds();
               // PostMarkDeadEnds();
                //cout << m_board;
                if(Search(D) == true)
                {
                    return true;
                }
                else
                {
                    cerr << "No solution found, sol length = " << D <<", r = "<<offsetRow<<", col = "<<offsetCol<<endl;
                }
            }
        }
    }
    return false;
}

void AvoidDeadEnds::MarkDeadEnds()
{
    for(int row = 0; row < m_board->GetBoardX(); row++)
    {
        for(int col = 0; col < m_board->GetBoardY(); col++)
        {
            if((*m_board)(row,col) == '.' && IsRoadBlocked(row, col))
            {
                m_board->Mark(Position(row,col), 'D');
            }
        }
    }
}

bool AvoidDeadEnds::IsRoadBlocked(int x, int y)
{
    if(x==0 && y==0){return false;}
    if(y==0)
    {
        if((*m_board)(x-1, y)!='.')
        {
            return true;
        }
    }
    else
    {
        if(x==0)
        {
            if((*m_board)(x, y-1)!='.')
            {
                return true;
            }
         } else
        if((*m_board)(x, y-1)!='.' && (*m_board)(x-1, y)!='.')
        {
            return true;
        }
    }

    return false;
}

bool AvoidDeadEnds::PostMarkDeadEnds()
{
    bool isDirty = true;
    while(isDirty == true)
    {
        isDirty = false;
        for(int row = 0; row<m_board->GetBoardX();row++)
        {
            for(int col = 0; col<m_board->GetBoardY(); col++)
            {
                if((*m_board)(row,col) == '.' && IsPositionHidden(row, col))
                {
                    m_board->Mark(Position(row,col), 'D');
                    isDirty = true;
                }
            }
        }
    }
    return isDirty;
}

bool AvoidDeadEnds::IsPositionHidden(int x, int y)
{
    if(x == m_board->GetBoardX() - 1 || y == m_board->GetBoardY()-1)
    {
        return false;
    } else
    {
        if ((*m_board)(x, y+1)!='.' && (*m_board)(x+1, y)!='.')
        {
            return true;
        }
    }
    return false;
}

bool AvoidDeadEnds::Search(int pathLength)
{
    //    cout<<m_board;
    bool solutionFound = false;
    Directions direction = Right ;
    Tile* tile = m_board->CreateTile();

    //cout<<m_board;
    int zeroLenghtCount = 0;
    while(!solutionFound)
    {
        if(direction == Right)
        {
            tile->GoRight();
        }
        else
        {
            tile->GoDown();
        }
        if((tile->GetType() == Tile::Exit || (tile->GetType() == Tile::Empty && tile->GetPath().size() >= pathLength)))
        {
            if (VerifySolution(tile) == true)
            {
                m_solutionPath=tile->GetPath();
                cout<<"Solution found: "<<m_solutionPath<<endl;
                solutionFound = true;
                break;
            }
            else
            {
                solutionFound = false;
                break;
            }
        }
        else if (tile->GetType() == Tile::Empty)
        {
            direction = Right;
        }
        else if (tile->GetType() == Tile::Wall || tile->GetType() == Tile::DeadEnd)
        {
            tile->DropAllCheckedDirections();
            direction = Down;
        }
        if(tile->GetPath().size() == 0)
        {
            zeroLenghtCount++;
            if(zeroLenghtCount == 2)
            {
                break;
            }
        }
    }
    return solutionFound;
}

AvoidDeadEnds::~AvoidDeadEnds()
{

}
