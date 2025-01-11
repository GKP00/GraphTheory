#include "GraphTheory.hpp"

#include <iostream>
#include <string_view>
#include <algorithm>
#include <vector>
#include <unordered_map>

std::vector<XY> FindShortestPath(std::string_view grid, XY dims, XY start={0,0})
{
  std::unordered_map<XY, XY> parentMap;
  XY currentParent;

  bool foundTarget = GridBFS(dims, start, 
  [&](auto node)
  {
    currentParent = node;
    return grid[(node.Y * (dims.X+1))+node.X] == 'e'; //goal
  },

  [&](auto neighbour)
  {
    parentMap[neighbour] = currentParent;
    return grid[(neighbour.Y * (dims.X+1))+neighbour.X] != '#'; //wall
  });

  if(!foundTarget)
    return {};

  std::vector<XY> path;
  while(parentMap.find(currentParent) != parentMap.end())
  {
    path.emplace_back(currentParent);
    currentParent = parentMap[currentParent];
  }

  path.emplace_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

int main()
{
  std::string_view grid = 
    "s..#."
    "..##."
    "....e";

  auto path = FindShortestPath(grid, {4, 2});

  for(size_t i = 0; i < path.size(); ++i)
  {
    std::cout << '(' << path[i].X << ", " << path[i].Y << ')';
    if(i+1 < path.size()) 
      std::cout << ", ";
    else
      std::cout << '\n';
  }

  return 0;
}

