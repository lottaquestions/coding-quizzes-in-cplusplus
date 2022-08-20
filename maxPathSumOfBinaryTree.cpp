#include <iostream>
#include <memory>
#include <climits>
#include <vector>
#include <tuple>

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

//int currMaxPathSum{0}; //Global variable to hold max path sum

std::tuple<int,int> maxPathSum (shared_ptr<Node> root, int  currMaxPathSum);

int dfsMaxPathSum (shared_ptr<Node> root){
  if(root == nullptr){
    return 0;
  }
  auto [maxPathNoSplit, currNodeMaxPath] = maxPathSum(root, root->value);
  return std::max(maxPathNoSplit, currNodeMaxPath);
}

std::tuple<int,int> maxPathSum (shared_ptr<Node> root, int  currMaxPathSum){
  if(root == nullptr){
    return {0, currMaxPathSum};
  }

  auto [leftMaxPath, leftCurMaxPath]   = maxPathSum(root->left, currMaxPathSum);
  auto [rightMaxPath, rightCurMaxPath] = maxPathSum(root->right, currMaxPathSum);
  
  leftMaxPath  = std::max(leftMaxPath, 0);
  rightMaxPath = std::max(rightMaxPath, 0);

  // Compute max path sum with split and compare it to the current max path sum
  int splitMaxPathSum { std::max(currMaxPathSum, root->value + leftMaxPath +  rightMaxPath)};

  // Compute the max path sum with no split
  int noSplitMaxPath { root->value + std::max(leftMaxPath, rightMaxPath) };

  // Compute what this node perceives to be the overall max path
  int maxBtwnLeftAndRight {std::max(leftCurMaxPath, rightCurMaxPath)};
  int currNodeMaxPath {std::max(splitMaxPathSum, maxBtwnLeftAndRight)};
  return {noSplitMaxPath, currNodeMaxPath};
}


int main(){
  auto root{sortedVector2Tree({1,2,3,4,5,6,7})} ;
  int theMaxPathSum {dfsMaxPathSum(root)};

  std::cout<< "The max path sum is " << theMaxPathSum << std::endl;

  return 0;
}
