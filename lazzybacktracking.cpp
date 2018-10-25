#include "lazzybacktracking.h"
#include <list>
#include <string>
#include "tile.h"
#include "tools.h"

using namespace std;
LazzyBacktracking::LazzyBacktracking()
{
}

bool LazzyBacktracking::ApplyAlgorithm()
{
    bool solutionFound = false;
    Directions direction = Right ;
    string currentPath;
    string candidate;
    std::list<std::string> m_candidates;
    m_candidates.push_back("");
    Tile* tile = m_board->CreateTile();
    while(!solutionFound || m_candidates.size() != 0)
    {
        candidate = currentPath + (direction == Right ? "R":"D");
        tile->SetPath(candidate);
        if(tile->GetType() == Tile::Exit || (tile->GetType() == Tile::Empty && candidate.size() >= m_board->GetSolLengthMax()))
        {
            if (VerifySolution(tile) == true)
            {
                cout<<"Solution found: "<<m_solutionPath<<endl;
                solutionFound = true;
                break;
            }
            else
            {
                //tile->SetType(Tile::Visited);
                //cerr<<m_board;
                m_candidates.pop_back();
                if(m_candidates.size()!=0)
                {
                    currentPath = m_candidates.back();
                    m_board->ResetAllVisited(tile->GetPosition());
                }
                else
                {
                    break;
                }
                direction = Down;
            }
        } else
        if (tile->GetType() == Tile::Empty)
        {
            direction = Right;
            m_candidates.push_back(candidate);
            currentPath = candidate;
            tile->SetPath(currentPath);
            tile->SetType(Tile::Visited);
            //cerr<<m_board;
        } else
        if (tile->GetType() == Tile::Wall || tile->GetType() == Tile::Visited)
        {
            if(direction == Down)
            {
                m_candidates.pop_back();
                if(m_candidates.size()!=0)
                {

                    currentPath = m_candidates.back();
                    m_board->ResetAllVisited(tile->GetPosition());
                }
                else
                {
                    break;
                }
            }
            else
            {

            }
            direction = Down;
        }
    }
    if(!solutionFound)
    {
        cout<<"No solution found!"<<endl;
    }
    return solutionFound;
}
