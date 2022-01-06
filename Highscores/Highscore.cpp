#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Highscore.h"


void WriteToFile(std::vector<std::string> lines)
{
   std::ofstream stream;
   stream.open("./Highscore.CSV");
   if(stream.is_open())
   {
      for (auto& line : lines)
      {
         stream << line << std::endl;
      }
   }
}

void Split(const std::string &s, const char c, std::vector<std::string> &v)
{
   std::string::size_type i = 0;
   auto j = s.find(c);

   while (j != std::string::npos)
   {
      v.push_back(s.substr(i, j - i));
      i = ++j;
      j = s.find(c, j);

      if (j == std::string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

std::vector<std::string> GetHighScores()
{
   std::vector<std::string> lineArr;
   std::ifstream stream;
   stream.open("./Highscore.CSV");
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

void ShowHighscore()
{   
   std::vector<std::string> v;
   auto lineArr = GetHighScores();
   for(unsigned int i = 0; i < lineArr.size(); i++)
   {
      std::cout << i+1 << ". Platz: " <<  lineArr[i] << std::endl;    
   }
   if(lineArr.empty())
   {
       std::cout << "There are not highscores yet!" << std::endl;
   }
}

void AddHighscore(const int score, const std::string name)
{
	auto lineArr = GetHighScores();
	auto isBigger = false;
    unsigned int position = 1;

	for(unsigned int i = 0; i < lineArr.size(); i++)
   {
      std::vector<std::string> splitVector;
      Split(lineArr[i], ' ', splitVector);
      const int num = std::stoi(splitVector[1]); // actual score as int
      if(score > num)
      {
         isBigger = true;
         position = i;
         break;
      }
      position++;
   }

   if(isBigger) // Einfügen
   {
      for(unsigned int i = position; i < lineArr.size()-1; i++)
      {
         lineArr[i+1] = lineArr[i];
      }   
   }
   const auto scoreStr = std::to_string(score);
   if(lineArr.size() < 11)
   {
      lineArr.push_back(name + ", " + scoreStr + " Punkte");
   }
   else if(position < lineArr.size())
   {
      lineArr[position] = name + ", " + scoreStr + " Punkte";
   }
   WriteToFile(lineArr);
}