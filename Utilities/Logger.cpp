#include  "Logger.h"

void Log(std::string str )
{
    //  std::time_t result = std::time(nullptr);      
    std::ofstream log("./logfile.txt", std::ios_base::app | std::ios_base::out);
   // log << std::asctime(std::localtime(&result)) << ": "<< str << std::endl;
   log << str;
}

