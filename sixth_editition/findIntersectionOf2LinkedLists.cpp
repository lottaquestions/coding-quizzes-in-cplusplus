#include <iostream>
#include <memory>
#include <vector>
#include <numeric>
#include <cmath>
#include <tuple>
#include <array>

//Ubuntu 20 cored dumps are stored in /var/lib/apport/coredump

struct node{
  uint32_t data;
  std::shared_ptr<node> next;
  node(uint32_t data, std::shared_ptr<node> next){
    this->data = data;
    this->next = next;
  }
};

std::shared_ptr<node> listGenerator(std::vector<uint32_t>& initVec, std::shared_ptr<node> initAccum){
  return std::accumulate(initVec.rbegin(), initVec.rend(), initAccum, [&initVec](std::shared_ptr<node> accum, uint32_t cur){
							     return std::make_shared<node>(cur, accum);
							   });
}

std::tuple<std::shared_ptr<node>, uint32_t> getTailAndSize(std::shared_ptr<node> inputList){
  if (inputList == nullptr)
    return {std::shared_ptr<node>(), 0};

  uint32_t size {1};
  std::shared_ptr<node> current {inputList};

  while (current->next != nullptr){
    ++size;
    current = current->next;
  }
  return {current, size};
}

std::shared_ptr<node> getKthNode(std::shared_ptr<node> head, uint32_t k){
  std::shared_ptr<node> current{head};
  while (k > 0 && current != nullptr){
    --k;
    current = current->next;
  }
  return current;
}

std::shared_ptr<node> findIntersection(std::shared_ptr<node> list1, std::shared_ptr<node> list2){
  using std::array;
  using std::shared_ptr;
  if (list1 == nullptr  && list2 == nullptr )
    return std::shared_ptr<node>();

  // Get tail and size
  auto [tail1, size1] = getTailAndSize(list1);
  auto [tail2, size2] = getTailAndSize(list2);

  // If different tail nodes, then there is no intersection
  if (tail1 != tail2)
    return std::shared_ptr<node>();

  // Set pointers to the start of each linked list
  auto [shorter, longer] = size1 < size2 ? (array<shared_ptr<node>,2>{list1, list2}) : (array<shared_ptr<node>,2>{list2, list1});

  // Advance pointer for the longer linked-list by the difference in lengths
  longer = getKthNode(longer, std::abs(long(size1) - long(size2)));

  // Move both pointers until you get a collision
  while (shorter.get() != longer.get()){
    shorter = shorter->next;
    longer = longer->next;
  }

  // Return either one
  return longer;
}

int main(){

  std::vector<uint32_t> commonVec{1,2,3,4,5,6};
  std::vector<uint32_t> firstVec{7,8,9};
  std::vector<uint32_t> secondVec{11,12,7,8,9};

  std::shared_ptr<node> commonList{listGenerator(commonVec, std::shared_ptr<node>()) };
  std::shared_ptr<node> list1 {listGenerator(firstVec, commonList )};
  std::shared_ptr<node> list2 {listGenerator(secondVec, commonList )};

  auto intersectNode{findIntersection(list1, list2)};

  std::cout << "The intersecting node is " << intersectNode << " with value " << intersectNode->data << std::endl; 

  return 0;
}
