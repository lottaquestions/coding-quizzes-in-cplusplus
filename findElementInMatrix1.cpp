#include <iostream>
#include <vector>

template<typename T>
bool findElement(std::vector<std::vector<T> > &matrix, T elem){
  size_t row = 0;
  size_t col = matrix[0].size() -1;

  while (row < matrix.size() && col >= 0){
    if (matrix [row][col] == elem){
      return true;
    }
    else if (matrix [row][col] > elem){
      --col;
    }
    else{
      ++row;
    }
  }

  return false;
}

int main(){
  std::vector<std::vector<int> > matrix{{15, 20, 40,  85},
                                        {20, 35, 80,  95},
					{30, 55, 95,  105},
					{40, 80, 100, 120}};

  int valToFind{0};
  std::cout << "Value to find: ";
  std::cin >> valToFind;
  std::cout << (findElement<int>(matrix, 55)? "Found element!\n": "Did not find element!\n");

  return 0;
}
