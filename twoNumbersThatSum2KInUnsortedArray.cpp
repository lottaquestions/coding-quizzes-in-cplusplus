#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <utility>

using std::tuple;
using std::vector;
using std::pair;

tuple<int,int> getTwoNumsThatSumToK(vector<int> inputVec, int K){
  std::unordered_map<int,int> input2KdiffMap{};
  int firstNumber{0};
  int secondNumber{0};
  auto foundIt = std::find_if(inputVec.begin(), inputVec.end(), [&K, &input2KdiffMap, &firstNumber](int currItem){
						   input2KdiffMap[currItem] = K - currItem;
						   int searchItem{input2KdiffMap[currItem]};
						   auto it = std::find_if(input2KdiffMap.begin(), input2KdiffMap.end(), [&searchItem](pair<const int,int> currPair){
														return (searchItem != currPair.second && searchItem == currPair.first);
														 
													      });
						   if (it != input2KdiffMap.end() ){
						     firstNumber = it->first;
						     return true;
						   }
						   return false;
						 });
  secondNumber = (foundIt != inputVec.end()) ? (*foundIt) : 0;
  return {firstNumber, secondNumber};
}


int main(){
  vector<int> input{1,2,3,4,5,6,7,8,9,10};
  int K{10};
  auto [firstNum, secondNum] = getTwoNumsThatSumToK(input, K);

  std::cout << "The two numbers that sum to " << K <<" are " << firstNum << " and " << secondNum << std::endl;

  return 0;
}
