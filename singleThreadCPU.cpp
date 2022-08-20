#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using std::vector;
using std::priority_queue;
using std::for_each;
using std::pair;
using std::sort;
using std::max;

vector<int> getOrder (vector<vector<int>>& tasks){
  

  // Add index information
  int idx {0};
  for_each(tasks.begin(), tasks.end(), [&idx](vector<int>& curTask){
					 curTask.push_back(idx++);
				       });

  vector<int> ans{};

  auto timeIdxComparator = [](pair<int,int>& c1, pair<int,int>& c2){
			     if (c1.first == c2.first){
			       return c1.second > c2.second;
			     }
			     return c1.first > c2.first;
			   };
  priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(timeIdxComparator)> minHeap(timeIdxComparator);

  const auto numTasks{tasks.size()};
  size_t i{0}; // Tasks' pointer
  long time {0}; //current time
  sort(std::begin(tasks), std::end (tasks), [](vector<int>& v1, vector<int>& v2){
					      return v1[0] < v2[0];
					    }); 

  while (i < numTasks || !minHeap.empty()){
    if(minHeap.empty()){
      time = max (time, static_cast<long>(tasks[i][0]));
    }
    while(i < numTasks && time >= tasks[i][0]){
      minHeap.emplace(tasks[i][1], tasks[i][2]);
      ++i;
    }
    const auto [procTime, index] = minHeap.top();
    minHeap.pop();
    time += procTime;
    ans.push_back(index);
  }
  return ans;
}

int main(){
  vector<vector<int>> input {{1,2}, {4,1} , {3,2}, {2,4}};

  vector<int> orderOfJobs{getOrder(input)};
  for_each(orderOfJobs.begin(), orderOfJobs.end(), [](int i){std::cout << i << std::endl;});
  return 0;
}
