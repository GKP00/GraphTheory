#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

using Node     = char;
using EdgeList = std::vector< std::tuple<Node, int> >;
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
      stack.push( std::get<0>(*rit));
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

int main()
{
  Graph graph;
  graph['a'] = EdgeList{ {'b', 1}, {'c', 1} };
  graph['b'] = {};
  graph['c'] = EdgeList{ {'b', 1}, {'d', 1} };
  graph['d'] = {};

  BFS('a', graph, [](auto node)
  {
    std::cout << "visit: " << node << '\n';
  });

  return 0;
}

