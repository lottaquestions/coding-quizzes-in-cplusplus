#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using std::vector;



float medianOf2SortdArrays(vector<int>& array1, vector<int>& array2){
  auto array1Size{array1.size()};
  auto array2Size{array2.size()};
  size_t totalLength {array1.size() + array2.size()};
  size_t halfLength {totalLength / 2};
  vector<int> biggerArray{array1};
  vector<int> smallerArray{array2};
  if (array1.size() < array2.size()){
    biggerArray = array2;
    smallerArray = array1;
  }

  //if(array1.empty() && array2.empty())

  if(totalLength == 0)
    return 0.0;

  int leftIdx{0}, rightIdx{int(smallerArray.size()) -1};

  while(true){
    auto i{(leftIdx + rightIdx)/2}; // Smaller array midpoint index
    auto j{ halfLength - i - 2}; // Larger array midpoint index. the -2 is because both arrays are indexed from zero, so we do -1 twice ie -1-1=-2

    int smallerArrayLeftVal  { (i>=0 ? smallerArray[i] :  INT_MIN) };
    int smallerArrayRightVal {( (i+1) < smallerArray.size() ? smallerArray[i+1] : INT_MAX )};

    int biggerArrayLeftVal  { (j>=0 ? biggerArray[j] :  INT_MIN) };
    int biggerArrayRightVal {( (j+1) < biggerArray.size() ? biggerArray[j+1] : INT_MAX )};

    // When the left partition is just right
    if (smallerArrayLeftVal  <= biggerArrayRightVal && biggerArrayLeftVal <= smallerArrayRightVal){
      // Odd : modulo produces non-zero
      if ( totalLength % 2)
	return std::min ( smallerArrayRightVal, biggerArrayRightVal );
      // Even total length
      return (std::max(smallerArrayLeftVal, biggerArrayLeftVal) +
	      std::min(smallerArrayRightVal, biggerArrayRightVal))/2.0f;
    }else if( smallerArrayLeftVal > biggerArrayRightVal )
      rightIdx = i - 1;
    else
      leftIdx = i + 1;
  }
  
  return 0.0;
}
float medianOfSortdArray(vector<int>& array1){
  auto array1Size{array1.size()};
  auto midPoint { array1Size/2 };
  if (array1Size % 2)
    return array1[midPoint];
  if (array1Size > 2)
    return (array1[midPoint] + array1[midPoint + 1])/2.0;
  return (array1[0] + array1[1])/2.0;
}


int main(){
  vector<vector<int>> inputs1 {{}, {2,5,6}, {1, 2,3}};
  vector<vector<int>> inputs2 {{}, {8,9,10}, {1, 2}};

  for(auto& vec1 : inputs1){
    for(auto& vec2 : inputs2){
      std::cout << "Array 1: ";
      std::for_each(vec1.begin(), vec1.end(), [](int x){std::cout<< x <<" ";});
      std::cout<<std::endl;
      std::cout << "Array 2: ";
      std::for_each(vec2.begin(), vec2.end(), [](int x){std::cout<< x <<" ";});
      std::cout<<std::endl;
      if (!vec1.empty() && !vec2.empty())
	std::cout << "Median: "<< medianOf2SortdArrays(vec1, vec2) << std::endl;
      else if (!vec1.empty())
	std::cout << "Median: "<< medianOfSortdArray(vec1) << std::endl;
      else if (!vec2.empty())
	std::cout << "Median: "<< medianOfSortdArray(vec2) << std::endl;
      else
	std::cout << "Median: "<< 0.0  << std::endl;
    }
  }
  return 0;
}
