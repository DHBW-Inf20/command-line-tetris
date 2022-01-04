#include <fstream>
#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <map>

void split(const std::string &s, char c, std::vector<std::string> &v)
{
   std::string::size_type i = 0;
   std::string::size_type j = s.find(c);

   while (j != std::string::npos)
   {
      v.push_back(s.substr(i, j - i));
      i = ++j;
      j = s.find(c, j);

      if (j == std::string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

void showHighscore()
{
   {
      int platz = 1;
      std::string res;
      std::ifstream stream;
      stream.open("Highscores/Highscore.csv");
      std::string line;
      if (stream.is_open())
      {
         std::getline(stream, line);  
         for (int i = 1; i < 6; i++)
         {
            std::vector<std::string> v;
            std::getline(stream, line);
            split(line, ',', v);
            std::cout << "Platz " << platz << ": " << v[0] << " mit"  << v[1] << std::endl; 
            platz++;
         }
         stream.close();
      }
   }
}
