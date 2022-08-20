#include <iostream>
#include <string>
#include <algorithm>

using std::string;

void nextPermutation (string str, string perm){
  if (str.empty())
    std::cout << perm << std::endl;
  else
    for (auto c : str){
      nextPermutation(str.substr(1), perm + str[0]);
      std::rotate(std::begin(str), std::begin(str) + 1, std::end(str));
    }
}

int main(){
  nextPermutation("main", "");
  return 0;
}
