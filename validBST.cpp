#include <iostream>
#include <memory>
#include <climits>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

struct Node{
  Node(int value){
    this->value = value;
  }
  int value;
  shared_ptr<Node> left{};
  shared_ptr<Node> right{};
};

// For retval to be true, leftLimit < curr->value < rightLimit
bool isValidSubTree(shared_ptr<Node> curr, int leftLimit, int rightLimit){
  if(curr == nullptr){
    return true;
  }
  if(curr->value < leftLimit || curr->value > rightLimit){
    return false;
  }
  return isValidSubTree(curr->left, leftLimit, curr->value) && isValidSubTree(curr->right, curr->value, rightLimit);
}
bool isValidBST(shared_ptr<Node> root){
  return isValidSubTree(root, INT_MIN, INT_MAX);
}

shared_ptr<Node> makeTestTree(){
  shared_ptr<Node> root{make_shared<Node>(8)};
  root->left = make_shared<Node>(4);
  root->right = make_shared<Node>(7);
  return root;
}

shared_ptr<Node> createSubTree(vector<int>& input, int left, int right){
  if(left > right)
    return shared_ptr<Node>();

  int mid{(left + right)/2};
  shared_ptr<Node> root{make_shared<Node>(input[mid])};
  root->left = createSubTree(input, left, mid-1);
  root->right = createSubTree(input, mid+1, right);
  return root;
}
shared_ptr<Node> sortedVector2Tree(vector<int> input){
  if(input.empty()){
    return shared_ptr<Node>();
  }
  return createSubTree(input, 0, input.size()-1);
}

int main(){
  //auto root{makeTestTree()};
  auto root{sortedVector2Tree({1,2,3,4,5,6,7})} ;
  std::cout << isValidBST(root) <<std::endl;
  return 0;
}
