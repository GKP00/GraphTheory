#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

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

  while(!queue.empty())
  {
    Node node = queue.front();
    queue.pop();

    visit(node);

    auto it = graph.find(node);
    if(it == graph.end())
      throw;

    for(auto [n, w] : it->second)
      queue.emplace(n);
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

