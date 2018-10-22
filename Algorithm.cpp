#include "Algorithm.h"

using namespace std;

Algorithm::~Algorithm()
{

}

bool Algorithm::VerifySolution(std::string s)
{
    bool solutionFound = false;
    Tile* tile = m_board->CreateTile();

    tile->SetPath(s);
    bool shouldSearch = true;
    int idx = 0;
    while (shouldSearch == true)
    {
        if (!tile->Next(s.at(idx)))
        {
            cerr << "Next: Internal Error!" << endl;
            break;
        }
        if (tile->GetType() == Tile::Wall)
        {
            shouldSearch = false;
            solutionFound = false;

        } 
        else if (tile->GetType() == Tile::Exit)
        {
            shouldSearch = false;
            solutionFound = true;
        }
        idx++;
        if (idx > s.size() - 1)
        {
            idx = 0;
        }
    }
    if (solutionFound)
    {
        m_solutionPath.assign(s);
        DrawSolution();
        cout << m_board;
    }
    delete(tile);
    return solutionFound;
}

bool Algorithm::VerifySubSolution(string s)
{
//    if (VerifySolution2(s) == false)
//    {
//        //cerr<<"!";
//        return false;
//    }
    //cerr<<endl;
    bool solutionFound = true;
    //cerr<<"Verify solution "<< s<<endl;
    //cerr<<".";
    Tile* tile = m_board->CreateTile();

    for (int i = m_board->GetSolLengthMin(); i<= m_board->GetSolLengthMax(); i++)
    {
        string subPath = s.substr(0, i);

        tile->SetPath(subPath);
        bool shouldSearch = true;
        int idx = 0;
        while (shouldSearch == true)
        {
            if(!tile->Next(subPath.at(idx)))
            {
                cerr<<"Next: Internal Error!"<<endl;
                break;
            }
            if(tile->GetType() == Tile::Wall)
            {
                shouldSearch = false;
                solutionFound = false;

            }
            if(tile->GetType() == Tile::Exit )
            {
                shouldSearch = false;
                solutionFound = true;
                m_solutionPath = subPath;
            }
            idx++;
            if(idx > subPath.size() - 1)
            {
                idx = 0;
            }
        }
        if(solutionFound)
        {
            DrawSolution();
            cout<<m_board;
            break;
        }
    }
    delete(tile);
    return solutionFound;
}

bool Algorithm::VerifySolution2(string str)
{
    if(m_board->GetLevel() < 30)
    {
        return VerifySolution(str);
    }
    string start = str.substr(0, c_extraMoves);
    size_t pos = str.find(start, m_board->GetSolLengthMin()-1);
    if (pos == std::string::npos)
    {
        return false;
    } else if (pos == m_board->GetSolLengthMax() - 1)
    {
        //m_solutionPath = str.substr(0, pos);
        return true;
    }
    size_t lenOfCandidate = c_extraMoves + m_board->GetSolLengthMax() - pos;
    start = str.substr (0, lenOfCandidate);
    pos = str.find(start, m_board->GetSolLengthMin()-1);
    if (pos == std::string::npos)
    {
        return false;
    } else
    {
        //m_solutionPath = str.substr(0, pos-1);
        return true;
    }
}

void Algorithm::DrawSolution()
{
    if(m_solutionPath.size() == 0){return;}
     Tile* tile = m_board->CreateTile();
     bool shouldStop = false;
     while(!shouldStop)
     {
         for(auto i = 0; i < m_solutionPath.size(); i++)
         {
             if(m_solutionPath.at(i)=='R')
              {  tile->GoRight();}
              else
              {   tile->GoDown();}

              if(tile->GetType() == Tile::Empty)
              {
                  tile->SetType(Tile::Visited);
              } else if (tile->GetType() == Tile::Exit){
                shouldStop = true;
                break;
              } else {
                  cerr<<"Internal error. Bad solution?: "<<tile->GetPath()<<endl;
                  shouldStop = true;
                  break;
              }
         }
     }
}
