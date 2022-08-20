#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

int myAtoi(std::string input){
  if (input.empty())
    return 0;

  auto strLen{input.length()};
  int i{0};
  while (input[i] == ' ' && i < strLen)
    ++i;
  if (i >= strLen)
    return 0;
  int sign {1};
  if (input[i] == '-'){
    sign = -1;
    ++i;
  }
  else if(input[i] == '+'){
    ++i;
  }
  int result{0};
  while(i < strLen && std::isdigit(input[i])){
    result = result * 10 + (input[i] - '0');
    ++i;
  }
  return sign*result;
}

int main(){
  std::vector<std::string> testVals{"  +132", "   -6578", "","asdada"};
  std::for_each(testVals.begin(), testVals.end(), [](std::string input){
						    std::cout << "Input: " << input << ", Output: "<< myAtoi(input) << std::endl;
						  });
  return 0;
}
