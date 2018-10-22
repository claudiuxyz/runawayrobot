
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <list>
#include <chrono>
#include "gameop.h"
#include "tools.h"
#include "lazzybacktracking.h"
#include "backtracking.h"
#include "avoiddeadends.h"
using namespace std;


GameOp::GameOp():
    m_board(0),
    m_algorithm(0)
{
    m_board = new Board();
}

GameOp::~GameOp()
{
    if(m_algorithm != 0)
    {
        delete(m_algorithm);
    }
    if(m_board != 0)
    {
        delete(m_board);
    }
}

void GameOp::SetAlgorithm(Algorithm::Types algorithm)
{
    if(m_algorithm != 0)
    {
        delete(m_algorithm);
    }

    switch(algorithm)
    {
    case Algorithm::LazzyBacktracking:
            m_algorithm = new LazzyBacktracking();
            break;
    case Algorithm::Backtracking:
            m_algorithm = new Backtracking();
            break;
    case Algorithm::AvoidDeadEnds:
            m_algorithm = new AvoidDeadEnds();
            break;
    default:
        cerr<<"Algorithm not found!";
    }
}

bool GameOp::FindSolution()
{
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();

    if(m_algorithm != 0)
    {
        auto t0 = Time::now();
        auto result = m_algorithm->ApplyAlgorithm();
        auto t1 = Time::now();
        fsec fs = t1 - t0;
        ms d = std::chrono::duration_cast<ms>(fs);
//       std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(fs);
//       cout<<"Solved in "<<min.count()<<" [min]"<<endl;
        cout <<"Processing took "<< fs.count() << "s\n";
//       std::cout << d.count() << "ms\n";
        return result;
    }
    return false;
}

bool GameOp::GetBoardInfoFromFile()
{
    string s;
    string line;
    ifstream myfile (s_response_file);
    size_t pos = 0;
    bool ret = false;
    if (! myfile.is_open())
    {
        cout<< "Couldn't open " << s_response_file<<" !"<<endl;
        exit(1);
    }
    while ( getline (myfile,line) && ret == false )
    {

        if((pos = line.find(s_clue)) != std::string::npos && pos == 0){
            s = line.substr(strlen(s_clue) + 1, line.length() - 1);
            ret = true;
        }
    }
    myfile.close();
    if ( ret == false )
    {
        cout<<"Strange answer got from server, solution not OK?"<<endl;
    }
    else
    {
        m_board->GetInfoFromString(s);
        if(m_algorithm != 0)
        {
            m_algorithm->SetBoard(m_board);
        }
        cout<<"Attempting to solve level "<<m_board->GetLevel()<<endl;
    }
    return ret;
}
