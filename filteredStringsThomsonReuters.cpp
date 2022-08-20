#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::find_if;

struct Node{
  bool endFlag;
  vector<shared_ptr<Node> > children;
  bool isPrefixWord;
  char value;
  bool isRoot;

  Node(bool isRoot, char value){
    children.reserve(26);
    endFlag = false;
    isPrefixWord = false;
    this->isRoot = isRoot;
    this->value = value;
  }
};

void addWord(string inputString, shared_ptr<Node> inputRoot){
  Node* root {inputRoot.get()};
  for(char c : inputString){
    if(c == '/'){
      root->isPrefixWord = true;
      continue;
    }
    auto& children {root->children};
    auto childFinder = [&c](shared_ptr<Node> currNode){return static_cast<char>(currNode->value) == c;};
    if(find_if(children.begin(), children.end(), childFinder) == root->children.end()){
      root->children[c-'a'] = make_shared<Node>(false,c);
    }
    root = root->children[c-'a'].get();
    if (root->endFlag)
      break;
  }
  root->endFlag = true;
}

string printTrie (shared_ptr<Node> root){
  if(root->endFlag){
    return "\n";
  }
  string outputString{};
  for (auto child : root->children){
    outputString.push_back(child->value);
    if(child->isPrefixWord){
      outputString.push_back('/');
    }
    outputString.append(printTrie(child));
  }
  return outputString;
}

int main (){
  shared_ptr<Node> root {make_shared<Node>(true,'/')};
  addWord("/flapp/server/apache", root);
  addWord("/d/apps", root);
  addWord("/d/apps/pub", root);
  addWord("/flapp", root);
  addWord("/flocal/firms", root);
  addWord("/d/sw/java", root);
  addWord("/d/sw/orcl/jdbc", root);

  string filteredResult{"/" + printTrie(root)};

  std::cout << filteredResult << std::endl;
  return 0;
}
