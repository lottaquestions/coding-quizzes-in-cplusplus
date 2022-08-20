#include<iostream>
#include<string>

std::string longestPalindromicSubstring(std::string input){
  auto strLen{input.length()};
  if (strLen <= 1)
    return input;
  using sSizet = decltype(strLen);

  sSizet curPalindromeLen{0};
  std::string curPalindrome{};
  for (sSizet i = 0; i < strLen ; ++i){
    
    auto getPalindrome = [&](sSizet left, sSizet right){
			  while (left >= 0 &&  right < strLen && input[left] == input[right]){
			    if (auto newPalindromeLen = (right - left + 1); newPalindromeLen  > curPalindromeLen){
			      curPalindrome = input.substr(left, right+1);
			      curPalindromeLen = newPalindromeLen;
			    }

			    --left;
			    ++right;
      
			  }
			};
    //Odd lenght palindrome
    auto left{i};
    auto right{i};
    getPalindrome(left, right);

    //Even length palindrome
    left = i;
    right= i+1;
    getPalindrome(left, right);
    
  }
  return curPalindrome;
}

int main(){
  std::string input{"babad"};
  std::cout << "The longest palindromic substring is " << longestPalindromicSubstring(input) << std::endl;
  return 0;
}
