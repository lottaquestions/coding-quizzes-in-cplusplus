#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

double medianOf2SortedArrays(vector<int>& a, int n, vector<int>& b, int m){
  int minIndex{0}, maxIndex{n}, i{0}, j{0};
  double median{0.0};

  while (minIndex <= maxIndex){
    i = (minIndex + maxIndex)/2;
    j = (n + m + 1)/2 - i;

    // if j is negative, we reduce the number of i elements from array a 
    if (j < 0){
      maxIndex = i-1;
      continue;
    }

    // If i = n, it means we have no elements from a[] in the second partition.
    // If j = 0, it means we have no elements from b[] in the first partition.
    // Increase the first partition if rightmost element from b[] in first partition is greater than rightmost element in first partition
    if( i < n && j > 0 && b[j -1] > a[i])
      minIndex = i + 1;
    // If i = 0, it means we have no elements from a[] in the first partition
    // If j = m, it means we have no elements from b[] in the second partition
    // Increase second partition if leftmost element in the second partition is less than the rightmost element in the first partition
    else if(i > 0 && j < m && b[j] < a[i-1])
      maxIndex = j - 1;
    // The right spot has been found
    else{
      // If we do not have any elements from a in the first partition, we return the last element from b[] in the first partition
      if (i == 0)
	median = b[j-1];
      // If we do not have any elements in the first partition from b[], we return the last element from a[] in the first partition
      else if (j == 0)
	median = a[i-1];
      else
	median = std::max(a[i-1], b[j-1]);
      break;
    }
  }
  // Now to calculate the median

  // For n + m = odd, return the middle element
  if ( (n + m) % 2)
    return median;

  // If a[] has no elements in the second partition
  if( i == n )
    return (median + b[j]) / 2.0;

  // if b[] has no elements in the second partition
  if (j == m)
    return (median + a[i]) / 2.0;

  return (median + std::min(a[i], b[j])) / 2.0;
  
}


int main(){
  vector<int> a {900};
  vector<int> b {10, 13, 14};

  auto n {a.size()};
  auto m {b.size()};

  if (n < m)
    cout << medianOf2SortedArrays(a, n, b, m);
  else
    cout << medianOf2SortedArrays(b, m, a, n);
  cout << endl;
  return 0;
}
