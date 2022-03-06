#include <iostream>
#include <bitset>
#include <limits>

template<typename T>
void printBits(T valueToPrint)
{
  constexpr auto numOfBits{std::numeric_limits<T>::digits};
  std::cout << std::bitset<numOfBits>{valueToPrint};
}

template<typename T>
T bitSwapRequired(T a, T b){
  constexpr auto numOfBits{std::numeric_limits<T>::digits};
  std::string underline(numOfBits,'-');
  T count{0};

  std::cout << "a bits: ", printBits<T>(a), std::cout << std::endl;
  std::cout << "b bits: ", printBits<T>(b), std::cout << "\n\n";

  for (T c =a ^ b; c != 0; c = c & (c-1)){
    std::cout << "c bits:         ", printBits<T>(c), std::cout << std::endl;
    std::cout << "c-1 bits:       ", printBits<T>(c-1), std::cout << std::endl;
    std::cout << "                "<<underline << std::endl;
    std::cout << "c & (c-1) bits: ", printBits<T>(c & (c-1)), std::cout << std::endl<<std::endl;
    
    count++;
  }
  std::cout<<"\n\n";
  return count;
}

int main(){
  uint16_t a{0},b{0};
  std::cout << "Enter a: ";
  std::cin >>a;

  std::cout << "Enter b: ";
  std::cin >>b;

  using input_type_t = decltype(a);

  input_type_t c {bitSwapRequired<input_type_t>(a, b)};
  std::cout << "number of bits to flip: "<< c << std::endl;
  
}
