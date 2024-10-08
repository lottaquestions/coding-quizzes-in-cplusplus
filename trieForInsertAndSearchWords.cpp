#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
// To compile: g++ -std=c++17 -O0 -g3 trieForInsertAndSearchWords.cpp -o trieForInsertAndSearchWords.bin
// source: https://www.youtube.com/watch?v=BTf05gs_8iU

struct TrieNode{
  std::map<char,std::shared_ptr<TrieNode>> children{};
  bool isWord{false};
};
using TrieNodePtr = std::shared_ptr<TrieNode>;

class WordDictionary{
public:
  
  void addWord(std::string& word){
    TrieNode* curNodePtr = &root;
    for (const char c : word){
      TrieNode& curNode = *curNodePtr;
      if( curNode.children.find(c) == curNode.children.end()){
	curNode.children[c] = std::make_shared<TrieNode>();
      }
      curNodePtr = curNode.children[c].get();
    }
    curNodePtr->isWord = true;
  }

  bool searchWord(std::string& word){
    if (word.compare("") == 0){
      return false;
    }
    return dfs(0, root, word);
  }

  
private:
  bool dfs(int j, TrieNode& rootNode, std::string& word){
    TrieNode* curPtr = &rootNode;
    for(auto i = j ; i < word.size() ; i++){
      TrieNode& cur{*curPtr};
      const char c = word[i];
      if (c == '.'){
        for (auto &[_, child] : cur.children){
          if (dfs(i + 1, *child, word))
          {
            return true;
          }
        }
        return false;
      }
      else
      {
        if (cur.children.find(c) == cur.children.end())
        {
          return false;
        }
        curPtr = cur.children[c].get();
      }
    }
    return curPtr->isWord;
  }
  
  TrieNode root{};
};


int main(){
  // Test inputs
  std::vector<std::string> inputAddWords{"bad", "dad", "mad", "bada"};
  std::vector<std::string> inputSearchWords{"pad", "bad", ".ad", "b.."};
  
  WordDictionary wordDict;

  std::for_each(inputAddWords.begin(), inputAddWords.end(), [&wordDict](std::string& inputWord){return wordDict.addWord(inputWord);});
  
  std::for_each(inputSearchWords.begin(), inputSearchWords.end(), [&wordDict](std::string& inputWord){
								     bool foundWord = wordDict.searchWord(inputWord);
								     if (foundWord){
								       std::cout << inputWord <<" true" << std::endl;
								     }else{
								       std::cout << inputWord << "false" << std::endl;
								     }
								     return;
								   });
  return 0;
}