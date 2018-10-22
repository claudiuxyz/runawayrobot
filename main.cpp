#include "position.h"
#include "gameop.h"
#include "communicationservice.h"
#include "Algorithm.h"

using namespace std;

int main(int argc, char** argv)
{
    GameOp g;
    g.SetAlgorithm(Algorithm::AvoidDeadEnds);
    CommunicationService c;

    bool allLevelResolved = false;
    while (allLevelResolved == false)
    {
        if (c.GetStartupSolution() == false)
        {
            return(0);
        }
        if (g.GetBoardInfoFromFile() != true)
        {
            return(0);
        }
        bool solutionFound = g.FindSolution();
        if(solutionFound)
        {
            //return(0);
            c.SendSolution(g.GetSolution());
            if(c.EvaluateAnswer() == CommunicationService::SolutionNOK)
            {
                cout<<"Level "<<g.GetCurrentLevel()<<" could not be solved"<<endl;
                g.PrintBoard();
                break;
            }
        }
        else
        {
            cout<<"Could not solve level "<< g.GetCurrentLevel()<<". Abort!"<<endl;
            break;
        }
    }
    return(0);
}
