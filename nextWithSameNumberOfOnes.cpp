#include<iostream>
#include <bitset>
#include <limits>

template<typename T>
void printBits(T valueToPrint)
{
  constexpr auto numOfBits{std::numeric_limits<T>::digits};
  std::cout << std::bitset<numOfBits>{valueToPrint};
}

template<typename T>
T getNext(T n){
  T c = n;
  T c0 = 0;
  T c1 = 0;

  while (((c & 1) == 0) && (c != 0)){
    c0++;
    c >>= 1;
  }

  while ((c & 1) == 1){
    c1++;
    c >>=1;
  }

  // If n == 11...1100...0, then there is no bigger number with the same number of ones.
  constexpr auto numOfBits{std::numeric_limits<T>::digits};
  if ((c0+c1) == (numOfBits-1) || (c0+c1)==0){
    throw "No bigger number with same number of ones!";
  }

  T p = c0 + c1;// Position of rightmost non-trailing zero
  std::cout << "Original number: ", printBits<T>(n), std::cout<<std::endl;
  
  n |= (1 << p);// Flip rightmost non-trailing zero.
  std::cout << "After flipping right most non-trailing zero: ", printBits<T>(n), std::cout<<std::endl;
  
  n &= ~((1 << p)-1);// Clear all bits to the right of p
  std::cout << "After clering all bits to the right of the flip point: ", printBits<T>(n), std::cout<<std::endl;
  
  n |= (1 << (c1-1)) -1; //Insert (c1-1) ones on the right
  std::cout << "After inserting c1-1 ones to the right of the flip point: ",  printBits<T>(n), std::cout<<std::endl;
  
  return n;
}

template<typename T>
T getPrev(T n){
  T temp = n;
  T c0 = 0;
  T c1 = 0;

  while (temp & 1 == 1){
    c1++;
    temp >>= 1;
  }

  if (temp == 0)
    return -1;

  while (((temp & 1) == 0) && (temp != 0)){
    c0++;
    temp >>= 1;
  }

  T p = c0 + c1;// Position of rightmost non-trailing one

  n &= ((~0) << (p + 1)); //Clears bit p and all bits to the right of it ie at positions lesser than p

  T mask = ( 1<< (c1 + 1)) - 1; // Sequence of (c1+1) ones

  n |= mask << (c0-1);

  std::cout << "After inserting c1+1 ones to the right of the flip point: ",  printBits<T>(n), std::cout<<std::endl;

  return n;
}

int main(){
  uint16_t valueToTest;
  std::cout << "Enter a value to test: ";
  std::cin >> valueToTest;
  std::cout << "The next bigger number with the same number of ones: " << static_cast<int>(getNext<decltype(valueToTest)>(valueToTest)) << std::endl;
  
  std::cout << "The next smaller number with the same number of ones: " << static_cast<int>(getPrev<decltype(valueToTest)>(valueToTest)) << std::endl;
}
