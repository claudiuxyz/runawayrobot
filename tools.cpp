#include "tools.h"
using namespace std;



string splitstr(string s, string delimiter, int index){
    size_t pos = 0;
    std::string token;
    int tokenIdx = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(index == tokenIdx){ return token;}
        s.erase(0, pos + delimiter.length());
        tokenIdx++;
    }
    return s;
}
