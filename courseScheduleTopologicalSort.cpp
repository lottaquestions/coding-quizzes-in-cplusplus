#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using std::map;
using std::vector;
using std::set;

//To compile: g++ -std=c++17 -O0 -g3 courseScheduleTopologicalSort.cpp -o courseScheduleTopologicalSort.bin

struct CourseScheduleParameters{
  map<int,vector<int>> prereq{};
  set<int> visit{};
  set<int> cycle{};
  vector<int> output{};
  CourseScheduleParameters() = default;
  CourseScheduleParameters(int numCourses){
    int i{0};
    // For every course create an empty vector that will hold the course prerequisites
    // Note: the i has to be passed by value it cannot be passed by reference.
    std::generate_n(std::inserter(prereq, prereq.begin()), numCourses, [i]() mutable {
									 return std::make_pair(i++, vector<int>());
								       });
  }
};

bool dfs(int crs, CourseScheduleParameters& courseSchedParams){
  auto& [prereq, visit, cycle, output] = courseSchedParams;

  // Check if we have hit a cycle of course dependencies, i.e. we have come back to process a course we have already processed in the current iteration.
  // If we are in a cycle then abort processing.
  if (cycle.find(crs) != cycle.end()){
    return false;
  }

  // Check if we visited this course before in a previous iteration. If we did, no need to proceed further as we know the course is completeable.
  if(visit.find(crs) != visit.end()){
    return true;
  }

  cycle.insert(crs);
  for (auto pre : prereq[crs]){
    if (!dfs(pre, courseSchedParams)){
      return false;
    }
  }
  cycle.erase(crs); // Done processing course, remove from cycle set
  
  visit.insert(crs);
  output.push_back(crs);
  
  return true;
}

vector<int> findOrder(int, vector<std::pair<int,int>>& prerequisitesVec, CourseScheduleParameters& courseSchedParams){
  // Using the input list of prerequisites, map each course to its appropriate prerequisites
  for(auto& [crs, pre] : prerequisitesVec){
    courseSchedParams.prereq[crs].push_back(pre);
  }
  for (auto& [crs,_] : courseSchedParams.prereq){
    if (!dfs(crs, courseSchedParams)){
      return vector<int>();
    }
  }
  return courseSchedParams.output;
}

int main(){
  int numCourses{4};
  vector<std::pair<int,int>> prerequisitesVec{{5,0},{4,0},{0,1},{0,2},{1,3},{3,2}};
  CourseScheduleParameters courseSchedParams(numCourses);
  vector<int> courseOrder = findOrder(numCourses, prerequisitesVec, courseSchedParams);
  bool printComma{false};
  auto whenCommaFalse = [&printComma](){printComma = true; return " ";};
  for(int course : courseOrder){
    std::cout << (printComma ? ", ": whenCommaFalse())  <<course ;
  }
  std::cout <<std::endl;
  return 0;
}
