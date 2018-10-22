#include <string>
#include "backtracking.h"
#include "tools.h"

using namespace std;
Backtracking::Backtracking()
{

}

bool Backtracking::ApplyAlgorithm()
{
    bool solutionFound = false;
    cout << m_board;
    Directions direction = Right ;
    Tile* tile = m_board->CreateTile();
    //cout<<m_board;
    int zeroLenghtCount = 0;
    unsigned long long counter = 0;
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
        if(tile->GetType() == Tile::Exit || (tile->GetType() == Tile::Empty && tile->GetPath().size() >= m_board->GetSolLengthMax() + c_extraMoves))
        {
            counter++;
            //if(counter % 10000 == 0)
            //cout<<counter<<": "<<tile->GetPath()<<endl;
            //cout<<tile->GetPath()<<endl;

            if (VerifySolution(tile->GetPath()) == true)
            {
                cout<<"Solution found: "<<m_solutionPath<<endl;
                solutionFound = true;
                break;
            }
            else
            {
                tile->DropAllCheckedDirections();
                direction = Down;
            }
        }
        else if (tile->GetType() == Tile::Empty)
        {
            direction = Right;
        }
        else if (tile->GetType() == Tile::Wall)
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
    if(!solutionFound)
    {
        cout<<"No solution found!"<<endl;
    }
    return solutionFound;
}

Backtracking::~Backtracking()
{

}
