#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <numeric>

/*
template<typename T>
struct node{
  T data;
  std::unique_ptr<node<T> > next;
};

template<typename T>
*/

//First we try the solution without a templated type

struct node{
  uint32_t data;
  std::unique_ptr<node> next;
  node(uint32_t data, std::unique_ptr<node> next){
    this->data = data;
    this->next = std::move(next);
  }
};


//kth to last should run recursively and return back to us the actual kth from last node.
//It also returns to us the "distance of the most recently processed node from the end"

std::tuple<node*, uint32_t> kthToLast(std::unique_ptr<node>& head, uint32_t k){
  if(head == nullptr){
    return {nullptr, 0};
  }
  auto [curNode, i] = kthToLast(head->next, k);
  ++i;
  if (i == k){
    return {head.get(), i};
  }
  return {curNode, i};
}

std::unique_ptr<node> listGenerator(){
  std::vector<uint32_t> initVec{1,2,3,4,5,6};
  return std::accumulate(initVec.rbegin(), initVec.rend(), std::move(std::unique_ptr<node>()), [&initVec](std::unique_ptr<node>& accum, uint32_t cur){
							     return std::make_unique<node>(cur,std::move(accum));
							   });
}


int main(){
  uint32_t k{2};
  std::unique_ptr<node> inputList = std::move(listGenerator());
  auto [kthToLastNode, i] = kthToLast (inputList, k);
  if (kthToLastNode != nullptr)
    std::cout<< "The " << k << "th node from the end has data "<< kthToLastNode->data << " in the list of "<< i << " elements" << std::endl;
  return 0;
}
