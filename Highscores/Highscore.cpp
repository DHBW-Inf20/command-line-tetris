#include <fstream>
#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <map>

void writeToFile(std::vector<std::string> lines)
{
   std::ofstream stream;
   stream.open("Highscores/Highscore.csv");
   if(stream.is_open())
   {
      for(int i = 0; i < 11; i++)
      {
         stream << lines[i] << std::endl;
      }
      stream << "Test" << std::endl;
   }
}

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

std::vector<std::string> getHighScores()
{
   std::vector<std::string> lineArr;
   std::ifstream stream;
   stream.open("Highscores/Highscore.csv", std::ios::out);
   std::string line;
   if (stream.is_open())
   {
      while(std::getline(stream, line))
      {
         lineArr.push_back(line);
      }
   }
   stream.close(); 
   return lineArr;
}

void showHighscore()
{
   std::vector<std::string> v;
   std::vector<std::string> lineArr = getHighScores();
   for(int i = 1; i < 11; i++)
   {
      std::cout << i << ". Platz:" <<  lineArr[i] << std::endl;
   }
}

void addHighscore(int score, std::string name)
{ 
   std::vector<std::string> lineArr = getHighScores();
   std::vector<std::string> splitVector;
   bool isBigger = false;
   int position;
   int num;
   for(int i = 1; i < 11; i++)
   {
      split(lineArr[i], ' ', splitVector);
      num = std::stoi(splitVector[1]); // actual score as int
      if(score >= num)
      {
         isBigger = true;
         position = i;
         break;
      }
   }

   if(isBigger) // Einfügen
   {   
      for(int i = position; i < 10; i++)
      {
         lineArr[i+1] = lineArr[i];
      }
      lineArr[position] = name + ", " + std::to_string(score) + " Punkte";
      writeToFile(lineArr);
   }
}