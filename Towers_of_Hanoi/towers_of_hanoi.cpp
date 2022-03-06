#include <iostream>
#include "tower.cpp"

using namespace std;

int main (void){
  int stack_size = 0;
  
  cout << "Enter the stack size"<< endl;
  cin >> stack_size;
  
  Tower *src = new Tower(stack_size);
  Tower *dest = new Tower(0);
  Tower *buf = new Tower(0);
  
  MoveDisk(stack_size, src, dest, buf);
  
  cout << "Destination Tower"<<endl;
  for (int i= stack_size; i > 0; --i ){
    cout << dest->PopDisk() <<endl;
  }
  return 0;
}