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

struct RetVal{
  int nodeHeight{-1};
  int maxDiameter{-1};
};

/* The height of a null node is -1, therefore a single node with nullptr left and nullptr right will have
   a diameter of zero when we do 2 + leftheight + rightheight =  2 -1 -1 = 0 
*/
RetVal maxDiameterOfBinaryTree(shared_ptr<Node> root, int maxDiameter){
  if (root == nullptr){
    return {-1,maxDiameter};
  }

  auto [leftHeight, leftmaxDiameter] = maxDiameterOfBinaryTree(root->left,  maxDiameter);
  auto [rightHeight, rightmaxDiameter] = maxDiameterOfBinaryTree(root->right,  maxDiameter);

  int maxDiamBtwnLeftAndRight{std::max(leftmaxDiameter, rightmaxDiameter)};
  int intermediateMaxDiam{std::max(maxDiamBtwnLeftAndRight, maxDiameter )};
  int curMaxDiameter{ std::max(intermediateMaxDiam, 2 + leftHeight + rightHeight)};
  int curHeight {1+ std::max(leftHeight, rightHeight)};

  return {curHeight, curMaxDiameter};
}

int main(){
  auto root{sortedVector2Tree({1,2,3,4,5,6,7})} ;

  auto [treeHeight, maxDiameter] = maxDiameterOfBinaryTree(root, -1);

  std::cout << "The max diameter of the tree is " << maxDiameter << std::endl;

  return 0;
}
