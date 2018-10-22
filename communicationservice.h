#ifndef COMMUNICATIONSERVICE_H
#define COMMUNICATIONSERVICE_H
#include <string>

class CommunicationService
{
public:
    enum ResponseType{
        SolutionNOK,
        SolutionOK,
        ServerError
    };
    CommunicationService();
    ResponseType EvaluateAnswer();

    void SendSolution();
    void SendSolution(std::string s);
    bool GetStartupSolution();
private:
    std::string m_solution;
    std::string m_solutionPath;
};

#endif // COMMUNICATIONSERVICE_H
