#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include <variant>
#include <functional>

// To compile: g++ -std=c++17 -O0 -g3 LRUCache.cpp -o LRUCache.bin

struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node{
  NodePtr prev{nullptr};
  NodePtr next{nullptr};
  int key{0};
  int value{0};

  Node()=default;
  explicit Node(int key, int value) : key(key), value(value){}
  
};

template<unsigned int CAPACITY=2>
class LRUCache{
public:
  std::optional<int> get(int key){
    auto it = cache.find(key);
    if(it != cache.end()){
      
      /* Found an item, send it to the back of the double-linked list */
      NodePtr curNode{it->second};
      //Remove (delink) node from current position
      removeNodeFromList(curNode);
      //Insert (relink) node just before tailPtrToMRU
      tailPtrToMRU->prev->next = curNode;
      tailPtrToMRU->prev = curNode;
      
      return std::optional<int>{curNode->value};
    }
    return std::nullopt;
  }
  void removeNodeFromList(NodePtr curNode){
    //Remove (delink) node from current position
    curNode->prev->next = curNode->next;
    curNode->next->prev = curNode->prev;
  }
  
  void put(int key, int value){

    // Full cache case
    if (elementCount == CAPACITY){
      // Cache is at capacity remove LRU Node
      NodePtr elemToRemove = headPtrToLRU->next;
      removeNodeFromList(elemToRemove);
      cache.erase(elemToRemove->key);
      --elementCount;
    }

    // Inserting a key that already exists case 
    auto it = cache.find(key);
    if (it != cache.end()){
      // Remove the old key to make room for the new one
      removeNodeFromList(it->second);
      cache.erase(it);
    }

    // After performing all prechecks and pe-actions, insert the new item in the cache
    NodePtr newCacheItem = std::make_shared<Node>(key,value);
    cache.insert({key,newCacheItem});
    tailPtrToMRU->prev->next = newCacheItem;
    newCacheItem->prev = tailPtrToMRU->prev;
    newCacheItem->next = tailPtrToMRU;
    tailPtrToMRU->prev = newCacheItem;
    ++elementCount;
  }

  LRUCache(){
    headPtrToLRU = std::make_shared<Node>(0,0);
    tailPtrToMRU = std::make_shared<Node>(0,0);
    headPtrToLRU->next = tailPtrToMRU;
    tailPtrToMRU->prev = headPtrToLRU;
    elementCount = 0;
  }
private:
  std::unordered_map<int,NodePtr> cache;
  NodePtr headPtrToLRU; // Dummy node at head points to least recently used node
  NodePtr tailPtrToMRU; // Dummy node at tail points to most recently used node
  unsigned int elementCount;
};


int main(){
  LRUCache lruCache;
  enum class CacheActions {PUT, GET};
  std::vector<std::pair<CacheActions, std::variant<int, std::pair<int,int>> >> testInput{std::pair{CacheActions::PUT, std::pair{1,1}},
											 std::pair{CacheActions::PUT, std::pair{2,2}},
											 std::pair{CacheActions::GET, 1},
											 std::pair{CacheActions::PUT, std::pair{3,3}},
											 std::pair{CacheActions::GET, 2},
											 std::pair{CacheActions::PUT, std::pair{4,4}},
											 std::pair{CacheActions::GET, 1},
											 std::pair{CacheActions::GET, 3},
											 std::pair{CacheActions::GET, 4} };

  auto putTest = [&lruCache](std::variant<int, std::pair<int,int>>& input){
		   auto [key,val] = std::get<std::pair<int,int>>(input);
		   lruCache.put(key,val);
		   std::cout << "puting [key, value] = " << key << ", " << val <<std::endl; 
		 };

  auto getTest = [&lruCache](std::variant<int, std::pair<int,int>>& input){
		   int key = std::get<int>(input);
		   std::optional<int> lruRetval = lruCache.get(key);
		   if(lruRetval){
		     std::cout << "Requested "<< key << " got "<< lruRetval.value() << std::endl;
		   }else{
		     std::cout << "Requested "<< key << " got nothing" << std::endl;
		   }
		 };
  std::unordered_map<CacheActions, std::function<void(std::variant<int, std::pair<int,int>>&)> > actionToTestFunc{{CacheActions::PUT, putTest},
														  {CacheActions::GET, getTest}};
  for(auto& [action, value] : testInput){
    actionToTestFunc[action](value);
  }
  return 0;
}
