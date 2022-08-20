#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include <set>

using std::vector;
using std::map;
using std::for_each;
using std::set;
using std::all_of;

bool dfs(int crs, set<int> visitSet, map<int,vector<int>> preMap){
  if (visitSet.find(crs) != visitSet.end())
    return false;
  
  if (preMap[crs].empty())
    return true;
  
  visitSet.insert(crs);
  bool allFinishable = all_of(preMap[crs].begin(), preMap[crs].end(), [&visitSet, &preMap](int pre){
									return dfs(pre, visitSet, preMap);
								      });
  if(!allFinishable)
    return false;

  visitSet.erase(crs);
  preMap[crs].clear();

  return true;
}

bool canFinish (int numCourses, vector<vector<int>>& prerequisites){
  // Map each course to prerequisites list
  vector<int> courses(numCourses);
  std::iota(courses.begin(), courses.end(), 0);

  map<int,vector<int>> preMap{};

  // Initialize map of course to prerequisites. Each course will start with an empty vector
  // of prerequisites
  for_each(courses.begin(), courses.end(), [&preMap](int crs){preMap[crs] = vector<int>{};});

  // Map each course to prerequisites
  for_each(prerequisites.begin(), prerequisites.end(), [&preMap](vector<int>& preReqVec){
							 int crs {preReqVec[0]};
							 int pre {preReqVec[1]};
							 preMap[crs].push_back(pre);
						       });


  // Set for course nodes we are currently visiting in the graph
  set<int> visitSet{};
  
  //Visit all courses along the current depth first search dfs
  bool isFinishable = all_of(courses.begin(), courses.end(), [&preMap, &visitSet](int crs){
						return dfs(crs,visitSet, preMap);
					      });
  return isFinishable;
}


int main (){
  vector<vector<int>> input{{0,1}, {0,2}, {1,3}, {1,4}, {3,4}};
  bool isFinishable{canFinish(input.size(), input)};
  std::cout << "Can we finish: " << isFinishable << std::endl;
  return 0;
}
