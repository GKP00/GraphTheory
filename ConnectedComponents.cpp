#include "GraphTheory.hpp"

#include <iostream>

int main()
{
  Graph graph;
  graph["0"]  = {"4", "8", "14", "13"};
  graph["1"]  = {"5"};
  graph["2"]  = {"15", "9"};
  graph["3"]  = {"9"};
  graph["4"]  = {"8", "0"};
  graph["5"]  = {"1", "16", "17"};
  graph["6"]  = {"7", "11"};
  graph["7"]  = {"6", "11"};
  graph["8"]  = {"4", "0", "14"};
  graph["9"]  = {"3", "15", "2"};
  graph["10"] = {"15"};
  graph["11"] = {"6", "7"};
  graph["12"] = {};
  graph["13"] = {"0", "14"};
  graph["14"] = {"0", "13", "8"};
  graph["15"] = {"10", "2", "9"};
  graph["16"] = {"5"};
  graph["17"] = {"5"};

  std::cout << ConnectedComponents(graph) << '\n';
  return 0;
}

