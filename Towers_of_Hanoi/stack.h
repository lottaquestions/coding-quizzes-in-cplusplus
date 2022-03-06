#ifndef _STACK_H
#define _STACK_H
#include "disk.h"
class Stack{
public:
  Stack(){top = NULL;}
  ~Stack(){
    int i;
    while (top != NULL){
      Pop();
    }
  }
  
  /*Methods*/
  //Push a new disk onto the stack. i is the disk size
  virtual void Push(int i){
    if (top == NULL){
      top = new Disk(i);
      return;
    }
    Disk *temp = new Disk(i);
    temp->next = top;
    top = temp;
  }
  
  //Pop a disk off the stack
  virtual int Pop(){
    if (top == NULL)
      return 0;
    
    Disk *temp = top;
    top = top -> next;
    int data = temp -> size;
    delete temp;
    return data;
  }
protected:
  Disk *top;
};
#endif