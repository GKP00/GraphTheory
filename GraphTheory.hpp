#pragma once

#include <cstddef>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string_view>
#include <tuple>
#include <functional>

using Node = const char*;
struct Edge
{
  Edge(Node n, int w=1) : Neighbour{n}, Weight{w} {}
  Node Neighbour;
  int Weight;
};

using EdgeList = std::vector<Edge>;
using Graph    = std::unordered_map<Node, EdgeList>;

void RecursiveDFS(Node node, const Graph& graph, void(*visit)(Node), 
    std::unordered_set<Node>& visited)
{
  if(visited.find(node) != visited.end()) 
    return;

  visited.insert(node);
  visit(node);

  for(auto [n, w] : graph.find(node)->second)
    RecursiveDFS(n, graph, visit, visited);
}

void DFS(Node start, const Graph& graph, void(*visit)(Node))
{
  std::unordered_set<Node> visited;
  std::stack<Node> stack;
  stack.push(start);

  while(!stack.empty())
  {
    Node node = stack.top();
    stack.pop();

    if(visited.find(node) != visited.end()) 
      continue;

    visited.insert(node);
    visit(node);

    auto it = graph.find(node);
    if(it == graph.end())
      throw;

    for(auto rit = it->second.rbegin(); rit != it->second.rend(); ++rit)
      stack.push( rit->Neighbour);
  }
}

void BFS(Node start, const Graph& graph, void(*visit)(Node))
{
  std::queue<Node> queue;
  queue.emplace(start);

  std::unordered_set<Node> visited;
  visited.emplace(start);

  while(!queue.empty())
  {
    Node node = queue.front();
    queue.pop();

    visit(node);

    auto it = graph.find(node);
    if(it == graph.end())
      throw;

    for(auto [n, w] : it->second)
    {
      if(visited.find(n) == visited.end()) 
        queue.emplace(n);
    }
  }

}

size_t ConnectedComponents(const Graph& graph)
{
  size_t n = 0;
  std::unordered_set<Node> visited;

  for(auto kv : graph)
  {
    Node node = kv.first;

    if(visited.find(node) != visited.end())
      continue;

    ++n;
    RecursiveDFS(node, graph, [](auto){}, visited);
  }

  return n;
}

//for Grid based functions
struct XY 
{ 
  int X, Y; 

  bool operator==(const XY& other) const
  {
    return X == other.X && Y == other.Y;
  }
};
namespace std //make XY hashable for stl containers
{
  template<>
  struct hash<XY>
  { 
    std::size_t operator()(const XY& xy) const 
    {
      return std::hash<int>()(xy.X) ^ (std::hash<int>()(xy.Y) << 1);
    }
  };
}

bool GridBFS(std::string_view grid, XY dims, XY start, 
    std::function<bool(XY)> visit, //to stop search return false
    std::function<bool(XY)> shouldQueue = [](auto){ return true; }) 
{
  static const XY moveDirs[] = 
  {
    {+1,+0},
    {+0,+1},
    {-1,+0},
    {+0,-1},
  };

  std::queue<XY> queue;
  std::vector<bool> visited((dims.X+1) * (dims.Y+1), false);

  queue.emplace(start);
  visited[(start.Y * (dims.X+1)) + start.X] = true;

  while(!queue.empty())
  {
    XY node = queue.front();
    queue.pop();

    if(visit(node))
      return true;

    //visit every possible neighbour (every direction):
    for(size_t i = 0; i < sizeof(moveDirs)/sizeof(moveDirs[0]); ++i)
    {
      XY neighbour = {node.X+moveDirs[i].X, node.Y+moveDirs[i].Y};

      //dont visit out of bounds neighbour nodes
      if((neighbour.X < 0) || (neighbour.X > dims.X) ||
         (neighbour.Y < 0) || (neighbour.Y > dims.Y) )
        continue;

      //dont visit already visited nodes
      if(visited[(neighbour.Y * (dims.X+1)) + neighbour.X])
        continue;

      //dont visit if callback says no
      if(!shouldQueue(neighbour))
        continue;

      visited[(neighbour.Y * (dims.X+1)) + neighbour.X] = true;
      queue.emplace(neighbour);
    }

  }

  return false;
}

