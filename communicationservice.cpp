#include "communicationservice.h"
#include "tools.h"

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <list>

using namespace std;
CommunicationService::CommunicationService()
{
}

void CommunicationService::SendSolution(){
    std::string command = "wget -q -R .gif -R .jpg -R .png -i ";
    m_solution.append("http://www.hacker.org/runaway/index.php?name=claudiuxyz&password=cb312959&path=");
    m_solution.append( m_solutionPath );
    //m_solution.append("");
    ofstream solutionFile;
    solutionFile.open(s_solution_file, ios::in | ios::trunc);
    solutionFile << m_solution;
    solutionFile.close();

    command.append(s_solution_file);
    command.append(" -O ");
    command.append( s_response_file );
    system((const char*)command.c_str());
}

CommunicationService::ResponseType CommunicationService::EvaluateAnswer()
{
    string line;
    ifstream myfile (s_response_file);
    size_t pos = 0;
    ResponseType ret = ServerError;
    if (! myfile.is_open())
    {
        cout<< "Couldn't open " << s_response_file<<" !"<<endl;
        return ret;
    }
    while ( getline (myfile,line) && ret == ServerError )
    {

        if((pos = line.find(s_clue)) != std::string::npos && pos == 0){
            cout<<"OK"<<endl;
            ret = SolutionOK;
        }
        if((pos = line.find(s_badSolution)) != std::string::npos && pos == 0){
            cout<<"NOK"<<endl;
            ret = SolutionNOK;
        }
    }
    myfile.close();
    return ret;
}

void CommunicationService::SendSolution(string s){
    m_solutionPath = s;
    SendSolution();
}

bool CommunicationService::GetStartupSolution()
{
    m_solution.clear();
    ifstream myfile (s_response_file);
    if (!myfile.is_open())
    {
        cerr<<"Response from serve file not found or already opened!"<<endl;
        myfile.close();
        return false;
    }
    std::string command = "wget -q -R .gif -R .jpg -R .png  -O ";

    command.append( s_response_file );
    command.append( " ");
    command.append("\"http://www.hacker.org/runaway/?name=claudiuxyz&password=cb312959\"");
    //cout<<"Getting startup page: "<<flush;
    system((const char*)command.c_str());
    int retries = 3;
    ResponseType response = ServerError;
    while ( response == ServerError && retries > 0)
    {
        response = EvaluateAnswer();
        //cout<<". "<<flush;
        system((const char*)command.c_str());
        retries --;
    }
    if (response != SolutionOK)
    {
        cerr<<"Startup solution could not be retrieved correctly."<<endl<<flush;
        return false;
    }
    else
    {
        return true;
    }
}
