#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <string>
static const char s_directions[] = { 'D', 'R', 'U', 'L'};
static const char s_response_file[] = "d:\\work\\runawayrobot\\Debug\\response.html";
static const char s_solution_file[] = "d:\\work\\runawayrobot\\Debug\\solution.txt";
//static const char s_response_file[] = "/home/clau/projects/response.html";
static const char s_clue[] = "FlashVars";
static const char s_badSolution[] = "boom";
static const int c_BadRoute = 9999;
std::string splitstr(std::string s, std::string delimiter, int index);
enum Directions {
  Down,
  Right,
  Up,
  Left
};
#endif // TOOLS_H
