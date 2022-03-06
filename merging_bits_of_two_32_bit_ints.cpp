#include <iostream>
#include <bitset>
#include <limits>

template<typename T>
void printBits(T valueToPrint)
{
  constexpr auto numOfBits{std::numeric_limits<T>::digits};
  std::cout << std::bitset<numOfBits>{valueToPrint};
}

template<typename T1, typename T2>
auto updateBits(T1 n, T1 m, T2 i, T2 j )
{
  using valueType =  decltype(n);
  std::cout << "n: ", printBits<valueType>(n), std::cout << std::endl;
  std::cout << "m: ", printBits<valueType>(m), std::cout << std::endl;
  /* Create a mask to clear bits i through j in n
   * EXAMPLE: i = 2, j = 4. Result should be 11100011.
   * For simplicity, we'll use just 8 bits for the example. 
   */
  valueType allOnes = ~0; // A sequence of all ones

  // 1s before position j, then 0s. What is left based on our example 11100000
  valueType left = allOnes << (j + 1);
  std::cout << "Left: ", printBits<valueType>(left), std::cout << std::endl;
  
  valueType right = ((1<<i) - 1);
  std::cout << "Right: ", printBits<valueType>(right), std::cout << std::endl;

  // All 1s except zeros between i and j
  valueType mask = left | right;
  std::cout << "Mask: ", printBits<valueType>(mask), std::cout << std::endl;

  // Clear bits j through i in n and then insert m
  valueType n_cleared = n & mask;
  valueType m_shifted = (m << i);
  valueType m_in_n_inserted = n_cleared | m_shifted;
  std::cout << "Final: ", printBits<valueType>(m_in_n_inserted), std::cout << std::endl;

  return m_in_n_inserted;
}

int main()
{
  uint8_t n{0b1110'1011}, m{0b110}, i{2}, j{4};
  auto result = updateBits<decltype(n), decltype(i)>( n, m, i, j );
}
