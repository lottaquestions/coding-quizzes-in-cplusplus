#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <bitset>

// In this solution uniqueCharsv2 is better than uniqueChars because it uses a bitset hence lower space utilization. It may be faster too (though that is not proven),
// and it takes into account the whole character set (assumed to be ASCII), rather then only considering alphanumeric characters.

std::string strToLower(std::string input){
  std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){return std::tolower(c);});
  return input;
}

bool uniqueChars(std::string& inputString){
  std::unordered_map<unsigned char, int> countMap;
  std::string inputStr {strToLower(inputString)};
  bool hasDuplicate = std::any_of(inputStr.begin(), inputStr.end(), [&countMap](const unsigned char c){
						  if(countMap.find(c) == countMap.end()){
						    countMap.emplace(c,1);
						    return false;
						  }
						  else
						    return true;
						});

  return !hasDuplicate;
}

bool uniqueCharsv2(std::string& inputString){
  //Ask the interviewer if the character set is ASCII or unicode. In this solution, assume ASCII
  //ie assume 128 characters in the character-set
  constexpr int charSetSize{128};
  
  if (inputString.length() > charSetSize)
    return false;
  std::bitset<charSetSize> charSet;

  bool hasDuplicate = std::any_of(inputString.begin(), inputString.end(), [&charSet](const unsigned char c){
								      if(charSet[c]){
									return true;
								      }
								      charSet[c] = true;
								      return false;
								    });
  return !hasDuplicate;
}

int main(){
  std::string inputString {"Does this string have uniqe characters"};
  std::unordered_map<bool,std::string> bool2String{{false, "False"}, {true, "True"}};
  std::cout << "Is unique characters " << bool2String[uniqueChars(inputString)] << std::endl;
  std::cout << "Is unique characters v2 " << bool2String[uniqueCharsv2(inputString)] << std::endl;
  inputString = "AbCDEF";
  std::cout << "Is unique characters " << bool2String[uniqueChars(inputString)] << std::endl;
  std::cout << "Is unique characters v2 " << bool2String[uniqueCharsv2(inputString)] << std::endl;
  return 0;
}
