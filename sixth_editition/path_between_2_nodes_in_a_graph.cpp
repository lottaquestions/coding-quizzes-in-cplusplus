#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>
#include <execution>

// To compile: g++ -std=gnu++17 -g3 path_between_2_nodes_in_a_graph.cpp -o path_between_2_nodes_in_a_graph.bin -ltbb

enum class State {Unvisited, Visited, Visiting};

struct Node{
  std::string name;
  std::vector<std::shared_ptr<Node> > children;
  State state{State::Unvisited};

  Node (std::string& name){this->name = name;}
  std::vector<std::shared_ptr<Node> >& getAdjacent(){
    return children;
  }
  
};

struct Graph{
  std::vector<std::shared_ptr<Node>> nodes;
  std::vector<std::shared_ptr<Node> >& getNodes(){
    return nodes;
  }
};

bool search (Graph g, std::shared_ptr<Node> start, std::shared_ptr<Node> end){
  if (start == end)
    return true;

  // Operates as a queue
  std::deque<std::shared_ptr<Node> > q{};

  auto& graphNodes{g.getNodes()};

  std::for_each(std::execution::par, graphNodes.begin(), graphNodes.end(), [](std::shared_ptr<Node> curNode){ curNode->state = State::Unvisited; return;});//Can be removed

  start->state = State::Visiting;

  q.push_back(start);

  std::shared_ptr<Node> u;
  while(!q.empty()){
    u = q.front();
    if(u != nullptr){
      q.pop_front();
      std::vector<std::shared_ptr<Node> >& adjacentNodes = u->getAdjacent();
      bool isFound = std::any_of(adjacentNodes.begin(), adjacentNodes.end(), [end, &q](std::shared_ptr<Node> v){
								if(v->state == State::Unvisited){
								  if(v == end){
								    return true;
								  }else{
								    v->state = State::Visiting;
								    q.push_back(v);
								  }
								}
								return false;
							      });
      if (isFound)
	return isFound;
      u->state = State::Visited;
    }
  }
  return false;
  
}

std::vector<std::shared_ptr<Node>> createGraphNodes(std::vector<std::string>& nodeValues){
  std::vector<std::shared_ptr<Node> > graph{};
  graph.reserve(nodeValues.size());
  std::transform(nodeValues.begin(), nodeValues.end(), std::back_inserter(graph), [](std::string& name){return std::make_shared<Node>(name);});
  return graph;
}

void addChildrenToNode(std::string nodeValue, std::vector<std::string> childrenValues, Graph& graph){
  auto& graphNodes{graph.getNodes()};
  auto itToNode = std::find_if(graphNodes.begin(), graphNodes.end(), [&nodeValue](std::shared_ptr<Node> node){
								       if (nodeValue.compare(node->name) == 0){
									 return true;
								       }
								       return false;
								     });
  if (itToNode == graphNodes.end()){
    std::cerr <<"Invalid node provided: "<< nodeValue << " . Will not add child nodes"<< std::endl;
    return;
  }
  std::shared_ptr<Node> parentNode = (*itToNode);
  for(auto& child : childrenValues){
    auto it = std::find_if(graphNodes.begin(), graphNodes.end(), [&child](std::shared_ptr<Node> possibleChildNode){
								   if(child.compare(possibleChildNode->name) == 0){
								     return true;
								   }
								   return false;
								 });
    if(it == graphNodes.end()){
      std::cerr<< "Child node: "<< child << " does not exist. Skipping..." << std::endl;
      continue;
    }
    parentNode->children.emplace_back(*it);
  }
}

int main(){
  std::vector<std::string> nodeValues{"0","1","2","3"};

  Graph theGraph{};
  theGraph.nodes = createGraphNodes(nodeValues);
  addChildrenToNode("0",{"1"}, theGraph);
  addChildrenToNode("1",{"2"}, theGraph);
  addChildrenToNode("2",{"0","3"}, theGraph);
  addChildrenToNode("3",{"2"}, theGraph);

  auto& graphNodes{theGraph.getNodes()};
  auto src{graphNodes[0]};
  auto dest{graphNodes[3]};
  bool routeExists{search(theGraph, src, dest)};

  std::unordered_map<bool, std::string> printBool{{true, "True"}, {false, "False"}};

  std::cout << "It is "<< printBool[routeExists] << " that a route exists between " << src->name << " and " << dest->name << std::endl;

  return 0;
}
