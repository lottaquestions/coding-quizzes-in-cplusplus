#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using std::vector;
using std::priority_queue;
using std::greater;

double medianFromData(priority_queue<double>& maxQ,
		      priority_queue<double, vector<double>, greater<double> >& minQ,
		      double median, int input){
  if (maxQ.size() > minQ.size()){
    if( input < median){
      minQ.push(maxQ.top());
      maxQ.pop();
      maxQ.push(input);
    }
    else{
      minQ.push(input);
    }
    median = (maxQ.top() + minQ.top()) / 2.0;
  }
  else if (maxQ.size() < minQ.size()){
    if (input > median){
      maxQ.push(minQ.top());
      minQ.pop();
      minQ.push(input);
    }
    else{
      maxQ.push(input);
    }
    median = (maxQ.top() + minQ.top()) / 2.0;
  }
  else{
    if (input < median){
      maxQ.push(input);
      median = maxQ.top();
    }
    else{
      minQ.push(input);
      median = minQ.top();
    }
  }
  return median;
}


int main(){
  priority_queue<double> maxQ{};
  priority_queue<double, vector<double>, greater<double> > minQ{};
  vector<int> input{1,2,3,4,5,6,7};
  double median = input[0];
  maxQ.push(input[0]);

  for (int i=1; i < input.size(); ++i){
    median = medianFromData(maxQ,minQ, median, input[i]);
    std::cout << "Current median: " << median << std::endl;
  }
  return 0;
}
