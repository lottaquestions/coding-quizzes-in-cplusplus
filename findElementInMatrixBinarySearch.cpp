#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

struct Coordinate;

template<typename T>
Coordinate findElement(std::vector<std::vector<T> > &matrix, Coordinate origin, Coordinate dest, T elem);

template<typename T>
Coordinate findElement(std::vector<std::vector<T> > &matrix, T elem);

template<typename T>
Coordinate partitionAndSearch(std::vector<std::vector<T> > &matrix, Coordinate origin, Coordinate dest, Coordinate pivot, T elem);

struct Coordinate{
  int row;
  int column;

  Coordinate(int r, int c): row(r), column(c){}
  Coordinate(Coordinate &source): row(source.row), column(source.column){}
  Coordinate(Coordinate &&source): row(std::move(source.row)), column(std::move(source.column)){}

  template<typename T>
  bool inbounds(std::vector<std::vector<T> > &matrix){
    return row >=0 && column >= 0 &&
      row < matrix.size() && column < matrix[0].size();
  }

  bool isBefore(Coordinate p){
    return row <= p.row && column <= p.column;
  }

  void setToAverage(Coordinate min, Coordinate max){
    row    = (min.row + max.row)/2;
    column = (min.column + max.column)/2;
  }

  bool operator==(Coordinate &other){
    return this->row == other.row && this->column == other.column;
  }
  
  bool operator==(Coordinate &&other){
    return this->row == other.row && this->column == other.column;
  }

  bool operator!=(Coordinate &&other){
    return !(this->operator==(std::move(other)) );
  }
   bool operator!=(Coordinate &other){
     return !(this->operator==(other) );
  }
};

//template<typename T>
//Coordinate::inbounds(std::vector<std::vector<T> > &matrix) -> Coordinate::inbounds<T>(std::vector<std::vector<T> > &matrix);
  

template<typename T>
Coordinate findElement(std::vector<std::vector<T> > &matrix, Coordinate origin, Coordinate dest, T elem){
  if (!origin.inbounds<T>(matrix) || !dest.inbounds<T>(matrix))
    return Coordinate{-1,-1};

  if (matrix[origin.row][origin.column] == elem)
    return origin;
  else if (!origin.isBefore(dest))
    return Coordinate{-1,-1};

  // Set start to start of diagonal and end to the end of the diagonal. Since the grid may not be square,
  // the end of the diagonal may not equal dest
  Coordinate start{origin};

  int diagDist { std::min(dest.row - origin.row, dest.column - origin.column) };

  Coordinate end {start.row + diagDist, start.column + diagDist};
  Coordinate p {0,0};

  //Do binary search on the diagonal, looking for the first element greater than elem
  while (start.isBefore(end)){
    p.setToAverage(start, end);
    if (elem > matrix[p.row][p.column]){
      start.row = p.row + 1;
      start.column = p.column + 1;
    }
    else{
      end.row = p.row - 1;
      end.column = p.column -1;
    }
  }

  // Split the grid into quadrants. Search the bottom left and the top right
  return partitionAndSearch<T>(matrix, origin, dest, start, elem);
}

template<typename T>
Coordinate partitionAndSearch(std::vector<std::vector<T> > &matrix, Coordinate origin, Coordinate dest, Coordinate pivot, T elem){
  Coordinate lowerLeftOrigin{pivot.row, origin.column};
  Coordinate lowerLeftDest{dest.row, pivot.column -1};
  Coordinate upperRightOrigin{origin.row, pivot.column};
  Coordinate upperRightDest{pivot.row -1, dest.column};

  Coordinate lowerLeft{findElement(matrix, lowerLeftOrigin, lowerLeftDest, elem) };

  if (lowerLeft == Coordinate{-1,-1}){
    return findElement<T>(matrix, upperRightOrigin, upperRightDest, elem);
  }

  return lowerLeft;
}

template<typename T>
Coordinate findElement(std::vector<std::vector<T> > &matrix, T elem){
  Coordinate origin{0,0};
  Coordinate dest{matrix.size()-1, matrix[0].size()-1};
  return findElement<T>(matrix, origin, dest, elem);
}

int main(){
  std::vector<std::vector<int> > matrix{{15, 20, 40,  85},
                                        {20, 35, 80,  95},
					{30, 55, 95,  105},
					{40, 80, 100, 120}};

  int valToFind{0};
  std::cout << "Value to find: ";
  std::cin >> valToFind;

  auto coordElem{findElement<int>(matrix, 55)};
  std::cout << (( coordElem !=Coordinate{-1,-1})? "Found element!\n": "Did not find element!\n");

  return 0;
}
